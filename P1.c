#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "gerarBin.h"


int main(){

   setlocale(LC_ALL, "pt_BR.UTF-8");
   
   int total_alimentos = 0;   int total_linhas = 0;

   lerNumeroLinhas(&total_linhas, "alimentos.csv");
   
   Alimento alimentos[total_linhas];
   
   carregarTxt(alimentos, &total_alimentos, "alimentos.csv");
   
   salvarBin(alimentos, &total_alimentos);
   
   
   

return 0;}
