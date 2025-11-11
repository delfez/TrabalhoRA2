#include <stdio.h>
#include <string.h>
#include "gerarBin.h"
#include "lerBin.h"
#include <stdlib.h>
#include <locale.h>

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
   
   AlimentoNodo* n = malloc(sizeof(*n)); 
   if (!n) { perror("malloc"); fclose(arquivo); exit(EXIT_FAILURE); }
   
   n->alimento = temp;
   n->proximo = NULL;
   imprimirAlimentoNodo(*n);
   
   }
   
   if (ferror(arquivo)){ perror("Erro na leitura do arquivo.");}
   
   fclose(arquivo);
}
//Ao ler cada Alimento, criar um AlimentoNodo. Integrar esse Nodo à lista de Categorias. Cada elemento
// da lista de categorias guarda UMA das cateogorias de alimentos, assim como uma lista contendo todos os elementos da categoria em questao. Odenar todas as listas alfabeticamente automaticamente.

void imprimirAlimento(Alimento temp){
   
   printf("%d, ", temp.numero);
   printf("%s, ", temp.descricao);
   printf("KCAL: %d, ", temp.energia);
   printf("PROTEINA: %f, ", temp.proteina);
   printf("%s\n", categoriaParaString(temp.categoria));
   
}

void imprimirAlimentoNodo(AlimentoNodo nodo){

   Alimento alimento = nodo.alimento;
   imprimirAlimento(alimento);
   
   AlimentoNodo* proximo = nodo.proximo;
  
   if (proximo != NULL){
      printf("Proximo: ");
   imprimirAlimento(proximo->alimento);}

}

