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

//Uma estrutura para representar um gr�fico. Um grafo � um conjunto de listas de adjac�ncia.
//Tamanho da matriz ser� V (n�mero de v�rtices do gr�fico)
struct Graph{
    int V;
    struct AdjList* array;
};

// fun��o para criar um novo n� de lista de adjac�ncia
struct AdjListNode* newAdjListNode(int dest, int weight){
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

//fun��o que cria um gr�fico de v�rtices V
struct Graph* createGraph(int V){
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    // Cria um conjunto de listas de adjac�ncia. Tamanho da matriz ser� V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

    // Inicializar cada lista de adjac�ncia como vazio, fazendo cabe�a como NULL
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

// Fun��o para criar um novo mini Heap
struct MinHeapNode* newMinHeapNode(int v, int dist){
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

// A fun��o que cria o mini Heap
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

// A fun��o para trocar dois n�s de mini Heap. Necess�rio para mini heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b){
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// A fun��o padr�o para heapify em determinado index
// Esta fun��o tamb�m atualiza a posi��o de n�s quando eles s�o trocados.
// Posi��o � necess�rio para Key diminuir ()
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
        // Os n�s a serem trocados no mini Heap
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

// Fun��o que verifica que se o mini Heap esta vazio ou n�o
int isEmpty(struct MinHeap* minHeap){
    return minHeap->size == 0;
}

// Fun��o padr�o para extrair n� m�nimo de heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap){
    if (isEmpty(minHeap))
        return NULL;

   // Armazenar o n� raiz
    struct MinHeapNode* root = minHeap->array[0];

    // Substituir n� de raiz com o �ltimo n�
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

   //Posi��o Atualiza��o do �ltimo n�
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;

   // Reduzir o tamanho do heap e raiz heapify
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Fun��o para diminuir o valor de n� de um dado v�rtice v. Esta fun��o
// usa pos [] do Mini Heap para obter o �ndice atual de n� no mini Heap
void decreaseKey(struct MinHeap* minHeap, int v, int dist){

    // Retorna o �ndice v na matriz de heap
    int i = minHeap->pos[v];


    // Obter o n�, e atualizar o seu valor dist
    minHeap->array[i]->dist = dist;

    // Vai para cima, enquanto a �rvore completa n�o � heapified.
     // Este � um O (log n) de loop
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)    {

        // Trocar esse n� com o seu pai
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);

        // Move para o �ndice do pai
        i = (i - 1) / 2;
    }
}

// fun��o para verificar se um determinado v�rtice
// 'V' � no mini Heap ou n�o
bool isInMinHeap(struct MinHeap *minHeap, int v){
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}


// Fun��o usada para imprimir a solu��o
void printArr(int dist[], int n){
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

// A principal fun��o que calcula dist�ncias de caminhos mais curtos de src para todos
// V�rtices. � uma fun��o O (ELogV)
void dijkstra(struct Graph* graph, int src){
    int V = graph->V; //pega o numero de vertices no grafo
    int dist[V];      // valores dist usado para escolher aresta de peso m�nimo no vertice

    // Mini Heap representa conjunto E
    struct MinHeap* minHeap = createMinHeap(V);


    // Inicializar mini pilha com todos os v�rtices. valor dist de todos os v�rtices
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    // Fazer o valor da dist v�rtice src � 0 de modo que � extra�do primeiro
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);


    // Inicialmente tamanho do heap min � igual a V
    minHeap->size = V;

    // No seguinte loop, mini pilha cont�m todos os n�s
    // cuja dist�ncia mais curta ainda n�o est� finalizado.
    while (!isEmpty(minHeap))
    {
        // Extrair o v�rtice com valor m�nimo da dist�ncia
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // Armazene o n�mero de v�rtices extra�dos


        // Atravessar todos os v�rtices adjacentes de L (o extra�do
        // V�rtice) e atualizar seus valores de dist�ncia
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;


            // Se a dist�ncia mais curta para v ainda n�o foi finalizado, e dist�ncia para v
             // Atrav�s de u, � inferior � dist�ncia previamente calculada
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
                                          pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;

                // Valor da dist�ncia atualiza��o no heap mini tamb�m
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

   // Imprimir as dist�ncias mais curtas calculadas
    printArr(dist, V);
}


// Adiciona uma borda para um grafo n�o direcionado
void addEdge(struct Graph* graph, int src, int dest, int weight){
    // Adicionar uma aresta de src para dest. Um novo n� � adicionado � lista de adjac�ncia
    // de src. O n� � adicionada no in�cio
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Uma vez que o gr�fico � n�o direcionado, adicione uma borda para SRC tamb�m
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

//Fun��o para ler a quantidade de vertices no grafo e armazenar os espa�os
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

//fun��o usada para ler o arquivo e come�ar a criar o grafo armazenando os vertices e os pesos
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
