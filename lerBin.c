#include <stdio.h>
#include <string.h>
#include "gerarBin.h"
#include "lerBin.h"
#include <stdlib.h>
#include <locale.h>

const char* caminhoArquivo = "alimentos.bin";

Categoria* Categorias = NULL; 

int alteracao = 0;

const char* categoriaParaString(CategoriaAlimento categoria){

   switch (categoria){
   case CEREAIS: return "Cereais e derivados";  case VERDURAS: return "Verduras, hortaliças e derivados";  case FRUTAS: return "Frutas e derivados";  case GORDURAS: return "Gorduras e óleos";  case PESCADOS: return "Pescados e frutos do mar";  case CARNES: return "Carnes e derivados";   case LEITE: return "Leite e derivados";  case BEBIDAS: return "Bebidas (alcoólicas e não alcoólicas)";  case OVOS: return "Ovos e derivados"; case ACUCARADOS: return "Produtos açucarados"; case MISC: return "Miscelâneas";  case INDUSTRIALIZADOS: return "Outros alimentos industrializados"; case PREPARADOS: return "Alimentos preparados";  case LEGUMINOSAS: return "Leguminosas e derivados";  case NOZES: return "Nozes e sementes";
    }
}

void lerBin(const char* nome_arquivo){

   FILE* arquivo = fopen(nome_arquivo, "rb");
   if (!arquivo) {perror("Erro ao abrir o arquivo");exit(EXIT_FAILURE);}
   
   size_t lido, total = 0;
   
   Alimento temp;
   
   while((lido = fread(&temp, sizeof(Alimento), 1, arquivo)) == 1){
   
   //Criacao, alocacao e insercao de AlimentoNodo na lista Categorias
   
   AlimentoNodo* nodo = malloc(sizeof(*nodo)); 
   if (!nodo) { perror("malloc"); fclose(arquivo); exit(EXIT_FAILURE); }
   
   nodo->alimento = temp;
   nodo->proximo = NULL;
   
   inserirCategoria(nodo);
   
   
   
   }
   
   if (ferror(arquivo)){ perror("Erro na leitura do arquivo.");}
   
   fclose(arquivo);
}

//Ao ler cada Alimento, criar um AlimentoNodo. Checar lista de categorias e buscar categoria correspondente (criar se não existente). Integrar esse Nodo à lista de Categorias na categoria correta. Cada elemento da lista de categorias guarda UMA das cateogorias de alimentos, assim como uma lista contendo todos os elementos da categoria em questao. Odenar todas as listas alfabeticamente automaticamente.


void inserirAlimentoNodo(AlimentoNodo** lista, AlimentoNodo* novo){

   //insercao na lista de categorias
   
   //caso de lista vazia
   if (*lista == NULL){ *lista = novo; return;}
   
   AlimentoNodo* sucessor = *lista;
   AlimentoNodo* antecessor = NULL;
   
   while(sucessor != NULL && strcmp(novo->alimento.descricao, sucessor->alimento.descricao) > 0)  { //fica buscando a posicao correta enquanto a descricao do novo venha depois na ordem alfabetica
    		   antecessor = sucessor;
		   sucessor = sucessor->proximo;}
		
   if (sucessor != NULL && strcmp(sucessor->alimento.descricao, novo->alimento.descricao) == 0)
   { //caso de um alimento com a mesma descricao ja exista na ListaAlimentos da categoria;
	printf("Esse alimento já está na lista."); return; 
   }
   else if (sucessor == NULL)  //caso de insercao no fim da lista
   {
   	antecessor->proximo = novo;
   	novo->proximo = NULL;
   }
   else if (sucessor == *lista) // caso de insercao no inicio da lista
   {
   	novo->proximo = sucessor;
   	*lista = novo;
   }
   else //caso de insercao entre dois elementos
   {
   	novo->proximo = sucessor;
   	antecessor->proximo = novo;
   }
}


