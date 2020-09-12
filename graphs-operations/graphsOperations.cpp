/*
Arcabouço para implementação do Trabalho de
ECOM02 - Teoria dos Grafos

Grupo:
	Alex Junior Pereira
	Alex Junio Ribeiro Campos
	Caíque Cléber Dias de Rezende
	Leonardo Henrique de Melo
*/

#include <bits/stdc++.h>

#define MAX 100
#define INF 2000000

using namespace std;

int grafo[MAX][MAX]; // representação matricial dos grafos (matriz de adjacencia)
void exibeMenu();
void leGrafo(int g[][MAX],int ordem, int tamanho);
bool regular(int ordem);
void insercaoGrafo(int ordem, int a, int b);
void fusaoVertice(int ordem, int a, int b);
void contracaoVertice(int ordem, int a, int b);
int excentricidade (int g[][MAX], int ordem, int vertice);
int raio (int g[][MAX], int ordem);
int diametro (int g[][MAX], int ordem);
void centro (int g[][MAX], int ordem);
void printGrafo(int ordem);

int main()
{

    int operacao, ordem, tamanho, vertice;
    int a, b;

    // exibeMenu();

    while (true)
    {

    	cin >> operacao;
    	cout << endl;

        switch (operacao)
        {

        case 0:
            cout << "Programa finalizado." << endl;
            exit(0);

        case 1: // Caso exemplo - Verificar se Grafo é regular - Mat.Adjacencias
            cin >> ordem;
            leGrafo(grafo, ordem, ordem);
            if (regular(ordem))
                cout << "Grafo regular" << endl << endl;
            else
                cout << "Grafo nao regular" << endl << endl;
            break;

        case 2: // Excentricidade
        	cin >> ordem >> vertice;
            leGrafo(grafo, ordem, ordem);
            cout << endl << excentricidade(grafo, ordem, vertice) << endl << endl;
            break;

        case 3: // Raio
        	cin >> ordem;
            leGrafo(grafo, ordem, ordem);
            cout << endl << raio(grafo, ordem) << endl << endl;
            break;

        case 4: // Diametro
        	cin >> ordem;
            leGrafo(grafo, ordem, ordem);
            cout << endl << diametro(grafo, ordem) << endl << endl;
            break;

        case 5: // Centro
            cin >> ordem;
            leGrafo(grafo, ordem, ordem);
            centro(grafo, ordem);
            break;

        case 6: // Fusao vertice
        	cin >> ordem >> a >> b;
            fusaoVertice(ordem, a, b);
            break;

        case 7: // Contracao vertice
        	cin >> ordem >> a >> b;
            contracaoVertice(ordem, a, b);
            break;

        case 8: // Insercao grafo
        	cin >> ordem >> a >> b;
            insercaoGrafo(ordem, a, b);
            break;

        default:
            cout << "Opcao invalida!" << endl;
            break;

        }

    }

    return 0;

}

void exibeMenu()
{
    printf("::::::Menu:::::: \n1 - Regular\n2 - Excentricidade\n3 - Raio\n4 - Diametro\n5 - Centro\n6 - Fusao vertice\n7 - Contracao vertice\n8 - Insercao grafo\n0 - Encerrar programa\n\n");
}

// Funcao para ler a matriz
void leGrafo (int g[][MAX], int ordem, int tamanho)
{
    for (int i=0; i < ordem; i++)
        for (int j=0; j < tamanho; j++)
            cin >> g[i][j];
}

// Verifica se grafo é regular com Matriz de Adjacências
bool regular(int ordem)
{
    int grau=0, grau_aux;
    for (int i=0; i < ordem; i++)
        grau += (grafo[0][i] != 0 ? 1 : 0);
    for (int i=1; i < ordem; i++) {
        grau_aux=0;
    	for (int j=0; j < ordem; j++) {
        	grau_aux += (grafo[i][j] != 0 ? 1 : 0);
    	}
    	if (grau != grau_aux)
        	return false;
    }
    return true;
}

void insercaoGrafo(int ordem, int a, int b){
    leGrafo(grafo, ordem, ordem);
    if(ordem < MAX - 1){
        ordem++;
        grafo[a][b] = 0;
        grafo[b][a] = 0;
        grafo[a][ordem-1] = 1;
        grafo[b][ordem-1] = 1;
    	for(int i = 0; i < ordem; i++){
        	if( i == a || i == b){
            	grafo[ordem-1][i] = 1;
        	}else{
            	grafo[ordem-1][i] = 0;
        	}
    	}
    	printGrafo(ordem);
    }
}

