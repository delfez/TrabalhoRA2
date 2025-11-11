#ifndef GERARBIN_H
#define GERARBIN_H

#define DELIMITADOR ";"

typedef enum CategoriaAlimento CategoriaAlimento;
typedef struct Alimento Alimento;

 enum CategoriaAlimento{

    CEREAIS,
    VERDURAS,
    FRUTAS,
    GORDURAS,
    PESCADOS,
    CARNES,
    LEITE,
    BEBIDAS,
    OVOS,
    ACUCARADOS,
    MISC,
    INDUSTRIALIZADOS,
    PREPARADOS,
    LEGUMINOSAS,
    NOZES,
    CATEGORIA_INVALIDA

} ;

struct Alimento{
    int numero;
    char descricao[100];
    int energia;
    double proteina;
    CategoriaAlimento categoria;

} ;

void carregarTxt(Alimento alimentos[], int *total_alimentos, const char *nome_arquivo);
void lerNumeroLinhas(int* total_linhas, const char *nome_arquivo);
void salvarBin(Alimento alimentos[], int* total_alimentos);
CategoriaAlimento stringParaCategoria(const char* str);


#endif