void inserirCategoria(AlimentoNodo* novo){
//quando novo alimentoNodo for criado, essa funcao sera chamada para checar se em Categorias existe algum elemento da categoria do novo alimentoNodo. Se nao existir, chama inserirCategoria.

    
    	Categoria* sucessor = Categorias;
    	Categoria* antecessor = NULL;
    	
    	while(sucessor != NULL && strcmp(categoriaParaString(novo->alimento.categoria),categoriaParaString(sucessor->categoria)) > 0)  { //fica buscando a posicao correta enquanto a categoria do novo venha depois na ordem alfabetica
    		   antecessor = sucessor;
		   sucessor = sucessor->proximo;}
		
	if (sucessor != NULL && sucessor->categoria == novo->alimento.categoria){
	//caso a categoria ja exista em Categorias;
	inserirAlimentoNodo(&sucessor->listaAlimentos, novo);
	
	//Insercao na arvore proteica
   	ArvoreNodo* PTNode = malloc(sizeof(*PTNode));
  	PTNode->alimento = novo->alimento;
   	PTNode->direito = PTNode->esquerdo = NULL;
   	inserirProteina(&sucessor->arvoreProteina, PTNode);
   
   	//Insercao na arvore energetica
   	ArvoreNodo* ETNode = malloc(sizeof(*ETNode));
   	ETNode->alimento = novo->alimento;
   	ETNode->direito = ETNode->esquerdo = NULL;
   	inserirEnergia(&sucessor->arvoreEnergia, ETNode);
	return; 
	}
	//caso a categoria ainda não exista
	
	Categoria* categoria = malloc(sizeof(*categoria));
	categoria->categoria = novo->alimento.categoria;
	categoria->listaAlimentos = NULL;
	categoria->arvoreProteina = NULL;
	categoria->arvoreEnergia = NULL;
	categoria->proximo = sucessor;
	
	if (antecessor == NULL){ Categorias = categoria;} //insercao no inicio (antecessor null)
	else{ antecessor->proximo = categoria;}//liga o antecessor ao novo alimento inserido
    	
    	inserirAlimentoNodo(&categoria->listaAlimentos, novo);
    	
    	//Insercao na arvore proteica
   	ArvoreNodo* PTNode = malloc(sizeof(*PTNode));
  	PTNode->alimento = novo->alimento;
   	PTNode->direito = PTNode->esquerdo = NULL;
   	inserirProteina(&categoria->arvoreProteina, PTNode);
   
   	//Insercao na arvore energetica
   	ArvoreNodo* ETNode = malloc(sizeof(*ETNode));
   	ETNode->alimento = novo->alimento;
   	ETNode->direito = ETNode->esquerdo = NULL;
   	inserirEnergia(&categoria->arvoreEnergia, ETNode);  
    	
    	  
}
     
void inserirEnergia(ArvoreNodo** raiz, ArvoreNodo* novo){

	if (*raiz == NULL){
	*raiz = novo; return;
	}
	
	if (novo->alimento.energia < (*raiz)->alimento.energia){
		inserirEnergia(&(*raiz)->esquerdo, novo);
	}
	else{
		inserirEnergia(&(*raiz)->direito, novo);
	}
}

void inserirProteina(ArvoreNodo** raiz, ArvoreNodo* novo){

	if (*raiz == NULL){
	*raiz = novo; return;
	}
	
	if (novo->alimento.proteina < (*raiz)->alimento.proteina){
		inserirProteina(&(*raiz)->esquerdo, novo);
	}
	else{
		inserirProteina(&(*raiz)->direito, novo);
	}

}
    
    
void listarArvoreDecrescente(ArvoreNodo* raiz) {
        
    // primeiro percorre a direita (maiores valores)
    if(raiz->direito != NULL) listarArvoreDecrescente(raiz->direito);

    // imprime o alimento atual
    imprimirAlimento(raiz->alimento);

    // depois percorre a esquerda (menores valores)
    if (raiz->esquerdo != NULL) listarArvoreDecrescente(raiz->esquerdo);
}



void imprimirEnergiaIntervalo(ArvoreNodo* raiz, int min, int max) {
    
    if(raiz->esquerdo != NULL && min < raiz->alimento.energia) imprimirEnergiaIntervalo(raiz->esquerdo, min, max);

    if (raiz->alimento.energia >= min && raiz->alimento.energia <= max){
    imprimirAlimento(raiz->alimento);}

    if (raiz->direito != NULL && max > raiz->alimento.energia) imprimirEnergiaIntervalo(raiz->direito, min, max);
}



