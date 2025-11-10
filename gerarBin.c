#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

const char* DELIMITADOR = ";";

typedef struct
{
    int numero;
    char descricao[100];
    int energia;
    double proteina;
    char categoria[80];

} Alimento;

void carregarTxt(Alimento alimentos[], int *total_alimentos, const char *nome_arquivo);
void lerNumeroLinhas(int* total_linhas, const char *nome_arquivo);
void salvarBin(Alimento alimentos[], int* total_alimentos);

int main(){

   setlocale(LC_ALL, "pt_BR.UTF-8");
   
   int total_alimentos = 0;   int total_linhas = 0;

   lerNumeroLinhas(&total_linhas, "alimentos.csv");
   
   Alimento alimentos[total_linhas];
   
   carregarTxt(alimentos, &total_alimentos, "alimentos.csv");
   
   salvarBin(alimentos, &total_alimentos);
   
   
   

return 0;}

void lerNumeroLinhas(int* total_linhas, const char *nome_arquivo){

   FILE* arquivo; char linha[256]; *total_linhas = 0; 
   
   arquivo = fopen(nome_arquivo, "r");
   if (!arquivo){ printf("ERRO AO ABRIR O ARQUIVO %s\n", nome_arquivo); return;}
   
   printf("Lendo número de linhas do arquivo...\n");
   
   while(fgets(linha, sizeof(linha), arquivo)){
   
   (*total_linhas)++; 
   
   }printf("%d Linhas lidas.\n", *total_linhas); fclose(arquivo);

}

void carregarTxt(Alimento alimentos[], int *total_alimentos, const char *nome_arquivo){

   FILE* arquivo; char linha[256]; *total_alimentos = 0;
   
   arquivo = fopen(nome_arquivo, "r");
   if (!arquivo){ printf("ERRO AO ABRIR O ARQUIVO %s\n", nome_arquivo); return;}
   
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
   if(token != NULL){ strcpy(alimentos[*total_alimentos].categoria, token);}
   
   (*total_alimentos)++;
   
   }
   printf("%d Alimentos carregados!\n", *total_alimentos);
   fclose(arquivo);
  
}

void salvarBin(Alimento alimentos[], int* total_alimentos){

   printf("Salvando em arquivo binário...\n");
   FILE *bin = fopen("alimentos.bin", "wb");
   int i;
   for (i = 0; i < *total_alimentos; i++) { fwrite(&alimentos[i], sizeof(Alimento), 1, bin);}
   fclose(bin);
   printf("%d Alimentos salvos em arquivo binário com sucesso.\n", i);

}



