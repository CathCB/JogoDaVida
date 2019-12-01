#include <stdio.h>
#define TAMANHO 100
#define LARGURA 100
#define vida_sim 1
#define vida_nao 0

int tam_mundo, qtd_geracao;

typedef int tipoTabela [TAMANHO][LARGURA];


void printtabela(tipoTabela tabela, int bichinho) {
    int tamanho, largura;

   printf("  ");
    for (tamanho = 0;tamanho<tam_mundo;tamanho++){
        printf("%d ", tamanho);
    }
    printf("\n");

    for (tamanho = 0; tamanho < tam_mundo; tamanho++) {
        printf("%d", tamanho);
        for (largura = 0; largura < tam_mundo; largura++) {
            if (tabela[tamanho][largura] == vida_sim && bichinho==1) {
                printf(" #");
            } else if (tabela[tamanho][largura] == vida_sim && bichinho==2){
                printf(" *");
            } else {
		    printf("  ");
	    }
        }
        printf("\n");
    }
    printf("\n");
}


void limpartabela (tipoTabela tabela) {
	int tamanho, largura;
	for (tamanho = 0; tamanho < tam_mundo; tamanho++) {
		for (largura = 0; largura < tam_mundo; largura++) {
			tabela[tamanho][largura] = vida_nao;
		}
	}
}

int define_tam_mundo(){
    printf("Defina o tamanho do seu mundo (min. 50, max. 100): \n");
	scanf ("%d", &tam_mundo);
        while((tam_mundo<10)||(tam_mundo>100)){
		printf ("Tamanho invalido, digite novamente: \n");
		scanf ("%d", &tam_mundo);
		}
    return tam_mundo;
}
int perguntarusuario(tipoTabela tabelaA) {
	int i;
	int qtd_organismo;
	int tamanho, largura;

	printf("\nQuantas geracoes deseja simular? ");
	scanf("%d", &qtd_geracao);
	printf("Quantos organismos deseja? ");
	scanf("%d", &qtd_organismo);
	for (i = 0; i <qtd_organismo; i++) {
		printf("Escolha o local (x y) para o organismo %d: ", i + 1);
		scanf("%d %d", &tamanho, &largura);
		tabelaA[tamanho][largura] = vida_sim;
	}
	return qtd_geracao;
}

int formato_bichinho(){
        int bichinho;

        printf("Qual formato deseja? Digite 1 para # ou 2 para * ");
        scanf("%d", &bichinho);

return bichinho;

}


int valordevizinho(tipoTabela tabela, int lin, int col) {
	if (lin < 0 || lin >= tam_mundo
		|| col < 0 || col >= tam_mundo
		|| tabela[lin][col] != vida_sim )
	{
		return 0;
	} else {
		return 1;
	}
}


int contarvizinho (tipoTabela tabela, int lin, int col) {
	int vizinho = 0;

	vizinho += valordevizinho(tabela, lin - 1, col - 1);
	vizinho += valordevizinho(tabela, lin - 1, col);
	vizinho += valordevizinho(tabela, lin - 1, col + 1);
	vizinho += valordevizinho(tabela, lin, col - 1);
	vizinho += valordevizinho(tabela, lin, col + 1);
	vizinho += valordevizinho(tabela, lin + 1, col - 1);
	vizinho += valordevizinho(tabela, lin + 1, col);
	vizinho += valordevizinho(tabela, lin + 1, col + 1);

	return vizinho;
}

void calcular(tipoTabela tabelaA) {
	tipoTabela tabelaB;
	int vizinho, tamanho, largura;

	for (tamanho = 0; tamanho < tam_mundo; tamanho++) {
		for (largura = 0; largura < tam_mundo; largura++) {
			vizinho = contarvizinho(tabelaA, tamanho, largura);

			if (vizinho==3) {
				tabelaB[tamanho][largura] = vida_sim;
			} else if (vizinho == 2 && tabelaA[tamanho][largura] == vida_sim) {
				tabelaB[tamanho][largura] = vida_sim;
			} else {
				tabelaB[tamanho][largura] = vida_nao;
			}
		}
	}

	for (tamanho = 0; tamanho < tam_mundo; tamanho++) {
		for (largura = 0; largura < tam_mundo; largura++) {
			tabelaA[tamanho][largura] = tabelaB[tamanho][largura];
		}
	}
}

int main(void) {
	tipoTabela tabela;
	char opcao;
	int geracao = 0;
	int contador = 1;
	int bichinho;

    define_tam_mundo();
    limpartabela(tabela);
    perguntarusuario(tabela);
    bichinho = formato_bichinho();
    printf("Seu mundo se encontra assim:\n");
	printtabela(tabela, bichinho);
    do {
       calcular(tabela);
       printf("Geracao %d\n", ++geracao);
       printtabela(tabela, bichinho);
       contador++;
   } while (contador<=qtd_geracao) ;
   return 0;
}
