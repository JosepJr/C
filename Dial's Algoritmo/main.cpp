// C / C++ program for Dijkstra's shortest path algorithm for adjacency
// list representation of graph

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

// Estrutura que representa a lista de adjacencia
struct AdjListNode{
    int dest;
    int weight;
    struct AdjListNode* next;
};

// Estrutura que representa a lista de adjacencia
struct AdjList{
    struct AdjListNode *head;  // Ponteiro que vai ler o No da lista
};

//Uma estrutura para representar um gráfico. Um grafo é um conjunto de listas de adjacência.
//Tamanho da matriz será V (número de vértices do gráfico)
struct Graph{
    int V;
    struct AdjList* array;
};

// função para criar um novo nó de lista de adjacência
struct AdjListNode* newAdjListNode(int dest, int weight){
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

//função que cria um gráfico de vértices V
struct Graph* createGraph(int V){
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    // Cria um conjunto de listas de adjacência. Tamanho da matriz será V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

    // Inicializar cada lista de adjacência como vazio, fazendo cabeça como NULL
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}


//Estrutura que representa o Mini Heap do NO
struct MinHeapNode{
    int  v;
    int dist;
};

// Estrutura que representa todo o Mini Heap
struct MinHeap{
    int size;      // Number of heap nodes present currently
    int capacity;  // Capacity of min heap
    int *pos;     // This is needed for decreaseKey()
    struct MinHeapNode **array;
};

// Função para criar um novo mini Heap
struct MinHeapNode* newMinHeapNode(int v, int dist){
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

// A função que cria o mini Heap
struct MinHeap* createMinHeap(int capacity){
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// A função para trocar dois nós de mini Heap. Necessário para mini heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b){
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// A função padrão para heapify em determinado index
// Esta função também atualiza a posição de nós quando eles são trocados.
// Posição é necessário para Key diminuir ()
void minHeapify(struct MinHeap* minHeap, int idx){
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;

    if (smallest != idx)
    {
        // Os nós a serem trocados no mini Heap
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];

        // Troca de posicoes
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Troca de nos
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// Função que verifica que se o mini Heap esta vazio ou não
int isEmpty(struct MinHeap* minHeap){
    return minHeap->size == 0;
}

// Função padrão para extrair nó mínimo de heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap){
    if (isEmpty(minHeap))
        return NULL;

   // Armazenar o nó raiz
    struct MinHeapNode* root = minHeap->array[0];

    // Substituir nó de raiz com o último nó
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

   //Posição Atualização do último nó
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;

   // Reduzir o tamanho do heap e raiz heapify
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Função para diminuir o valor de nó de um dado vértice v. Esta função
// usa pos [] do Mini Heap para obter o índice atual de nó no mini Heap
void decreaseKey(struct MinHeap* minHeap, int v, int dist){

    // Retorna o índice v na matriz de heap
    int i = minHeap->pos[v];


    // Obter o nó, e atualizar o seu valor dist
    minHeap->array[i]->dist = dist;

    // Vai para cima, enquanto a árvore completa não é heapified.
     // Este é um O (log n) de loop
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)    {

        // Trocar esse nó com o seu pai
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);

        // Move para o índice do pai
        i = (i - 1) / 2;
    }
}

// função para verificar se um determinado vértice
// 'V' é no mini Heap ou não
bool isInMinHeap(struct MinHeap *minHeap, int v){
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}


// Função usada para imprimir a solução
void printArr(int dist[], int n){
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

// A principal função que calcula distâncias de caminhos mais curtos de src para todos
// Vértices. É uma função O (ELogV)
void dijkstra(struct Graph* graph, int src){
    int V = graph->V; //pega o numero de vertices no grafo
    int dist[V];      // valores dist usado para escolher aresta de peso mínimo no vertice

    // Mini Heap representa conjunto E
    struct MinHeap* minHeap = createMinHeap(V);


    // Inicializar mini pilha com todos os vértices. valor dist de todos os vértices
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    // Fazer o valor da dist vértice src é 0 de modo que é extraído primeiro
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);


    // Inicialmente tamanho do heap min é igual a V
    minHeap->size = V;

    // No seguinte loop, mini pilha contém todos os nós
    // cuja distância mais curta ainda não está finalizado.
    while (!isEmpty(minHeap))
    {
        // Extrair o vértice com valor mínimo da distância
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // Armazene o número de vértices extraídos


        // Atravessar todos os vértices adjacentes de L (o extraído
        // Vértice) e atualizar seus valores de distância
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;


            // Se a distância mais curta para v ainda não foi finalizado, e distância para v
             // Através de u, é inferior à distância previamente calculada
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
                                          pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;

                // Valor da distância atualização no heap mini também
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

   // Imprimir as distâncias mais curtas calculadas
    printArr(dist, V);
}


// Adiciona uma borda para um grafo não direcionado
void addEdge(struct Graph* graph, int src, int dest, int weight){
    // Adicionar uma aresta de src para dest. Um novo nó é adicionado à lista de adjacência
    // de src. O nó é adicionada no início
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Uma vez que o gráfico é não direcionado, adicione uma borda para SRC também
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

//Função para ler a quantidade de vertices no grafo e armazenar os espaços
int DimencaoMatriz(){
    FILE *dados;
    dados = fopen("arquivo.txt", "r");

    if (dados == NULL){
        printf("Nao foi possivel Abrir o Arquivo!!\n");
        getchar();
        exit(0);
    }

    int dimencao;

    fscanf(dados, "%d", &dimencao);

    fclose(dados);

    return dimencao;
}

//função usada para ler o arquivo e começar a criar o grafo armazenando os vertices e os pesos
void PreencherLista(struct Graph* graph){
    int linha = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    char auxiliar[250];
    char lixo1[50];
    char lixo2[50];
    char lixo3[50];
    FILE *dados;
    dados = fopen("arquivo.txt", "r");

    if (dados == NULL){
        printf("Nao foi possivel Abrir o Arquivo!!\n");
        getchar();
        exit(0);
    }
    while((fgets(auxiliar, sizeof(auxiliar), dados))!= NULL ){
        if (linha > 1){

            char *temp = strtok(auxiliar,"-");

            strcpy(lixo1,temp);
            x = atoi(lixo1);

            temp = strtok(NULL,"-");
            strcpy(lixo2,temp);
            y = atoi(lixo2);

            temp = strtok(NULL,"\n");
            strcpy(lixo3,temp);
            z = atoi(lixo3);

            addEdge(graph, x-1, y-1, z);
        }
        linha++;
    }

    fclose(dados);
}

int main(){

    int V = DimencaoMatriz();
    struct Graph* graph = createGraph(V);
    PreencherLista(graph);

    dijkstra(graph, 0);

    return 0;
}