void imprimirProteinaIntervalo(ArvoreNodo* raiz, double min, double max) {
    
    if(raiz->esquerdo != NULL && min < raiz->alimento.proteina) imprimirProteinaIntervalo(raiz->esquerdo, min, max);

    if (raiz->alimento.proteina >= min && raiz->alimento.proteina <= max){
    imprimirAlimento(raiz->alimento);}

    if (raiz->direito != NULL && max > raiz->alimento.proteina) imprimirProteinaIntervalo(raiz->direito, min, max);
}

void listarIntervaloEnergia(){

   int escolha = mostrarMenuCategorias();
   int min; int max;
   printf("Insira o valor mínimo desejado: \n");
   scanf("%d", &min);
   printf("Insira o valor máximo desejado: \n");
   scanf("%d", &max);
   
    Categoria* atual = Categorias;
    int indice = 1;
    while (atual != NULL)
     {
       if (indice == escolha)
       {
       printf("Alimentos da categoria %s dentro do intervalo do valor de energia especificado:\n\n", categoriaParaString(atual->categoria));
       imprimirEnergiaIntervalo(atual->arvoreEnergia, min, max);
              return;
       }
	atual = atual->proximo;
	indice++;
     }
}



void listarIntervaloProteina(){

   int escolha = mostrarMenuCategorias();
   double min; double max;
   printf("Insira o valor mínimo desejado: \n");
   scanf("%lf", &min);
   printf("Insira o valor máximo desejado: \n");
   scanf("%lf", &max);
   
    Categoria* atual = Categorias;
    int indice = 1;
    while (atual != NULL)
     {
       if (indice == escolha)
       {
       printf("Alimentos da categoria %s dentro do intervalo do valor de proteína especificado:\n\n", categoriaParaString(atual->categoria));
       imprimirProteinaIntervalo(atual->arvoreProteina, min, max);
              return;
       }
	atual = atual->proximo;
	indice++;
     }
          printf("Categoria não encontrada.");
}






void imprimirArvoreProteina(){

    int escolha = mostrarMenuCategorias();
    
    Categoria* atual = Categorias;
 
    int indice = 1;
    
    while (atual != NULL)
     {
       if (indice == escolha)
       {
       printf("Alimentos da categoria %s em ordem decrescente de proteína em gramas:\n\n", categoriaParaString(atual->categoria));
       listarArvoreDecrescente(atual->arvoreProteina);
              return;
       }
	atual = atual->proximo;
	indice++;
     }
          printf("Categoria não encontrada.");
}
void imprimirArvoreEnergia(){

    int escolha = mostrarMenuCategorias();
    
    Categoria* atual = Categorias;
 
    int indice = 1;

    while (atual != NULL)
     {
       if (indice == escolha)
       {
       printf("Alimentos da categoria %s em ordem decrescente de energia em KCal:\n\n", categoriaParaString(atual->categoria));
       listarArvoreDecrescente(atual->arvoreEnergia);
              return;
       }
	atual = atual->proximo;
	indice++;
     }
     printf("Categoria não encontrada.");
}


void imprimir(){

    int 
    
    codigo = mostrarMenuCategorias();
    
    Categoria* atual = Categorias;
    codigo--;
    while (atual != NULL)
     {
       if (atual->categoria == codigo)
       {
       printf("Alimentos da categoria %s em ordem decrescente de energia em KCal:\n\n", categoriaParaString(atual->categoria));
       listarArvoreDecrescente(atual->arvoreEnergia);
              return;
       }
	atual = atual->proximo;
     }
}


void imprimirAlimento(Alimento temp){
   
   printf("%d, ", temp.numero);
   printf("%s, ", temp.descricao);
   printf("KCAL: %d, ", temp.energia);
   printf("PROTEINA: %f, ", temp.proteina);
   printf("%s\n", categoriaParaString(temp.categoria));
   
}

void imprimirAlimentoNodo(AlimentoNodo* nodo){ imprimirAlimento(nodo->alimento);}

void imprimirCategorias(){
	
	printf("-------LISTANDO CATEGORIAS-------\n");
	
	Categoria* atual = Categorias;
	
	while(atual != NULL){
	   const char* categoria = categoriaParaString(atual->categoria);
	   printf("%s\n", categoria);

	   atual = atual->proximo;
	}
	
	printf("------------------------------\n");
}

