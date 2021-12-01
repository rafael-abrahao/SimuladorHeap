#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

int totalElementos = 0;

void Imprimir(int *heap);
int IndicePai(int x);
int FilhoEsq(int x);
int FilhoDir(int x);
void AjustarSubindo(int *heap, int pos);
void AjustarDescendo(int *heap, int pos);
void Inserir(int *heap, int x);
int Remover(int *heap);

int main()
{
    setlocale(LC_CTYPE, "Portuguese");

    int opt, n, cont = 1;
    int *minHeap = (int*) malloc(sizeof(int));

    while(cont == 1)
    {
        printf("\nHeap: ");
        Imprimir(minHeap);
        printf("\n1- Inserir Elemento\n");
        printf("2- Remover Elemento\n");
        printf("3- Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opt);

        switch (opt)
        {
        case 1:
            printf("\nDigite o valor do elemento a ser inserido: ");
            scanf("%d", &n);
            minHeap = realloc(minHeap, (totalElementos + 1) * sizeof(int));
            Inserir(minHeap, n);
            break;
        case 2:
            opt = Remover(minHeap);
            minHeap = realloc(minHeap, totalElementos * sizeof(int));
            printf("\nElemento %d removido", opt);
            break;
        case 3:
            printf("\nEncerrando...");
            cont = 0;
            break;
        default:
            printf("\nOpção inválida");
            break;
        }
    }
}

void Imprimir(int *heap)
{
    if(totalElementos == 0)
        printf("<vazio>\n");
    else
    {
        for(int i = 0; i < totalElementos - 1; i++)
        {
            printf("%d, ",heap[i]);
        }
        printf("%d\n",heap[totalElementos - 1]);
    }
}
int IndicePai(int x)
{
    int indice = (int) floor((x - 1) / 2);
    if(x <= 0 || x >= totalElementos)
        return -1;
    else
        return indice;
}
int FilhoEsq(int x)
{
    int indice = (2 * x) + 1;
    if(x >= totalElementos || indice >= totalElementos)
        return -1;
    else
        return indice;
}
int FilhoDir(int x)
{
    int indice = (2 * x) + 2;
    if(x >= totalElementos || indice >= totalElementos)
        return -1;
    else
        return indice;
}
void AjustarSubindo(int *heap, int pos)
{
    if(pos != -1)
    {
        int pai = IndicePai(pos);
        if(pai != -1)
        {
            if(heap[pos] < heap[pai])
            {
                int aux = heap[pos];
                heap[pos] = heap[pai];
                heap[pai] = aux;

                AjustarSubindo(heap, pai);
            }
        }
    }
}
void AjustarDescendo(int *heap, int pos)
{
    int filhoEsq = FilhoEsq(pos);
    int filhoDir = FilhoDir(pos);
    if(pos != -1 && filhoEsq != -1)
    {
        int menorFilho = filhoEsq;
        if(filhoDir != -1 && heap[filhoDir] < heap[menorFilho])
            menorFilho = filhoDir;
        
        if(heap[menorFilho] < heap[pos])
        {
            int aux = heap[pos];
            heap[pos] = heap[menorFilho];
            heap[menorFilho] = aux;

            AjustarDescendo(heap, menorFilho);
        }
    }
}
void Inserir(int *heap, int x)
{
    heap[totalElementos] = x;
    totalElementos++;

    AjustarSubindo(heap, totalElementos - 1);
}
int Remover(int *heap)
{
    if(totalElementos == 0)
        return -1;
    int retorno = heap[0];
    heap[0] = heap[totalElementos - 1];
    totalElementos--;

    AjustarDescendo(heap, 0);

    return retorno;
}