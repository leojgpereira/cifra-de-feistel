/* Permutação inicial A (rodada de número par) */
int P_A[] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 128, 130, 132, 134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 166, 168, 170, 172, 174, 176, 178, 180, 182, 184, 186, 188, 190, 192, 194, 196, 198, 200, 202, 204, 206, 208, 210, 212, 214, 216, 218, 220, 222, 224, 226, 228, 230, 232, 234, 236, 238, 240, 242, 244, 246, 248, 250, 252, 254, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 128, 130, 132, 134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 166, 168, 170, 172, 174, 176, 178, 180, 182, 184, 186, 188, 190, 192, 194, 196, 198, 200, 202, 204, 206, 208, 210, 212, 214, 216, 218, 220, 222, 224, 226, 228, 230, 232, 234, 236, 238, 240, 242, 244, 246, 248, 250, 252, 254};

/* Permutação inicial B (rodada de número ímpar) */
int P_B[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65, 67, 69, 71, 73, 75, 77, 79, 81, 83, 85, 87, 89, 91, 93, 95, 97, 99, 101, 103, 105, 107, 109, 111, 113, 115, 117, 119, 121, 123, 125, 127, 129, 131, 133, 135, 137, 139, 141, 143, 145, 147, 149, 151, 153, 155, 157, 159, 161, 163, 165, 167, 169, 171, 173, 175, 177, 179, 181, 183, 185, 187, 189, 191, 193, 195, 197, 199, 201, 203, 205, 207, 209, 211, 213, 215, 217, 219, 221, 223, 225, 227, 229, 231, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65, 67, 69, 71, 73, 75, 77, 79, 81, 83, 85, 87, 89, 91, 93, 95, 97, 99, 101, 103, 105, 107, 109, 111, 113, 115, 117, 119, 121, 123, 125, 127, 129, 131, 133, 135, 137, 139, 141, 143, 145, 147, 149, 151, 153, 155, 157, 159, 161, 163, 165, 167, 169, 171, 173, 175, 177, 179, 181, 183, 185, 187, 189, 191, 193, 195, 197, 199, 201, 203, 205, 207, 209, 211, 213, 215, 217, 219, 221, 223, 225, 227, 229, 231, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255};

/* T guardará a chave da rodada (repetição da chave informada na inicialização) */
/* S guardará a função de uma rodada */
int S[256], T[256];