void listarAlimentosPorCategoria() {

    int escolha = mostrarMenuCategorias();
    Categoria* atual = Categorias;
    int indice = 1;

    while (atual != NULL) {
        if (indice == escolha) {
            printf("Alimentos da categoria %s:\n\n", categoriaParaString(atual->categoria));
            AlimentoNodo* nodo = atual->listaAlimentos;
            while (nodo != NULL) {
                imprimirAlimento(nodo->alimento);
                nodo = nodo->proximo;
            }
            return;
        }
        atual = atual->proximo;
        indice++;
    }
    printf("Categoria não encontrada.\n");
}
 
void listarAlimentosDaCategoria(int escolha) {

    Categoria* atual = Categorias;
    int indice = 1;

    while (atual != NULL) {
        if (indice == escolha) {
            printf("Alimentos da categoria %s:\n\n", categoriaParaString(atual->categoria));
            AlimentoNodo* nodo = atual->listaAlimentos;
            while (nodo != NULL) {
                imprimirAlimento(nodo->alimento);
                nodo = nodo->proximo;
            }
            return;
        }
        atual = atual->proximo;
        indice++;
    }
    printf("Categoria não encontrada.\n");
}
 
    
int mostrarMenuCategorias() {
    printf("Escolha uma categoria:\n");

    int i = 1;
    Categoria* atual = Categorias;
    while (atual != NULL) {
        printf("%d - %s\n", i, categoriaParaString(atual->categoria));
        atual = atual->proximo;
        i++;
    }

    int escolha;
    printf("\nDigite o número da categoria: ");
    scanf("%d", &escolha);

    return escolha; // índice na lista, não no enum
}



void imprimirAlimentoNodos(Categoria* atual){
//pega determinado elemento da lista de categorias, acessa seu atributo listaAlimentos, e para cada AlimentoNodo passa a funcao imprimirAlimentoNodo
	AlimentoNodo* nodo = atual->listaAlimentos;
	
	while(nodo != NULL){
		imprimirAlimentoNodo(nodo);
		nodo = nodo->proximo;
	} 
}

//----------------------------------------------------------------------------------------------------------------------
//				REMOCAO DE CATEGORIAS
//----------------------------------------------------------------------------------------------------------------------


