#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* =====================================================================
    ========================CHECK LIST==================================
    INSERE FAMILIA ----- OK
    LIGA FAMILIAS -------- BO
    INSERE VIRUS ------- OK
    RANDOM ------------- OK
    INICIA SIMULACAO
        -MOVIMENTOS --------- X
        -AGENTE --------------- X
        -VIRUS MULTIPLICA ------ X
        AGENTE SAUDE ------- TEM UM COMENTARIO COM UM ESBOÇO, PROVAVELMENTE SEJA SÓ AQUILO.
    VERIFICA SURTO -------- X
========================================================================= */

// Lista Familia

typedef struct Familia{ // FAMILIA
    char nome_fam[2];
    int qtd_fam;
    int virus;
    struct Familia *prox;
}Fam;
typedef struct CabFam{ //CABECA PRA FAMILIA
    Fam *prox;
    Fam *ult; // SETA ULTIMO DA LISTA
    Fam *prim; // SETA PRIMEIRO DA LISTA
    int tam;
}Cfam;

Cfam *criaFam(){
    Cfam *CF = (Cfam*)malloc(sizeof(Cfam));
    CF->prim = NULL;
    CF->ult = NULL;
    CF->prox = NULL;
    CF->tam = 0;
    return CF;
}

// Liga Familias

typedef struct LigaFam{ // LIGA FAMILIA
    char nome_fam1[2];
    char nome_fam2[2];
    struct LigaFam *prox;
}LFam;
typedef struct CabLFam{ //CABECA PRA LIGA FAMILIA
    LFam *prox;
    LFam *ult; // SETA ULTIMO DA LISTA
    LFam *prim; // SETA PRIMEIRO DA LISTA
}CLfam;

CLfam *criaLFam(){
    CLfam *CLF = (CLfam*)malloc(sizeof(CLfam));
    CLF->prim = NULL;
    CLF->ult = NULL;
    CLF->prox = NULL;
    return CLF;
}

// Insere Familia

void insereFam(Cfam **p, char *nome_fam, int qtd_fam){

    Fam *novo = (Fam*)malloc(sizeof(Fam));
    if(novo == NULL){
        printf("Out of Memory. 1\n");
    };
    strcpy(novo->nome_fam,nome_fam);
    novo->qtd_fam = qtd_fam;
    novo->virus = 0;
    novo->prox = NULL;

    if((*p)->prim == NULL){
        (*p)->prim = novo;
        (*p)->ult = novo;
        (*p)->prox = novo;
        (*p)->tam ++;
    }
    else{
        (*p)->ult->prox  = novo;
        (*p)->ult = novo;
        (*p)->tam ++;
    }
}

// Insere Liga Familia

void ligafamilias(CLfam **p, char *nome_fam1, char *nome_fam2){

    LFam *novo = (LFam*)malloc(sizeof(LFam));
    if(novo == NULL){
        printf("Out of Memory. 2 \n");
    };
    strcpy(novo->nome_fam1,nome_fam1);
    strcpy(novo->nome_fam2,nome_fam2);
    novo->prox = NULL;

    if((*p)->prim == NULL){
        (*p)->prim = novo;
        (*p)->ult = novo;
        (*p)->prox = novo;
        
    }
    else{
        (*p)->ult->prox = novo;
        (*p)->ult = novo;
    }
}

// Escreve a Lista Familias na tela

void printFam(Cfam *p){
    Fam *aux = p->prox;
    if(aux == NULL){
        printf("LISTA VAZIA \n");
        return;
    }
    while(aux != NULL){
        printf("||FAM: %s || QTD: %d || VIRUS: %d|| \n", aux->nome_fam,aux->qtd_fam,aux->virus);
        aux = aux->prox;
    }
}

void printLFam(CLfam *p)
{
    LFam *aux = p->prox;
    if(aux == NULL){
        printf("LISTA VAZIA \n");
        return;
    }
    while(aux != NULL){
        printf("FAM1: %s FAM2: %s\n", aux->nome_fam1, aux->nome_fam2);
        aux = aux->prox;
    }
}
void inserevirus(Cfam **p, char *fam){
    Fam *aux = (*p)->prox;

    while (aux != NULL)
    {
        if(strcmp(aux->nome_fam,fam)==0){
            aux->virus ++;
            return;
        }
        aux = aux->prox;
    }
    
}

/*void agente_saude(Fam *p){ // passamos o ponteiro para a familia infectada;
    (*p)->virus = 0;
    return;}
*/
char* random(Cfam *p){ //recebe cabeça // devolve char com a familia sorteada
    int res;
    srand((unsigned)time(NULL));
    res = 1 + (rand() % (p->tam));
    printf("%d \n",res);
    char a =  (char)(res + 48);
    printf("%c \n",a);
    char resp[1] = {'F',a};
    printf("%s", resp);
    return resp;
}
// ENTRADAS COMANDO
// 1 - CRIA FAMILIA
// 2 - LIGA FAMILIA
// 3 - INSERE VIRUS
// 4 - INICIA SIMULAÇÃO
// 5 - VERIFICA SURTO

// a ordem dos subcomandos dependem da forma como eles estão dispostos na função

void comandoArquivo(int comando, Cfam **pfam, CLfam **plfam){
    
    // Comando
    char func[18]; //ARMAZENA STRING FUNCAO

    // Lista Fam
    char fam[2]; // STRING PARA NOME FAMILIA GENERICO
    int qtd; // QTD DE PESSOAS NA FAM

    // Lista Liga Fam
    char fam1[2];//STRING PARA NOME FAMILIA 1.
    char fam2[2];//STRING PARA NOME FAMILIA 2.

    
    int movag,vmult,mov; // VARIAVEIS A.ATUA -- V.MULTIPLICA -- MOVIMENTOS

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
            fscanf(ent,"%s",fam);
            fscanf(ent,"%d",&qtd);
            insereFam(&(*pfam), fam, qtd);
        }

        // Cria uma lista que liga as familias atraves de suas IDs

        if(strcmp(func,"ligafamilias")==0 && comando==2)
        {   
            char f1[2],f2[2]; //BO
            printf("Digite fam: ");
            scanf(" %s",f1);
            printf("Difite fam 2: ");
            scanf(" %s",f2);
            ligafamilias(&(*plfam),f1, f2);
        }

        // Edita a presença de virus nas familias infectadas

        if(strcmp(func,"inserevirus")==0 && comando==3)
        {
            fscanf(ent,"%s",fam1); 
            inserevirus(&(*pfam),fam1);
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
    Cfam *fam = criaFam(); // LISTA FAMILIAS
    CLfam *Lfam = criaLFam();
    comandoArquivo(1,&fam,&Lfam);
    printf("LISTA FAM \n");
    printFam(fam);
    comandoArquivo(3,&fam,&Lfam);
    printf("LISTA APOS INSERCAO \n");
    printFam(fam);
   // printLFam(Lfam);
    //comandoArquivo(2);
    //comandoArquivo(3);
    //comandoArquivo(4);
    //comandoArquivo(5);

}