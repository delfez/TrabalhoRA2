#ifndef LERBIN_H
#define LERBIN_H

typedef struct Categoria Categoria;
typedef struct AlimentoNodo AlimentoNodo;
typedef struct ArvoreNodo ArvoreNodo;

 struct Categoria{

   CategoriaAlimento categoria;
   AlimentoNodo* listaAlimentos;
   ArvoreNodo* arvoreProteina;
   ArvoreNodo* arvoreEnergia;
   Categoria* proximo;

};

 struct AlimentoNodo{

   Alimento alimento;
   AlimentoNodo* proximo;

};

struct ArvoreNodo{
	
   Alimento alimento;
   ArvoreNodo* direito;
   ArvoreNodo* esquerdo;

};

extern Categoria* Categorias;
extern int alteracao;


const char* categoriaParaString(CategoriaAlimento categoria);
void lerBin(const char* nome_arquivo);
void imprimirAlimentoNodo(AlimentoNodo* nodo);
void imprimirAlimento(Alimento temp);
void inserirCategoria(AlimentoNodo* novo);
void inserirAlimentoNodo(AlimentoNodo** lista, AlimentoNodo* novo);
void imprimirCategorias();
void imprimirAlimentoNodos(Categoria* atual);
void inserirProteina(ArvoreNodo** raiz, ArvoreNodo* novo);
void inserirEnergia(ArvoreNodo** raiz, ArvoreNodo* novo);
int mostrarMenuCategorias();
void listarAlimentosPorCategoria();
void listarArvoreDecrescente(ArvoreNodo* raiz);
void imprimirArvoreProteina();
void imprimirArvoreEnergia();
void listarIntervaloEnergia();
void listarIntervaloProteina();
void imprimirProteinaIntervalo(ArvoreNodo* raiz, double min, double max);
void imprimirEnergiaIntervalo(ArvoreNodo* raiz, int min, int max);
void liberarArvore(ArvoreNodo* raiz);
void liberarListaAlimentos(AlimentoNodo* lista);
void removerCategoria();
void liberarCategorias();
void executarInterface();
void mostrarMenuPrincipal();
void salvarDados();
void removerAlimentoLista(AlimentoNodo** lista, const char* descricao);
void reconstruirArvores(Categoria* categoria);
void removerAlimento();
void listarAlimentosDaCategoria(int escolha);



#endif
