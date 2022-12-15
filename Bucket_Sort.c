#include <assert.h>
# include <stdio.h>
#include <stdlib.h>
#define NARRAY 7    /*  Tamanho do array */
#define NBUCKET 7   /* Tamanho do bucket */
#define INTERVAL 10 /*  Variar bucket */

struct Node
{
    int data;
    struct Node *next;
};

void BucketSort(int arr[]);
struct Node *InsertionSort(struct Node *list);
void print(int arr[]);
void printBuckets(struct Node *list);
int getBucketIndex(int value);

void BucketSort(int arr[])
{
    int i, j;
    struct Node **buckets;

    /* alocar memória para array de ponteiros para os baldes */
    buckets = (struct Node **)malloc(sizeof(struct Node *) * NBUCKET);

    /* inicializar ponteiros para os baldes */
    for (i = 0; i < NBUCKET; ++i)
    {
        buckets[i] = NULL;

    }

    /* colocar itens nos baldes */
    /* cria uma lista de links em cada slot de bucket */

    for (i = 0; i < NARRAY; i++)
    {
        struct Node *current;
        int pos = getBucketIndex(arr[i]);
        current = (struct Node *)malloc(sizeof(struct Node));
        current->data = arr[i];
        current->next = buckets[pos];
        buckets[pos] = current;
    }

    /* verifique o que há em cada balde */
    for (i = 0; i < NBUCKET; i++)
    {
        printf("Bucket[\"%d\"] : ", i);
        printBuckets(buckets[i]);
        printf("\n");
    }

    /* classificando o bucket usando o Insertion Sort */
    for (i = 0; i < NBUCKET; i++)
    {

       buckets[i] = InsertionSort(buckets[i]);

    }

    /* verifique o que há em cada balde */
    printf("--------------\n");
    printf("Buckets depois de classificado\n");
    for (i = 0; i < NBUCKET; i++)
    {
        printf("Bucket[\"%d\"] : ", i);
        printBuckets(buckets[i]);
        printf("\n");
    }

    /* colocar itens de volta no array original */
    for (j = 0, i = 0; i < NBUCKET; ++i)
    {
        struct Node *node;
        node = buckets[i];
        while (node)
        {
            // pré-condição para evitar fora dos limites da matriz
            assert(j < NARRAY);
            arr[j++] = node->data;
            node = node->next;
        }
    }

    /* free memoria */
    for (i = 0; i < NBUCKET; ++i)
    {
        struct Node *node;
        node = buckets[i];
        while (node)
        {
            struct Node *tmp;
            tmp = node;
            node = node->next;
            free(tmp);
        }
    }
    free(buckets);
    return;
}

/* Ordenação por Inserção */
struct Node *InsertionSort(struct Node *list)
{
    struct Node *k, *nodeList;
    /* precisa de pelo menos dois itens para classificar*/
    if (list == NULL || list->next == NULL)
    {
        return list;
    }

    nodeList = list;
    k = list->next;
    nodeList->next = NULL; /* 1º nó é uma nova lista */
    while (k != NULL)
    {
        struct Node *ptr;
        /* verifique se inserir antes de primeiro */
        if (nodeList->data > k->data)
        {
            struct Node *tmp;
            tmp = k;
            k = k->next;  // importante por enquanto
            tmp->next = nodeList;
            nodeList = tmp;
            continue;
        }

        // do começo ao fim
        // encontra [i] > [i+1]
        for (ptr = nodeList; ptr->next != NULL; ptr = ptr->next)
        {
            if (ptr->next->data > k->data)
                break;
        }

        // se encontrado (acima)
        if (ptr->next != NULL)
        {
            struct Node *tmp;
            tmp = k;
            k = k->next;  // importante por enquanto
            tmp->next = ptr->next;
            ptr->next = tmp;
            continue;
        }
        else
        {
            ptr->next = k;
            k = k->next;  // importante por enquanto
            ptr->next->next = NULL;
            continue;
        }
    }
    return nodeList;
}

int getBucketIndex(int value) { return value / INTERVAL; }

void print(int ar[])
{
    int i;
    for (i = 0; i < NARRAY; ++i)
    {
        printf("%d ", ar[i]);
    }
    printf("\n");
}

void printBuckets(struct Node *list)
{
    struct Node *cur = list;
    while (cur)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
}

int menu()
{
    int resp;
    printf("---Menu Principal---\n");
    printf("1 - Melhor caso\n");
    printf("2 - Pior caso\n");
    printf("0 - Sair\n");
    scanf("%d", &resp);
    return resp;
}
int main(void){
    int resp;
    int array[NARRAY] = {57, 41, 25, 20, 13, 12, 9};
    int array2[NARRAY] = {12, 57, 9, 41, 20, 25, 13};

 do
    {
        resp = menu();
            switch(resp)
            {
                case 1:
                    printf("Array original\n");
                    printf("9, 12, 13, 20, 25, 41, 57\n");
                    printf("------------\n");

                    BucketSort(array);
                    printf("------------\n");
                    printf("Array ordenada\n");
                    print(array);

                    break;
                case 2:
                    printf("Array original\n");
                    printf("13, 25, 20, 41, 9, 57, 12\n");
                    printf("------------\n");

                    BucketSort(array2);
                    printf("------------\n");
                    printf("Array ordenada\n");
                    print(array2);
                    break;

                    case 0:
                    printf("Ate breve.\n");
                    break;
        }
    }
    while(resp!=0);

    return 0;
}
