// Trabalho Covid
// Julio César G. Costa - RA: 2203049
// Francisco Correa Neto - RA: 2201615
// Recomenda-se a execução no ambiente linux mint o qual foi desenvolvido.
// Necessario um arquivo nomeado como entrada.txt com os comandos a serem executados.
// Obs.: A ordem dos comandos não é um problema.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>

int m = 0; // A quantidade de movimentos globais dos virus
int ae = 0; // A quantidade de vezes que o agente errou
int ac = 0; // A quantidade de vezes que o agente acertou

// 1.0.0 - Todas as Structs do Sistema
// 1.0.1 VIRUS
typedef struct Virus{ 
    int mov;
    struct Virus *prox;
}Virus;
// 1.1.1 FAMILIA
typedef struct Familia{ 
    char nome_fam[2];
    int qtd_fam;
    int qtd_virus;
    int doente;
    struct Virus *infectado;
    struct Familia *prox;
}Fam;
// 1.1.2 CABECA PRA FAMILIA
typedef struct CabFam{ 
    Fam *prox;
    Fam *ult; 
    Fam *prim; 
}Cfam;
// 1.2.1 LIGA FAMILIA
typedef struct LigaFam{ 
    char nome_fam1[3];
    char nome_fam2[3];
    struct LigaFam *prox;
}LFam;
// 1.2.2 CABECA PRA LIGA FAMILIA
typedef struct CabLFam{ 
    LFam *prox;
    LFam *ult; 
    LFam *prim; 
}CLfam;

// 2.0.0 - Criação das cabeças das Listas
// 2.0.1 Cria a Cabeça da Lista Familia
Cfam *criaFam(){
    Cfam *CF = (Cfam*)malloc(sizeof(Cfam));
    CF->prim = NULL;
    CF->ult = NULL;
    CF->prox = NULL;
    return CF;
}
// 2.0.2 Cria a Cabeça da Lista de Ligações
CLfam *criaLFam(){
    CLfam *CLF = (CLfam*)malloc(sizeof(CLfam));
    CLF->prim = NULL;
    CLF->ult = NULL;
    CLF->prox = NULL;
    return CLF;
}

