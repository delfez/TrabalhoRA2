#ifndef LERBIN_H
#define LERBIN_H

typedef struct Categoria Categoria;
typedef struct AlimentoNodo AlimentoNodo;

 struct Categoria{

   CategoriaAlimento categoria;
   AlimentoNodo* listaAlimentos;
   Categoria* proximo;

};

 struct AlimentoNodo{

   Alimento alimento;
   AlimentoNodo* proximo;

};

extern Categoria* Categorias;


const char* categoriaParaString(CategoriaAlimento categoria);
void lerBin(const char* nome_arquivo);
void imprimirAlimentoNodo(AlimentoNodo* nodo);
void imprimirAlimento(Alimento temp);
void inserirCategoria(AlimentoNodo* novo);
void inserirAlimentoNodo(AlimentoNodo** lista, AlimentoNodo* novo);
void imprimirCategorias();


#endif
