#include <stdio.h>
#include "feistel.h"

int main() {
    int inicializado = 0;
    int funcoes[32][256] = {0};

    char comando;
    scanf(" %c", &comando);

    if(comando == 'I') {
        printf("Iniciando processo de inicialização...\n");

        int numero_de_rodadas, tamanho_da_chave;
        scanf("%d %d", &numero_de_rodadas, &tamanho_da_chave);

        if(numero_de_rodadas < 2 || numero_de_rodadas > 32 || numero_de_rodadas % 2 != 0) {
            printf("E\n");
            return 0;
        }

        if(tamanho_da_chave < 8 || tamanho_da_chave > 32) {
            printf("E\n");
            return 0;
        }

        int chave[tamanho_da_chave];
        for(int i = 0; i < tamanho_da_chave; i++) {
            scanf("%d", &chave[i]);

            if(chave[i] < 0 || chave[i] > 255) {
                printf("E\n");
                return 0;
            }
        }

        for(int i = 0; i < numero_de_rodadas; i++) {
            computa_funcao_da_rodada(i, chave, tamanho_da_chave, funcoes);
        }

        inicializado = 1;
    } else {
        printf("Algo deu errado!\n");
    }

    return 0;
}