// 3.0.0 - Inserções
// 3.0.1 Insere Inicio da Lista Familias
void insereFam(Cfam **p, char *nome_fam, int qtd_fam){

    Fam *novo = (Fam*)malloc(sizeof(Fam));
    if(novo == NULL){
        printf("Memória insuficiente para alocar. \n");
    };
    strcpy(novo->nome_fam,nome_fam);
    novo->qtd_fam = qtd_fam;
    novo->qtd_virus = 0;
    novo->doente = 0;
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
// 3.0.2 Insere Inicio da Lista Ligações das Familias
void insereLFam(CLfam **p, char *fam1, char *fam2){

    LFam *novo = (LFam*)malloc(sizeof(LFam));
    if(novo == NULL){
        printf("Memória insuficiente para alocar. \n");
    };

    strcpy(novo->nome_fam1, fam1);
    strcpy(novo->nome_fam2, fam2);

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
// 3.0.3 Insere Virus
void insereVirus(Cfam **fam, char *famdesc){

	Virus *novoVirus = (Virus*)malloc(sizeof(Virus));

	Fam *aux = (*fam)->prox;
    if(aux == NULL){
        printf("Lista Familia Vazia, impossivel inserir virus. \n");
        return;
    }
    while(aux != NULL){
        if (strcmp(aux->nome_fam, famdesc) == 0) // Encontra a familia a qual será inserido o virus.
        {
        	aux->qtd_virus = aux->qtd_virus + 1;
        	aux->doente = 1;
        	novoVirus->mov = 0;
        	novoVirus->prox = NULL;
        	if (aux->infectado == NULL) // Familia não tem virus.
        		aux->infectado = novoVirus;
        	else // A familia já tem virus.
        	{
        		Virus *auxVirus = aux->infectado;
        		while (auxVirus->prox != NULL) // Itera até encontrar o ultimo virus vinculado a Familia.
        		{
        			auxVirus = auxVirus->prox;
        		}
        		auxVirus->prox = novoVirus;
        	}
        	break;
        }
        aux = aux->prox;
    }
}

// 4.0.0 - Comandos da simulação
// 4.0.1 Verifica se o virus ainda está presente na simulação
bool verificaExistenciaVirus(Cfam **fam)
{
	Fam *aux = (*fam)->prox;
    if(aux == NULL){
        printf("Lista Familia Vazia, impossivel verificar a existencia de virus. \n");
        return 0;
    }
    while(aux != NULL){
    	if (aux->infectado != NULL) // Verifica se encontrou virus
    		return true;
    	aux = aux->prox;
    }
    return false;
}
// 4.0.2 Agente de Saude
char agenteSaude(Cfam **fam)
{
	int contfam = 0;
	Fam *auxfam = (*fam)->prox;
	if(auxfam == NULL)
	{
		printf("A Lista familia está vazia. \n");
        return '0';
	}
	while(auxfam != NULL) // conta quantas familias existem para rand
	{
		contfam++;
		auxfam = auxfam->prox;
	}
	int res = rand() % contfam; // gera um numero randomico entre 0 e o contador de familias
	auxfam = (*fam)->prox; // retorna a iteração da familia ao primeiro membro
	for (int i = 0; i < res; i++) // percorre a lista familias até o membro res (numero randomico)
	{
		auxfam = auxfam->prox;
	}
	auxfam->qtd_virus = 0;
	auxfam->doente = 0;
	auxfam->infectado = NULL; // cura a familia escolhida randomicamente
	printf("%d - O AGENTE DE SAUDE atuou na Familia %s.\n", m, auxfam->nome_fam);
	return auxfam->nome_fam[1];
}
// 4.0.3 Virus Multiplica
void virusMultiplica(Cfam **fam, char *fammult)
{
	insereVirus(&(*fam), fammult);
	insereVirus(&(*fam), fammult);
	printf("%d - Virus se MULTIPLICANDO em %s.\n", m, fammult);
}
// 4.0.4 Executa a movimentação do virus
void virusMove(Cfam **fam, CLfam **lfam, int mov, int agente, int mult)
{  
	char familiasvinculadas[100]; // numero maximo de familias vinculadas a uma unica familia
	Fam *auxfam = (*fam)->prox;
	Fam *auxfam2 = (*fam)->prox;
	LFam *auxlfam = (*lfam)->prox;
	Virus *auxV;
	Virus *auxV2;
	Virus *antV;
	int contfv = 0;
	char famdest[3];
	if(auxfam == NULL || auxlfam == NULL)
	{
		printf("A Lista familia ou de ligações está vazia, logo os virus não podem se mover. \n");
        return;
	}
	while(auxfam != NULL) // percorre a lista de familias
	{ 
    	if (auxfam->infectado != NULL && m < mov) // a familia tem virus
    	{
    		printf("%d - Virus encontrado em %s.\n", m, auxfam->nome_fam);
    		contfv = 0; // limpa o contador de familia vinculadas 		
    		famdest[0] = 'F';
    		famdest[1] = ' ';
    		famdest[2] = '\0';
    		auxV = NULL;
    		antV = NULL;
    		for (int i = 0; i < 100; i++) // limpa o vetor de familias vinculadas
				familiasvinculadas[i] = '0';
			auxlfam = (*lfam)->prox; // limpa a iteração da lista de ligações
			auxfam2 = (*fam)->prox; // limpa a iteração da lista das familias

			auxV = auxfam->infectado; // aux para o primeiro virus da familia
			antV = auxfam->infectado;
	
			if (auxV->prox != NULL) // tem um ou mais virus
			{
				if (auxV->prox->prox == NULL) // tem dois virus
				{
					antV = auxV;
					auxV = auxV->prox;
				}
				else // tem mais que dois virus
				{
			    	while (auxV->prox != NULL) // encontra o ultimo virus da familia com virus
			    	{
			    		antV = auxV;
			    		auxV = auxV->prox;
			    	}
		    	}
	    	}

	    	if (auxV->mov % mult == 0 && auxV->mov != 0) // O virus vai se multiplicar
    		{
    			virusMultiplica(&(*fam), auxfam->nome_fam);
    			break;
    		}
    	
    		if (auxV->mov % agente == 0 && auxV->mov != 0) // Agente de saude vai atuar
    		{
    			char famagen[3];
    			famagen[0] = 'F';
    			famagen[1] = agenteSaude(&(*fam));
    			famagen[2] = '\0';
    			if (strcmp(auxfam->nome_fam, famagen) == 0)
    				break;
    			if (verificaExistenciaVirus(&(*fam)) == false)
    				break;
    		}
    		
    		auxV->mov++; // contabiliza o movimento unitario do virus
    		while(auxlfam != NULL) // busca as familias vinculadas a familia infectada
    		{
    			if (strcmp(auxfam->nome_fam, auxlfam->nome_fam1) == 0) // verifica o primeiro membro e guarda o segundo
	            {	 	        
	                familiasvinculadas[contfv] = auxlfam->nome_fam2[1];	// atribui a familia vinculada ao vetor de familias possiveis
	                contfv++; // contador para o random   
	            }
	            if (strcmp(auxfam->nome_fam, auxlfam->nome_fam2) == 0) // verifica o segundo membro e guarda o primeiro
	            {	            	 
	                familiasvinculadas[contfv] = auxlfam->nome_fam1[1];  // atribui a familia vinculada ao vetor de familias possiveis
	                contfv++; // contador para o random                 	            
	            }
    			auxlfam = auxlfam->prox;
    		}
    		int res = rand() % contfv; // gera um numero randomico entre 0 e o contador de familias vinculadas
    		famdest[1] = familiasvinculadas[res]; // descobre a familia destino
    		printf("%d - Movendo o ultimo virus de %s para %s.\n", m, auxfam->nome_fam, famdest);
    		
    		// Inicio do movimento
    		// Vinculando a Familia destino
    		while(auxfam2 != NULL) // percorre a lista de familias
			{			
				if (strcmp(famdest, auxfam2->nome_fam) == 0) // encontra a familia a ser infectada
				{
					auxV2 = NULL;
					auxfam2->qtd_virus++;
					auxfam2->doente = 1;
					if (auxfam2->infectado == NULL){
						auxfam2->infectado = auxV; // associa o virus a nova familia no inicio da lista de virus
					}
					else{
						auxV2 = auxfam2->infectado;
						while (auxV2->prox != NULL) // encontra o ultimo virus da familia a ser infectada
							auxV2 = auxV2->prox;
						auxV2->prox = auxV; // associa o virus a nova familia no final da lista de virus
					}
					break;	
				}
				auxfam2 = auxfam2->prox;
			}
			// Desvinculando da familia origem
			if (auxfam->infectado->prox == NULL) // a familia origem tem um virus
			{
				auxfam->qtd_virus--;
				auxfam->infectado = NULL;
			}
			else if (auxfam->infectado->prox->prox == NULL)
			{
				auxfam->qtd_virus--;
				auxfam->infectado->prox = NULL;
			}
			else
			{
				auxfam->qtd_virus--;
				antV->prox = NULL;
			}
			printf("%d - Virus movido para %s.\n", m, famdest);
    		m++; // contabiliza o movimento global dos virus 		
    	}
    	auxfam = auxfam->prox;
    }
}

// 5.0.0 - Relatórios
// 5.0.1 Relatório da Familia
void printFam(Cfam *p){
    Fam *aux = p->prox;
    if(aux == NULL){
        printf("LISTA VAZIA \n");
        return;
    }
    while(aux != NULL){
        printf("||FAM: %s || QTD: %d || QTDVIRUS: %d|| DOENTE: %d|| \n", aux->nome_fam,aux->qtd_fam,aux->qtd_virus,aux->doente);
        aux = aux->prox;
    }
}

// FUNÇÃO PRINCIPAL DE EXECUÇÃO DOS COMANDOS POR ORDEM
// 1 - CRIA FAMILIA
// 2 - LIGA FAMILIA
// 3 - INSERE VIRUS
// 4 - INICIA SIMULAÇÃO
// 5 - VERIFICA SURTO

// a ordem dos subcomandos dependem da forma como eles estão dispostos na função

void comandoArquivo(int comando, Cfam **pfam, CLfam **plfam){
    
    // Variavel de Comando
    char func[18]; 
    // Variaveis Comando 1 (Lista Familia)
    char fam[2]; 
    int qtd; 
    // Variaveis Comando 3 (Lista Familia)
    char faminf[3];
    
    int movag,vmult,mov; // VARIAVEIS A.ATUA -- V.MULTIPLICA -- MOVIMENTOS

    // Leitura do conteudo do arquivo entrada.txt

    FILE *ent; 
    ent = fopen("entrada.txt","r");

    if(ent==NULL){
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    while(!feof(ent)) // Leitura por linha do arquivo entrada.txt
    {
        fscanf(ent,"%s",func);

        // Comando de criação da lista familia

        if(strcmp(func,"inserefamilia")==0 && comando==1)
        { 
            fscanf(ent,"%s",fam);
            fscanf(ent,"%d",&qtd);
            printf("Adicionando a familia %s a lista familias.\n", fam);
            insereFam(&(*pfam), fam, qtd);
        }

        // Comando de criação da lista que liga as familias atraves de suas IDs

        if(strcmp(func,"ligafamilias")==0 && comando==2)
        {   
            char aux[7];
            char aux1[3];
            char aux2[3];
            
            fgets(aux,7,ent); 

            for (int i = 0; i < 7; i++)
            {
                if (i > 0 && i < 3)
                {
                    aux1[i-1] = aux[i];
                }
                if (i > 3 && i < 6)
                {
                    aux2[i-4] = aux[i];
                }
            }  
            aux1[2] = '\0';
            aux2[2] = '\0';
            printf("Adicionando a ligação entre %s - %s na lista de ligações.\n", aux1, aux2);           
            insereLFam(&(*plfam), aux1, aux2);
        }

        // Insere o virus na familia em questão

        if(strcmp(func,"inserevirus")==0 && comando==3)
        {
        	fscanf(ent,"%s",faminf);
            printf("Infectando a familia %s.\n", faminf);
            insereVirus(&(*pfam),faminf);
        }

        // Configura o agente e o virus para a simulação

        if(strcmp(func,"agente_atua")==0 && comando==4){
            fscanf(ent,"%d",&movag);
            printf("O Agente foi configurado para atuar após %d movimentos do virus.\n", movag);
        }
        if(strcmp(func,"vírus_multiplica")==0 && comando==4){
            fscanf(ent," %d ",&vmult);
            printf("A Multiplicação dos virus foi configurada para acontecer após %d movimentos do virus.\n", vmult);
        }

        // Inicia a simulação da 4 parte

        if(strcmp(func,"iniciasimulacao")==0 && comando==4)
        {
            fscanf(ent,"%d",&mov); 
            printf("Simulação configurada para um total maximo de %d movimentos.\n", mov);
            printf("------------------------------------------------\n");
            printf("Iniciando Simulação...\n");
            while (m < mov)
		    {
		        if (verificaExistenciaVirus(&(*pfam)) == false)
		        {
		        	printf("%s\n", "Não há mais nenhum virus em nenhuma familia.");
		            break;
		        }
		        else
		        	virusMove(&(*pfam),&(*plfam), mov, movag, vmult);
		    }

        }
        
        // Verifica o surto que ocorreu na simulação da 4 parte
        
        if(strcmp(func,"verificasurto")==0 && comando==5)
        {        
            
            printf("VERIFICA SURTO \n");
            //verificasurto();
            break;
            
        }
    }
}

void main()
{
	srand(time(NULL));
	printf("------------- Configuração inicial -------------\n");
	printf("Criando Lista Familias.\n");
	Cfam *fam = criaFam(); 
	printf("Criando a Lista de ligações entre as Familias.\n");
    CLfam *Lfam = criaLFam();
    comandoArquivo(1,&fam,&Lfam);
    comandoArquivo(2,&fam,&Lfam);
    comandoArquivo(3,&fam,&Lfam);
    comandoArquivo(4,&fam,&Lfam);
    printf("------------- Relatórios -------------\n");
    printFam(fam);
}