#include <stdio.h>
#include <string.h>
#include "gerarBin.h"
#include "lerBin.h"
#include <stdlib.h>
#include <locale.h>



int main (){

   setlocale(LC_ALL, "pt_BR.UTF-8");
   

   const char* arquivo = "alimentos.bin";
   lerBin(arquivo);


   executarInterface();
	

    

return 0;
}
