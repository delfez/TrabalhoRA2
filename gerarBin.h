#ifndef GERARBIN_H
#define GERARBIN_H

#define DELIMITADOR ";"

typedef enum{

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

} Categoria;

typedef struct
{
    int numero;
    char descricao[100];
    int energia;
    double proteina;
    Categoria categoria;

} Alimento;

void carregarTxt(Alimento alimentos[], int *total_alimentos, const char *nome_arquivo);
void lerNumeroLinhas(int* total_linhas, const char *nome_arquivo);
void salvarBin(Alimento alimentos[], int* total_alimentos);
Categoria stringParaCategoria(const char* str);

#endif
