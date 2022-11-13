#include <stdio.h>
#include "feistel.h"

int main() {
    int inicializado = 0;
    int funcoes[32][256] = {0};
    int numero_de_rodadas;

    char comando;

    while(scanf(" %c", &comando) != EOF) {
        if(comando == 'I') {
            printf("Inicialização...\n");

            int tamanho_da_chave;
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
        } else if(comando ==  'C') {
            printf("Cifragem...\n");

            if(inicializado == 1) {
                int plaintext[32], texto_cifrado[32];
                
                for(int i = 0; i < 32; i++) {
                    scanf("%d", &plaintext[i]);

                    if(plaintext[i] < 0 || plaintext[i] > 255) {
                        printf("E\n");
                        return 0;
                    }
                }

                cifra(plaintext, texto_cifrado, funcoes, numero_de_rodadas);

                printf("\n");

                for(int i = 0; i < 32; i++) {
                    printf("%d ", texto_cifrado[i]);
                }

                printf("\n");
            } else {
                printf("E\n");
                return 0;
            }
        }
    }

    return 0;
}