/* Função para trocar dois inteiros de posição */
void troca(int* a, int* b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

/* Função para rotacionar a chave um número exato de vezes */
void rotaciona_chave(int numero_de_rotacoes, int chave[], int tamanho_da_chave, int nova_chave[]) {
    /* Copia a chave para um novo vetor */
    for(int i = 0; i < tamanho_da_chave; i++) {
        nova_chave[i] = chave[i];
    }

    for(int i = 0; i < numero_de_rotacoes; i++) {
        /* Guarda o último byte da chave (representado pelo último inteiro do vetor) */
        int aux = nova_chave[tamanho_da_chave - 1];

        /* Puxa todos os inteiros (do primeiro ao penúltimo elemento) do vetor uma posição para a direita */
        for(int j = tamanho_da_chave - 1; j > 0; j--) {
            nova_chave[j] = nova_chave[j-1];
        }

        /* Coloca o último elemento do vetor na primeira posição do vetor */
        nova_chave[0] = aux;
    }
}

/* Gera a função de uma rodada da rede de feistel */
void computa_funcao_da_rodada(int rodada, int chave[], int tamanho_da_chave, int funcoes[32][256]) {
    /* Verifica se a rodada é par */
    if(rodada % 2 == 0) {
        /* Copia a permutação inicial A para o vetor S */
        for(int i = 0; i < 256; i++) {
            S[i] = P_A[i];
        }
    } else {
        /* Copia a permutação inicial B para o vetor S */
        for(int i = 0; i < 256; i++) {
            S[i] = P_B[i];
        }
    }

    /* Calcula o número de rotações da chave para uma determinada rodada */
    int numero_de_rotacoes = rodada / 2;
    int nova_chave[tamanho_da_chave];

    /* Rotaciona a chave */
    rotaciona_chave(numero_de_rotacoes, chave, tamanho_da_chave, nova_chave);

    /* Repete a chave da rodada já rotacionada até completar 256 posições */ 
    for(int i = 0; i < 256; i++) {
        T[i] = nova_chave[i % tamanho_da_chave];
    }

    int j = 0;
    
    /* Calcula a função com base na descrição do trabalho */
    for(int i = 0; i < 256; i++) {
        j = (j + S[i] + T[i]) % 256;
        troca(&S[i], &S[j]);
    }

    /* Copia a função resultante de S para a matriz que guarda as funções das rodadas */
    for(int i = 0; i < 256; i++) {
        funcoes[rodada][i] = S[i];
    }
}

/* Função responsável por cifrar um texto claro fornecido */
void cifra(int plaintext[], int texto_cifrado[], int funcoes[32][256], int numero_de_rodadas) {
    /* E = Parte que entrará na esquerda do bloco */
    /* D = Parte que entrará na direita do bloco */
    /* CE = Texto cifrado parcial resultante do lado esquerdo do bloco */
    /* CD = Texto cifrado parcial resultante do lado direito do bloco */
    int E[16], D[16], CE[16], CD[16];

    /* Copia para E o lado esquerdo do texto claro */
    for(int i = 0; i < 16; i++) {
        E[i] = plaintext[i];
    }

    /* Copia para D o lado direito do texto claro */
    for(int i = 0; i < 16; i++) {
        D[i] = plaintext[i+16];
    }

    for(int i = 0; i < numero_de_rodadas; i = i + 2) {
        /* Computa e guarda o texto cifrado parcial esquerdo após duas rodadas */
        for(int j = 0; j < 16; j++) {
            CE[j] = E[j] ^ funcoes[i][D[j]];
        }

        /* Computa e guarda o texto cifrado parcial direito após duas rodadas */
        for(int j = 0; j < 16; j++) {
            CD[j] = D[j] ^ funcoes[i+1][CE[j]];
        }

        /* Copia o texto cifrado parcial esquerdo para o vetor E (para dar continuidade as rodadas seguintes) */
        for(int j = 0; j < 16; j++) {
            E[j] = CE[j];
        }

        /* Copia o texto cifrado parcial direito para o vetor D (para dar continuidade as rodadas seguintes) */
        for(int j = 0; j < 16; j++) {
            D[j] = CD[j];
        }
    }

    /* Após todas as rodadas, guarda o texto cifrado final invertendo os textos cifrados parciais esquerdo e direito */
    for(int i = 0; i < 16; i++) {
        texto_cifrado[i] = D[i];
    }

    for(int i = 0; i < 16; i++) {
        texto_cifrado[i+16] = E[i];
    }
}

/* Função responsável por decifrar um texto cifrado fornecido */
void decifra(int texto_cifrado[], int plaintext[], int funcoes[32][256], int numero_de_rodadas) {
    /* E = Parte que entrará na esquerda do bloco */
    /* D = Parte que entrará na direita do bloco */
    /* DE = Texto decifrado parcial resultante do lado esquerdo do bloco */
    /* DD = Texto decifrado parcial resultante do lado direito do bloco */
    int E[16], D[16], DE[16], DD[16];

    /* Copia para E o lado esquerdo do texto claro */
    for(int i = 0; i < 16; i++) {
        E[i] = texto_cifrado[i];
    }

    /* Copia para D o lado direito do texto claro */
    for(int i = 0; i < 16; i++) {
        D[i] = texto_cifrado[i+16];
    }

    for(int i = numero_de_rodadas; i > 0; i = i - 2) {
        /* Computa e guarda o texto decifrado parcial esquerdo após duas rodadas, começando da função da última rodada até a função da primeira rodada */
        for(int j = 0; j < 16; j++) {
            DE[j] = E[j] ^ funcoes[i-1][D[j]];
        }

        /* Computa e guarda o texto decifrado parcial direito após duas rodadas, começando da função da última rodada até a função da primeira rodada */
        for(int j = 0; j < 16; j++) {
            DD[j] = D[j] ^ funcoes[i-2][DE[j]];
        }

        /* Copia o texto decifrado parcial esquerdo para o vetor E (para dar continuidade as rodadas seguintes) */
        for(int j = 0; j < 16; j++) {
            E[j] = DE[j];
        }

        /* Copia o texto decifrado parcial direito para o vetor D (para dar continuidade as rodadas seguintes) */
        for(int j = 0; j < 16; j++) {
            D[j] = DD[j];
        }
    }

    /* Após todas as rodadas, guarda o texto decifrado final invertendo os textos decifrados parciais esquerdo e direito */
    for(int i = 0; i < 16; i++) {
        plaintext[i] = D[i];
    }

    for(int i = 0; i < 16; i++) {
        plaintext[i+16] = E[i];
    }
}