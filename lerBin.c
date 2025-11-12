#include <stdio.h>
#include <string.h>
#include "gerarBin.h"
#include "lerBin.h"
#include <stdlib.h>
#include <locale.h>


Categoria* Categorias = NULL; 

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
	return; 
	}
	//caso a categoria ainda não exista
	
	Categoria* categoria = malloc(sizeof(*categoria));
	if(!categoria){perror("malloc"); exit(EXIT_FAILURE);}
	categoria->categoria = novo->alimento.categoria;
	categoria->listaAlimentos = NULL;
	categoria->proximo = sucessor;
	if (antecessor == NULL){ Categorias = categoria;} //insercao no inicio (antecessor null)
	else{ antecessor->proximo = categoria;}//liga o antecessor ao novo alimento inserido
    	
    	inserirAlimentoNodo(&categoria->listaAlimentos, novo);
    
    }
    
   

void imprimirAlimento(Alimento temp){
   
   printf("%d, ", temp.numero);
   printf("%s, ", temp.descricao);
   printf("KCAL: %d, ", temp.energia);
   printf("PROTEINA: %f, ", temp.proteina);
   printf("%s\n", categoriaParaString(temp.categoria));
   
}

void imprimirAlimentoNodo(AlimentoNodo* nodo){


   imprimirAlimento(nodo->alimento);
  
   if (nodo->proximo != NULL){
      printf("Proximo: ");
   imprimirAlimento(nodo->proximo->alimento);}

}

void imprimirCategorias(){
	
	Categoria* atual = Categorias;
	Categoria* sucessor = atual->proximo;
	
	while(atual != NULL){
	   const char* categoria = categoriaParaString(atual->categoria);
	   printf("%s\n", categoria);
	   atual = atual->proximo;
	}

} 


