#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "gerarBin.h"

//Realiza a leitura do numero de linhas para defincao do tamanho do vetor de Alimento

void lerNumeroLinhas(int* total_linhas, const char *nome_arquivo){

   FILE* arquivo; char linha[256]; *total_linhas = 0; 
   
   arquivo = fopen(nome_arquivo, "r");
   if (!arquivo){ printf("ERRO AO ABRIR O ARQUIVO %s\n", nome_arquivo); return;}
   
   printf("Lendo número de linhas do arquivo...\n");
   
   while(fgets(linha, sizeof(linha), arquivo)){
   
   (*total_linhas)++; 
   
   }printf("%d Linhas lidas.\n", *total_linhas); fclose(arquivo);

}

// Abre e lê o arquivo texto com os dados dos alimentos e armazena em um vetor de Alimento

void carregarTxt(Alimento alimentos[], int *total_alimentos, const char *nome_arquivo){

   FILE* arquivo; char linha[256]; *total_alimentos = 0;
   
   arquivo = fopen(nome_arquivo, "r");
   if (!arquivo){ perror("ERRO AO ABRIR O ARQUIVO"); exit(EXIT_FAILURE);}
   
   printf("Lendo arquivo...\n");
   
   while(fgets(linha, sizeof(linha), arquivo)){
   
   linha[strcspn(linha, "\n")] = 0;
   
   char* token;
   
   token = strtok(linha, DELIMITADOR);
   if(token != NULL){ alimentos[*total_alimentos].numero = atoi(token);}
   
   token = strtok(NULL, DELIMITADOR);
   if(token != NULL){ strcpy(alimentos[*total_alimentos].descricao, token);}
   
   token = strtok(NULL, DELIMITADOR);
   if(token != NULL){ alimentos[*total_alimentos].energia = atoi(token);}
   
   token = strtok(NULL, DELIMITADOR);
   if(token != NULL){ alimentos[*total_alimentos].proteina = atof(token);}
   
   token = strtok(NULL, DELIMITADOR);
   if(token != NULL){ alimentos[*total_alimentos].categoria = stringParaCategoria(token);}
   
   (*total_alimentos)++;
   
   }
   printf("%d Alimentos carregados!\n", *total_alimentos);
   fclose(arquivo);
  
}

//Recebe o vetor de Alimento lido e salva em formato binario

void salvarBin(Alimento alimentos[], int* total_alimentos){

   printf("Salvando em arquivo binário...\n");
   FILE *bin = fopen("alimentos.bin", "wb");
   int i;
   for (i = 0; i < *total_alimentos; i++) { fwrite(&alimentos[i], sizeof(Alimento), 1, bin);}
   fclose(bin);
   printf("%d Alimentos salvos em arquivo binário com sucesso.\n", i);

}

//Converter string do arquivo texto para enum Categoria

Categoria stringParaCategoria(const char* str){
    if (strcmp(str, "Cereais e derivados") == 0) return CEREAIS;
    if (strcmp(str, "Verduras, hortaliças e derivados") == 0) return VERDURAS;
    if (strcmp(str, "Frutas e derivados") == 0) return FRUTAS;
    if (strcmp(str, "Gorduras e óleos") == 0) return GORDURAS;
    if (strcmp(str, "Pescados e frutos do mar") == 0) return PESCADOS;
    if (strcmp(str, "Carnes e derivados") == 0) return CARNES;
    if (strcmp(str, "Leite e derivados") == 0) return LEITE;
    if (strcmp(str, "Bebidas (alcoólicas e não alcoólicas)") == 0) return BEBIDAS;
    if (strcmp(str, "Ovos e derivados") == 0) return OVOS;
    if (strcmp(str, "Produtos açucarados") == 0) return ACUCARADOS;
    if (strcmp(str, "Miscelâneas") == 0) return MISC;
    if (strcmp(str, "Outros alimentos industrializados") == 0) return INDUSTRIALIZADOS;
    if (strcmp(str, "Alimentos preparados") == 0) return PREPARADOS;
    if (strcmp(str, "Leguminosas e derivados") == 0) return LEGUMINOSAS;
    if (strcmp(str, "Nozes e sementes") == 0) return NOZES;
    return CATEGORIA_INVALIDA;
}




