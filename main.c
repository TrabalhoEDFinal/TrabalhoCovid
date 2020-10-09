#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Familia{ // FAMILIA
    char nome_fam[2];
    int qtd_fam;
    int virus;
    struct Familia *prox;
}Fam;
typedef struct CabFam{ //CABECA  PRA FAMILIA
    Fam *prox;
    Fam *ult; // SETA ULTIMO DA LISTA
    Fam *prim; // SETA PRIMEIRO DA LISTA
}Cfam;

void criaFam(Cfam **p){
    (*p)->prim = NULL;
    (*p)->ult = NULL;
    (*p)->prox = NULL;
}
void *insere(Cfam **p, char *nome_fam, int qtd_fam){

    Fam *novo = (Fam*)malloc(sizeof(Fam));
    if(novo == NULL){
        printf("erro, sistema nao quis dar memoria \n");
    };
    strcpy(novo->nome_fam,nome_fam);
    novo->qtd_fam = qtd_fam;
    novo->virus = 0;
    novo->prox = NULL;

    if((*p)->prim == NULL){
        (*p)->prim = novo;
        (*p)->ult = novo;
        (*p)->prox = novo;
    }
    else{
        (*p)->ult->prox  = novo;
        (*p)->ult = novo;
    }
       
}
void print(Cfam *p){
    Fam *aux = p->prox;
    if(aux == NULL){
        printf("LISTA VAZIA \n");
        return;
    }
    while(aux != NULL){
        printf("||FAM: %s || QTD: %d || VIRUS: %d || \n", aux->nome_fam,aux->qtd_fam,aux->virus);
        aux = aux->prox;
    }
}
// ENTRADAS COMANDO
// 1 - CRIA FAMILIA
// 2 - LIGA FAMILIA
// 3 - INSERE VIRUS
// 4 - INICIA SIMULAÇÃO
// 5 - VERIFICA SURTO

// a ordem dos subcomandos dependem da forma como eles estão dispostos na função

void comandoArquivo(int comando, Cfam **pfam){

	int movag,vmult,mov; // VARIAVEIS A.ATUA -- V.MULTIPLICA -- MOVIMENTOS
    int qtd; // QTD DE PESSOAS NA FAM
    char fam1[2]; // STRING PARA NOME FAMILIA GENERICO
    char fam2[2];//STRING PARA NOME FAMILIA 2.
    char func[18]; //ARMAZENA STRING FUNCAO

	FILE *ent; // ARQUIVO ENTRADA
    ent = fopen("entrada.txt","r");

    if(ent==NULL){
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    while(!feof(ent)) //ATE O FIM DA LISTA
    {
        fscanf(ent,"%s",func); // Le o super texto ent e armazena cada linha em func

        // Cria uma lista para a familia

        if(strcmp(func,"inserefamilia")==0 && comando==1)
        {
            printf("%s -> ",func); 
            fscanf(ent,"%s",fam1);
            printf("fam %s : ",fam1);
            fscanf(ent,"%d",&qtd);
            printf(" qtd fam %d \n",qtd);
            insere(&(*pfam),fam1,qtd);
            print(*pfam);
        }

        // Cria uma lista que liga as familias atraves de suas IDs

        if(strcmp(func,"ligafamilias")==0 && comando==2)
        {   
            printf("%s -> ",func); 
            fscanf(ent,"%s",fam1); 
            printf("fam %s : ",fam1);
            fscanf(ent,"%s",fam2); 
            printf("fam %s \n",fam2);
        }

        // Edita a presença de virus nas familias infectadas

        if(strcmp(func,"inserevirus")==0 && comando==3)
        {
            printf("%s -> ",func); 
            fscanf(ent,"%s",fam1); 
            printf("fam %s\n",fam1);
        }

        // Carrega as informações da 4 parte antes de serem executadas na simulação

        if(strcmp(func,"agente_atua")==0 && comando==4){
            printf("%s -> ",func);
            fscanf(ent,"%d",&movag);
            printf("mov ag %d \n",movag);
        }
        if(strcmp(func,"vírus_multiplica")==0 && comando==4)
        {
            printf("%s -> ",func);
            fscanf(ent," %d ",&vmult);
            printf(" vmult %d \n",vmult);
        }

        // Inicia a simulação da 4 parte

        if(strcmp(func,"iniciasimulacao")==0 && comando==4)// função gatilho
        {
            printf("%s -> ",func);
            fscanf(ent,"%d",&mov); //GUARDA OS MOVIMENTOS
            printf("mov %d \n",mov);
            //iniciasimulacao() PRINCIPAL
            // SECUNDARIAS
            //agente_atua() USAREMOS OS MOVIMENTOS DO AGENTE AQUI (MOVAG)
            //virus_multiplica() USAREMOS O MULTIPLICA DO VIRUS AQUI (VMULT)
            // -----ESSAS FUNCOES SO ESTAO NO PDF DO TRABALHO
            //agente_saude 
            //virus_move
        }
        
        // Verifica o surto que ocorreu na simulação da 4 parte
        
        if(strcmp(func,"verificasurto")==0 && comando==5)
        {        
            printf("%s -> ",func);
            printf("VERIFICA SURTO \n");
            //verificasurto();
            break;
            
        }
    }
}

void main(){
    Cfam *fam = (Cfam*)malloc(sizeof(Cfam)); // LSITA FAMILIAS
    criaFam(&fam); //SETA NULL
    comandoArquivo(1,&fam);
    //comandoArquivo(2);
    //comandoArquivo(3);
    //comandoArquivo(4);
    //comandoArquivo(5);

}