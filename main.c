#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Familia{ // FAMILIA
    char nome_fam;
    int qtd_fam;
    int virus;
    struct Familia *prox;
}Fam;
typedef struct CabFam{ //CABECA  PRA FAMILIA
    Fam *prox;
    Fam *ult; // SETA ULTIMO DA LISTA
    Fam *prim; // SETA PRIMEIRO DA LISTA
}Cfam;

typedef struct Ligacao{
    struct Ligacao *p1; //LIGACAO 1
    struct Ligacao *p2; //LIGACAO 2
    struct Ligacao *prox;
}Lig;

void anulaLig(Lig **p){
    (*p)->p1 = NULL;
    (*p)->p2 = NULL;
    (*p)->prox = NULL;
}
void anulaFam(Cfam **p){
    (*p)->prim = NULL;
    (*p)->ult = NULL;
    (*p)->prox = NULL;
}

void main(){
    Cfam *fam = (Cfam*)malloc(sizeof(Cfam)); // LSITA FAMILIAS
    anulaFam(&fam); //SETA NULL
    Lig *lig = (Lig*)malloc(sizeof(Lig)); //LISTA LIGACOES
    anulaLig(&lig); // SETA NULL

    
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
        fscanf(ent,"%s",func); //LE A STRING FUNCAO
        if(strcmp(func,"agente_atua")==0){
            printf("%s -> ",func);
            fscanf(ent,"%d",&movag); // GUARDA OS MOVIMENTOS APRA DEPOIS
            printf("mov ag %d \n",movag);
        }
        if(strcmp(func,"vírus_multiplica")==0)//COMPARA STRINGS
        {
            printf("%s -> ",func);
            fscanf(ent," %d ",&vmult); // GUARDA O MULTIPLICA PARA DEPOIS 
            printf(" vmult %d \n",vmult);
        }
        if(strcmp(func,"inserefamilia")==0)//COMPARA STRINGS
        {
            printf("%s -> ",func); 
            fscanf(ent,"%s",fam1); // GUARDA A FAMILIA 
            printf("fam %s : ",fam1);
            fscanf(ent,"%d",&qtd);
            printf(" qtd fam %d \n",qtd);
            //inserefamilia();
        }
        if(strcmp(func,"ligafamilias")==0)//COMPARA STRINGS
        {   
            printf("%s -> ",func); 
            fscanf(ent,"%s",fam1); // GUARDA A FAMILIA  1
            printf("fam %s : ",fam1);
            fscanf(ent,"%s",fam2); // GUARDA A FAMILIA  2
            printf("fam %s \n",fam2);
            //ligafamilias();
        }
        if(strcmp(func,"inserevirus")==0)//COMPARA STRINGS
        {
            printf("%s -> ",func); 
            fscanf(ent,"%s",fam1); // GUARDA A FAMILIA E JA USA 
            printf("fam %s\n",fam1);
            //inserevirus();
        }
        if(strcmp(func,"iniciasimulacao")==0)//COMPARA STRINGS
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
        if(strcmp(func,"verificasurto")==0)//COMPARA STRINGS
        {        
            printf("%s -> ",func);
            printf("VERIFICA SURTO \n");
            //verificasurto();
            break;
            
        }
    }



}