void fusaoVertice(int ordem, int a, int b){
    leGrafo(grafo, ordem, ordem);
    int novo = 0;
    if(ordem >= 2){
        novo = a;
        if(grafo[a][b] == 1){
            grafo[novo][novo] = 2;
        }

        for(int c = 0; c < ordem; c++){
            if(a != c){
                if( grafo[a][c] == 1 && grafo[b][c] == 1){
                grafo[novo][c] = 2;
                grafo[c][novo] = 2;
            }
            else if((grafo[a][c] == 1 && grafo[b][c] == 0) || (grafo[a][c] == 0 && grafo[b][c] == 1)){
                grafo[novo][c] = 1;
                grafo[c][novo] = 1;
            }
        }

        }

        for(int i = b; i < ordem-1; i++){
            for(int j = 0; j < ordem; j++){
                grafo[i][j] = grafo[i+1][j];
            }
        }
        for(int i = 0; i < ordem; i++){
            for(int j = b; j< ordem - 1; j++){
                grafo[i][j] = grafo[i][j+1];
            }
        }
        ordem--;
    }
    printGrafo(ordem);
}

void contracaoVertice(int ordem, int a, int b){
    leGrafo(grafo, ordem, ordem);
    int novo = a;
    if(ordem >= 2){
        for( int c = 0; c < ordem; c++){
            if(a != c){
                if( grafo[a][c] == 1 || grafo[b][c] == 1){
                    grafo[novo][c] = 1;
                    grafo[c][novo] = 1;
                }
            }
        }


        for(int i = b; i < ordem-1; i++){
            for(int j = 0; j < ordem; j++){
                grafo[i][j] = grafo[i+1][j];
            }
        }
        for(int i = 0; i < ordem; i++){
            for(int j = b; j< ordem - 1; j++){
                grafo[i][j] = grafo[i][j+1];
            }
        }
        ordem--;
    }
    printGrafo(ordem);
}

int excentricidade (int g[][MAX], int ordem, int vertice){
    bool visitado[ordem];
    int fila[ordem], primeiro=0, ultimo=0, exc=0, qtd=1, encontrados=1;

    for(int i=0;i<ordem;i++){ visitado[i]=false; }

    do{
        qtd=encontrados;
        encontrados=0;
        while(qtd--){
            visitado[vertice]=true;
            for(int i=0;i<ordem;i++){
                if(g[vertice][i]!=0 && visitado[i]==false){
                    fila[ultimo]=i;
                    ultimo++;
                    encontrados++;
                    visitado[i]=true;
                }
            }
            vertice=fila[primeiro];
            primeiro++;
        }
        if(encontrados>0) exc++;
    } while(encontrados!=0);

    return exc;
}

int raio (int g[][MAX], int ordem){
    int vraio = ordem-1, tamanho;
    for(int i=0;i<ordem;i++){
        tamanho = excentricidade(grafo, ordem, i);
        if(tamanho<vraio){vraio=tamanho;}
    }
    return vraio;
}

int diametro (int g[][MAX], int ordem){
    int vdiametro = 0, tamanho;
    for(int i=0;i<ordem;i++){
        tamanho = excentricidade(grafo, ordem, i);
        if(tamanho>vdiametro){vdiametro=tamanho;}
    }
    return vdiametro;
}

void centro (int g[][MAX], int ordem){
    int vraio = ordem-1, tamanho;
    int tamvert[MAX];
    bool primeiro=true;

    for(int i=0;i<ordem;i++){
        tamanho = excentricidade(grafo, ordem, i);
        tamvert[i]=tamanho;
        if(tamanho<vraio){vraio=tamanho;}
    }
    cout << endl;
    for(int i=0;i<ordem;i++){
        if(tamvert[i]==vraio){
                if(primeiro) {cout << i << " "; primeiro=false;}
                else cout << i << " ";
        }
    }
    cout << endl << endl;
}

void printGrafo(int ordem){
    cout << endl;
    for(int i = 0; i < ordem; i++){
        for(int j = 0; j < ordem; j++){
            cout << grafo[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}
