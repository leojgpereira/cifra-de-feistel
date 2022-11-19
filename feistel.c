#include <stdio.h>
#include "feistel.h"

int main() {
    /* Variável que guarda se o comando de inicialização (I) foi executado -- 0 (não), 1 (sim) */
    int inicializado = 0;

    /* Matriz que guarda as funções computadas para cada rodada */
    int funcoes[32][256] = {0};

    /* Guarda o número de rodadas definido pelo comando de inicializaçãooooo (I) */
    int numero_de_rodadas;

    /* Vetores que guardam o texto claro e o texto cifrado, respectivamente */
    int plaintext[32], texto_cifrado[32];

    /* Guarda o caracter que representa o comando lido da entrada */
    char comando;

    while(scanf(" %c", &comando) != EOF) {
        /* Verifica se é o comando de inicialização (I) */
        if(comando == 'I') {
            /* Lê e guarda o tamanho da chave e o número de rodadas lido da entrada */
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

            /* Lê um vetor de inteiros que representa a chave  */
            int chave[tamanho_da_chave];
            for(int i = 0; i < tamanho_da_chave; i++) {
                scanf("%d", &chave[i]);

                /* Verifica se cada byte da chave está entre 0 e 255. */
                if(chave[i] < 0 || chave[i] > 255) {
                    printf("E\n");
                    return 0;
                }
            }

            /* Computa a função que deve ser utilizada em cada rodada */
            for(int i = 0; i < numero_de_rodadas; i++) {
                computa_funcao_da_rodada(i, chave, tamanho_da_chave, funcoes);
            }

            /* Guarda que a inicialização foi realizada */
            inicializado = 1;

            /* Verifica se é o comando de cifragem (C) */
        } else if(comando ==  'C') {
            /* Verifica se o comando de inicialização (I) foi executado */
            if(inicializado == 1) {

                /* Lê e guarda em um vetor os bytes que representam o texto claro lido da entrada */
                for(int i = 0; i < 32; i++) {
                    scanf("%d", &plaintext[i]);

                    /* Verifica se cada byte do texto claro está entre 0 e 255. */
                    if(plaintext[i] < 0 || plaintext[i] > 255) {
                        printf("E\n");
                        return 0;
                    }
                }

                /* Chama a função que executa a cifragem do texto claro */
                cifra(plaintext, texto_cifrado, funcoes, numero_de_rodadas);
                
                /* Imprime o texto claro cifrado */
                printf("C ");

                for(int i = 0; i < 31; i++) {
                    printf("%d ", texto_cifrado[i]);
                }

                printf("%d", texto_cifrado[31]);

                printf("\n");
            } else {
                printf("E\n");
                return 0;
            }

            /* Verifica se é o comando de decifragem (D) */
        } else if(comando == 'D') {
            /* Verifica se o comando de inicialização (I) foi executado */
            if(inicializado == 1) {

                /* Lê e guarda em um vetor os bytes que representam o texto cifrado lido da entrada */
                for(int i = 0; i < 32; i++) {
                    scanf("%d", &texto_cifrado[i]);

                    /* Verifica se cada byte do texto cifrado está entre 0 e 255. */
                    if(texto_cifrado[i] < 0 || texto_cifrado[i] > 255) {
                        printf("E\n");
                        return 0;
                    }
                }

                /* Chama a função que realiza a decifragem do texto cifrado */
                decifra(texto_cifrado, plaintext, funcoes, numero_de_rodadas);

                /* Imprime o texto claro (decifrado) */
                printf("C ");

                for(int i = 0; i < 31; i++) {
                    printf("%d ", plaintext[i]);
                }

                printf("%d", plaintext[31]);

                printf("\n");
            } else {
                printf("E\n");
                return 0;
            }
        }
    }

    return 0;
}