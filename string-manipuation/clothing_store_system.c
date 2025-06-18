/*
* CLOTHING STORE MANAGEMENT SYSTEM
* 
* GOAL:
* Develop a simple system to control sales for a clothing store that carries
* different types of products (shirts, pants, caps) in various colors and
* with distinct prices.
* 
* MAIN FEATURES:
* 1. Control product inventory (code, description, type, price, quantity)
* 2. Process sales through customer CPF
* 3. Check product availability before sale
* 4. Automatically update inventory after each sale
* 5. Suggest alternative products of the same type when insufficient stock
* 6. Calculate sales totals per product (in currency)
* 7. Calculate sales totals per product type (in units)
* 8. Generate final report with sales summary
* 
* BUSINESS RULES:
* - Each product has unique code, description (color), type and price
* - Sales are only made if there is sufficient stock
* - System suggests alternatives only if they meet the requested quantity
* - Separate control of sales by individual product and by category
* 
* STRUCTURE: Uses only basic C functions, arrays and simple structures
*/

#include <stdio.h>
#include <string.h>
#define TAMPRODUTO 8

int busca(int v[], int n, int val) { //Busca produto
	for (int i=0; i<n; i++) {
		if(v[i]==val)
			return i;
	}
	return -1;

}

int buscaPosTipo(char vTipos[][20], char tipo[], int tamanho) {
	for (int i=0; i<tamanho; i++) { // Para busca no AcumuladorTipo
		if(strcmp(vTipos[i], tipo)==0) {
			return i;
		}
	}
	return -1;
}


void exibeMesmoTipo(int codProduto[], char tipoDesejado[],
                    char tiposProduto[][20], int qtdComprada, int estoque[],
                    int tamanho, char descricao[][20]) {
	for(int i=0; i<tamanho; i++) {
		if(strcmp(tiposProduto[i], tipoDesejado)==0 &&
		        estoque[i]>=qtdComprada) { // devemos conferir que qtdComprada seja ate estoque
			printf("\nO produto %d, com descricao %s, tem %d unidades em estoque",
			       codProduto[i], descricao[i], estoque[i]);
		} else {
			printf("\nNC#o possuimos o estoque suficiente do que esta precisando");
		}
	}
}


void mostrarTotais(int codProduto[], int totalVendidoProduto[],
                   int totalVendidoTipo[], char tipos[][20],
                   int tamanhoEstoque, int tamanhoTipo) {
	//Total estoque (em reais)
	for(int i=0; i<tamanhoEstoque; i++)
		printf("\nO produto %d teve %d reais de vendas",
		       codProduto[i], totalVendidoProduto[i]);
	// Total tipo (em unidades)
	for (int i=0; i<tamanhoTipo; i++)
		printf("\nForama vendidas %d unidades do tipo %s",
		       totalVendidoTipo[i], tipos[i]);
}
int main()
{
	// Criando tabela de estoque
	int vCod[TAMPRODUTO]= {1,2,3,4,5,6,7,8};
	int vQtEstoque[TAMPRODUTO]= {20,20,20,20,20,20,20,20};
	char descricao[TAMPRODUTO][20]= {"vermelho", "azul", "verde", "amarelo", "preto",
	                                 "branco", "rosa", "roxo"
	                                };
	char tipo[TAMPRODUTO][20]= {"camisa", "camisa", "camisa", "calca", "calca", "calca",
	                            "bone", "bone"
	                           };
	int precos[TAMPRODUTO] = {59, 99, 34, 59, 99, 34, 59, 99};
	int totalVendido[TAMPRODUTO]= {0};


	// Acumulador para Tipos AcumuladorTipo
	char vTipos[3][20]= {"camisa", "calca", "bone"};
	int vTotais[3]= {0};

	// Compra
	int cpf, codigo, quantidade, pos;
	char cor;
	printf("Digite o cpf, ou 0 para sair ");
	scanf("%d", &cpf);
	while(cpf!=0) {
		printf("Digite o codigo do produto ");
		scanf("%d", &codigo);
		pos = busca(vCod, TAMPRODUTO, codigo);

		if(pos!=-1) { // Produto existe
			// vender Produto
			printf("\nTem %d em estoque ", vQtEstoque[pos]);
			printf("\nDigitar a quantidade de produto ");
			scanf("%d", &quantidade);

			if(vQtEstoque[pos]>=quantidade) {
				vQtEstoque[pos]-=quantidade; //Diminuir estoque
				totalVendido[pos]+=(quantidade*precos[pos]); //Aumentar o dinheiro

				// Aumentar AcumuladorTipo
				int posTipo;
				posTipo = buscaPosTipo(vTipos, tipo[pos], 3); //Vai procurar o tipo no vetor de tipos
				if(posTipo != -1)
					vTotais[posTipo] += quantidade;

			} else {
				printf("\nNC#o temos estoque suficiente para o produto %d ", codigo);
				printf("\nProdutos alternativos do mesmo tipo (%s) com estoque disponC-vel:", tipo[pos]);
				exibeMesmoTipo(vCod, tipo[pos], tipo, quantidade, vQtEstoque, TAMPRODUTO, descricao);
			}
		} else {
			printf("\nCodigo do produto nao encontrado");
		}
		printf("\nDigite o cpf, ou 0 para sair ");
		scanf("%d", &cpf);
	}

	// Mostrartotais de vendas
	mostrarTotais(vCod, totalVendido, vTotais, vTipos, TAMPRODUTO, 3);

	return 0;
}