void removerCategoria() {
    int escolha = mostrarMenuCategorias(); // índice escolhido pelo usuário

    Categoria* atual = Categorias;
    Categoria* anterior = NULL;
    int indice = 1;

    while (atual != NULL) {
        if (indice == escolha) {
            // desconectar da lista
            if (anterior == NULL) {
                Categorias = atual->proximo; // removendo a primeira
            } else {
                anterior->proximo = atual->proximo;
            }

            // liberar memória associada
            liberarListaAlimentos(atual->listaAlimentos);
            liberarArvore(atual->arvoreEnergia);
            liberarArvore(atual->arvoreProteina);
            free(atual);
            alteracao = 1;

            printf("Categoria removida com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
        indice++;
    }

    printf("Categoria não encontrada.\n");
}


//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//				REMOCAO DE ALIMENTOS
//----------------------------------------------------------------------------------------------------------------------


void removerAlimento() {
    int escolha = mostrarMenuCategorias(); // índice da categoria
    Categoria* atual = Categorias;
    int indice = 1;
    listarAlimentosDaCategoria(escolha);
    while (atual != NULL) {
        if (indice == escolha) {
            char descricao[100];
            printf("Digite a descrição do alimento a remover: ");
            scanf(" %[^\n]", descricao);

            removerAlimentoLista(&atual->listaAlimentos, descricao);
            reconstruirArvores(atual);
            alteracao = 1;

            printf("Alimento removido com sucesso.\n");
            return;
        }
        atual = atual->proximo;
        indice++;
    }

    printf("Categoria não encontrada.\n");
}


void reconstruirArvores(Categoria* categoria) {
	
    liberarArvore(categoria->arvoreEnergia);
    liberarArvore(categoria->arvoreProteina);
    
    categoria->arvoreEnergia = NULL;
    categoria->arvoreProteina = NULL;

    AlimentoNodo* nodo = categoria->listaAlimentos;
    while (nodo != NULL) {
        // energia
        ArvoreNodo* ETNode = malloc(sizeof(*ETNode));
        ETNode->alimento = nodo->alimento;
        ETNode->esquerdo = ETNode->direito = NULL;
        inserirEnergia(&categoria->arvoreEnergia, ETNode);

        // proteína
        ArvoreNodo* PTNode = malloc(sizeof(*PTNode));
        PTNode->alimento = nodo->alimento;
        PTNode->esquerdo = PTNode->direito = NULL;
        inserirProteina(&categoria->arvoreProteina, PTNode);

        nodo = nodo->proximo;
    }
}


void removerAlimentoLista(AlimentoNodo** lista, const char* descricao) {
    AlimentoNodo* atual = *lista;
    AlimentoNodo* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->alimento.descricao, descricao) == 0) {
            if (anterior == NULL) {
                *lista = atual->proximo; 
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
		//PERSISTENCIA DE DADOS EM CASO DE REMOCOES
//----------------------------------------------------------------------------------------------------------------------

void salvarDados() {
    FILE* arquivo = fopen(caminhoArquivo, "wb");
    if (!arquivo) {
        perror("Erro ao abrir arquivo para escrita");
        exit(EXIT_FAILURE);
    }

    Categoria* cat = Categorias;
    while (cat != NULL) {
        AlimentoNodo* nodo = cat->listaAlimentos;
        while (nodo != NULL) {
            fwrite(&nodo->alimento, sizeof(Alimento), 1, arquivo);
            nodo = nodo->proximo;
        }
        cat = cat->proximo;
    }

    fclose(arquivo);
}
//----------------------------------------------------------------------------------------------------------------------
			//LIBERAR MEMORIA
//----------------------------------------------------------------------------------------------------------------------

void liberarCategorias() {
    Categoria* atual = Categorias;
    while (atual != NULL) {
        Categoria* temp = atual;
        atual = atual->proximo;

        liberarListaAlimentos(temp->listaAlimentos);
        liberarArvore(temp->arvoreEnergia);
        liberarArvore(temp->arvoreProteina);
        free(temp);
    }
    Categorias = NULL; 
}

void liberarListaAlimentos(AlimentoNodo* lista) {
    while (lista != NULL) {
        AlimentoNodo* temp = lista;
        lista = lista->proximo;
        free(temp);
    }
}

void liberarArvore(ArvoreNodo* raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esquerdo);
    liberarArvore(raiz->direito);
    free(raiz);
}


//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
		//INTERFACE
//----------------------------------------------------------------------------------------------------------------------

void mostrarMenuPrincipal() {
    printf("\n");
    printf("\n===== MENU PRINCIPAL =====\n");
    printf("1 - Listar categorias de alimentos\n");
    printf("2 - Listar alimentos por categoria\n");
    printf("3 - Listar alimentos em ordem decrescente de energia\n");
    printf("4 - Listar alimentos em ordem decrescente de proteína\n");
    printf("5 - Listar alimentos por intervalo de energia\n");
    printf("6 - Listar alimentos por intervalo de proteína\n");
    printf("7 - Remover categoria\n");
    printf("8 - Remover alimento\n");
    printf("9 - Encerrar execução\n");
    printf("==========================\n");
    printf("Escolha uma opção: ");

}

void executarInterface() {
    int executando = 1;

    while (executando == 1) {
        mostrarMenuPrincipal();
        int opcao;
        scanf("%d", &opcao);

        if (opcao == 1) {
            imprimirCategorias();
        } else if (opcao == 2) {
            listarAlimentosPorCategoria();
        } else if (opcao == 3) {
            imprimirArvoreEnergia();
        } else if (opcao == 4) {
            imprimirArvoreProteina();
        } else if (opcao == 5) {
            listarIntervaloEnergia();
        } else if (opcao == 6) {
            listarIntervaloProteina();
        } else if (opcao == 7) {
            removerCategoria();
        } else if (opcao == 8) {
            removerAlimento();
        } else if (opcao == 9) {
            executando = 0;
        } else {
            printf("Opção inválida.\n");
        }
    }
	
		
   if (alteracao){
    salvarDados();
    printf("Arquivo atualizado salvo em alimentos.bin.\n");
    }
    // antes de sair, liberar memória
    liberarCategorias();
    printf("Programa encerrado.\n");
}

