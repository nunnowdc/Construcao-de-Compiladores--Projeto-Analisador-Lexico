#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Função para verificar se o caractere está presente na lista de caracteres especiais
int buscaCaractere(char caractere, char lista[], int tamanho_lista) {
    for (int i = 0; i < tamanho_lista; i++) {
        if (caractere == lista[i]) {
            return 1;  // O caractere está na lista
        }
    }
    return 0;  // O caractere não está na lista
}

// Função para verificar se uma palavra está presente na lista de palavras reservadas
int buscaPalavra(char *palavra, char *lista[], int tamanho_lista) {
    for (int i = 0; i < tamanho_lista; i++) {
        if (strcmp(palavra, lista[i]) == 0) {
            return 1;  // A palavra está na lista
        }
    }
    return 0;  // A palavra não está na lista
}

// Função para verificar se o caractere é um operador de comparação
int buscaComparador(char *possivel_comparador, char *lista[], int tamanho_lista) {
    for (int i = 0; i < tamanho_lista; i++) {
        if (strcmp(possivel_comparador, lista[i]) == 0) {
            return 1;  // O comparador está na lista
        }
    }
    return 0;  // O comparador não está na lista
}

// Função para verificar se a palavra é um número
int is_number(char *palavra, int *is_decimal) {
    int has_dot = 0;
    if (palavra[0] == '\0') { // String vazia não é um número
        return 0;
    } 
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (isdigit((unsigned char)palavra[i])) {
            continue; // Se for dígito, continua
        } 
        else if (palavra[i] == '.' && !has_dot) {
            has_dot = 1; // Encontrou um ponto decimal
        } 
        else {
            return 0; // Não é um número
        }
    }
    *is_decimal = has_dot; // Define se é decimal(1) ou nao(0)
    return 1;
}

// Função para buscar um símbolo na tabela de símbolos
int find_symbol(char **symbol_table, int symbol_count, char *symbol) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i], symbol) == 0) {
            return i + 1; // Retorna índice 1-based
        }
    }
    return -1;  // Se não achar, retorna -1
}

// Função para adicionar um símbolo à tabela de símbolos
int add_symbol(char ***symbol_table, int *symbol_count, char *symbol) {
    *symbol_table = realloc(*symbol_table, (*symbol_count + 1) * sizeof(char *));
    if (*symbol_table == NULL) {
        printf("Erro de alocação de memória para a tabela de símbolos.\n");
        exit(1);  // Encerra o programa por inteiro se ocorrer erro na realocação
    }
    (*symbol_table)[*symbol_count] = strdup(symbol); // strdup reserva espaço/memoria para uma string específica
    if ((*symbol_table)[*symbol_count] == NULL) {
        printf("Erro de alocação de memória para o símbolo.\n");
        exit(1);  // Encerra o programa por inteiro caso nao tenha memoria suficiente para o simbolo novo
    }
    (*symbol_count)++;
    return *symbol_count; // Retorna índice 
}

// Função para adicionar um token à lista de tokens
int add_token(char ***lista_tokens, int *tamanho_lista_tokens, const char *token_entry) {
    *lista_tokens = realloc(*lista_tokens, (*tamanho_lista_tokens + 1) * sizeof(char *));
    if (*lista_tokens == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }
    (*lista_tokens)[*tamanho_lista_tokens] = strdup(token_entry); // strdup reserva espaço/memoria para uma string específica
    (*tamanho_lista_tokens)++;
    return *tamanho_lista_tokens; // Retorna o novo tamanho
}

int main() {
    FILE *arquivo;
    int caractere;  // Usar int para armazenar EOF corretamente
    char char_especiais[] = {'=', '+', '-', '*', '/', '%', '!', '(', ')', '{', '}', '[', ']', ',', ';', '.', '#', '@', '$'};
    int tamanho_lista_char_especiais = sizeof(char_especiais) / sizeof(char_especiais[0]);

    // Lista de palavras reservadas
    char *palavras_reservadas[] = {"int", "float", "char", "boolean", "void", "if", "else", "for", "while", "scanf", "printf", "main", "return"};
    int tamanho_lista_palavras_reservadas = sizeof(palavras_reservadas) / sizeof(palavras_reservadas[0]);

    // Lista de operadores de comparação
    char *vetor_comp[] = {">=", "<=", "==", "!=", ">", "<"};
    int tamanho_lista_comp = sizeof(vetor_comp) / sizeof(vetor_comp[0]);

    // Ponteiros para armazenar tokens e símbolos dinamicamente
    char **lista_tokens = NULL;
    char **symbol_table = NULL;
    int symbol_count = 0;
    char palavra_buffer[256];
    int indice_palavra = 0;

    // Contadores de ID, NUM, TEXTO e COMP
    int ID_counter = 1;
    int COMP_counter = 1;

    // Tamanhos dinâmicos para os arrays
    int tamanho_lista_tokens = 0;

    // Abrindo o arquivo em modo de leitura
    arquivo = fopen("index.c", "r");

    // Verificando se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Variáveis para controlar comentários de bloco
    int dentro_comentario_bloco = 0;

    // Lendo os caracteres do arquivo um por um
    while ((caractere = fgetc(arquivo)) != EOF) {
        // Verifica se estamos dentro de um comentário de bloco
        if (dentro_comentario_bloco) {
            if (caractere == '*') {  
                int proximo_caractere = fgetc(arquivo);
                if (proximo_caractere == '/') {
                    dentro_comentario_bloco = 0;  // Saímos do comentário de bloco
                } else {
                    ungetc(proximo_caractere, arquivo);  // Devolve o caractere se não for '/'
                }
            }
            continue;  // Ignora caracteres dentro do comentário de bloco
        }

        // Verifica se encontramos o início de um comentário
        if (caractere == '/') {
            int proximo_caractere = fgetc(arquivo);
            if (proximo_caractere == '/') {
                // Ignora até o fim da linha (comentário de uma linha)
                while ((caractere = fgetc(arquivo)) != '\n' && caractere != EOF);
                continue; // Continue com a próxima iteração
            } else if (proximo_caractere == '*') {
                // Início de comentário de bloco
                dentro_comentario_bloco = 1;
                continue; // Continue com a próxima iteração
            } else {
                ungetc(proximo_caractere, arquivo);  // Devolve o caractere lido
            }
        }

        // Verifica se encontramos '<'
        if (caractere == '<') {
            char menor_que[] = "<";
            char token_entry[50];
            snprintf(token_entry, sizeof(token_entry), "(COMP, %d) ", COMP_counter++);
            add_token(&lista_tokens, &tamanho_lista_tokens, token_entry);
            if (find_symbol(symbol_table, symbol_count, menor_que) == -1) {
                add_symbol(&symbol_table, &symbol_count, menor_que);
            }
            int prox_caractere;
            if ((prox_caractere = fgetc(arquivo)) != ' ' && prox_caractere != EOF && prox_caractere != '>') {
                // Inicializa o buffer e adiciona o primeiro caractere após o '<'
                char ID_buffer[256];
                int indice_id = 0;
                ID_buffer[indice_id++] = prox_caractere;  // Adiciona o primeiro caractere
                
                // Continua lendo até encontrar '>'
                while ((caractere = fgetc(arquivo)) != EOF && caractere != '>') {
                    if (indice_id < 255) {
                        ID_buffer[indice_id++] = caractere;
                    }
                }
                ID_buffer[indice_id] = '\0';  // Termina a string

                // Adiciona como identificador (ID)
                snprintf(token_entry, sizeof(token_entry), "(ID, %d) ", ID_counter++);
                add_token(&lista_tokens, &tamanho_lista_tokens, token_entry);

                if (find_symbol(symbol_table, symbol_count, ID_buffer) == -1) {
                    add_symbol(&symbol_table, &symbol_count, ID_buffer);
                }

                // Adiciona '>' como comparador
                char maior_que[] = ">";
                snprintf(token_entry, sizeof(token_entry), "(COMP, %d) ", COMP_counter++);
                add_token(&lista_tokens, &tamanho_lista_tokens, token_entry);

                if (find_symbol(symbol_table, symbol_count, maior_que) == -1) {
                    add_symbol(&symbol_table, &symbol_count, maior_que);
                }
            }
            continue;  // Não processa mais o caractere após '>'
        }

        // Verifica se o caractere é uma letra, dígito ou '_' (parte de uma palavra)
        if (isalnum(caractere) || caractere == '_') {
            // Adiciona o caractere ao buffer da palavra
            if (indice_palavra < 255) {
                palavra_buffer[indice_palavra++] = caractere;
            }
        } 

        else if (caractere == '"') {  // Verifica se é o início ou fim de um texto entre aspas
            char texto_buffer[256];
            int indice_texto = 0;
            // Continua até encontrar o fechamento da aspa
            while ((caractere = fgetc(arquivo)) != EOF && caractere != '"') {
                if (indice_texto < 255) { // Previne overflow
                    texto_buffer[indice_texto++] = caractere;
                }
            }
            texto_buffer[indice_texto] = '\0';  // Adiciona o terminador nulo

            // Adiciona as aspas ao texto para a tabela de símbolos
            char texto_com_aspas[258];
            snprintf(texto_com_aspas, sizeof(texto_com_aspas), "\"%s\"", texto_buffer);

            // Formata o token de texto
            char token_entry[50];
            snprintf(token_entry, sizeof(token_entry), "(TEXTO, %s)", texto_com_aspas);
            add_token(&lista_tokens, &tamanho_lista_tokens, token_entry);

            continue; // Continue para não processar mais este caractere

        } 

        else if (caractere == '.' && indice_palavra > 0 && isdigit(palavra_buffer[indice_palavra-1])) {
            // Se encontramos um ponto logo após um número, verificamos se é um decimal
            palavra_buffer[indice_palavra++] = caractere;  // Adiciona o ponto ao buffer
            // Continua lendo após o ponto para verificar se são dígitos
            while ((caractere = fgetc(arquivo)) != EOF && isdigit(caractere)) {
                if (indice_palavra < 255) {
                    palavra_buffer[indice_palavra++] = caractere;  // Adiciona os dígitos após o ponto
                }
            }
            palavra_buffer[indice_palavra] = '\0';  // Termina a palavra

            // Verifica se o número completo é um número decimal
            char token_entry[50];
            snprintf(token_entry, sizeof(token_entry), "(NUM_DEC, %s) ", palavra_buffer); // formatar uma string e guardar o resultado em um array
            add_token(&lista_tokens, &tamanho_lista_tokens, token_entry);

            // Limpa o buffer
            indice_palavra = 0;
            ungetc(caractere, arquivo);  // Devolve o caractere para não perder processamento
        }
        else {
            // Se não for letra nem dígito, terminamos a palavra
            if (indice_palavra > 0) {
                palavra_buffer[indice_palavra] = '\0';  // Adiciona o terminador nulo

                // Verifica se é uma palavra reservada
                if (buscaPalavra(palavra_buffer, palavras_reservadas, tamanho_lista_palavras_reservadas)) {
                    // É uma palavra reservada, adiciona à lista de tokens
                    char token_entry[50];
                    snprintf(token_entry, sizeof(token_entry), "%s ", palavra_buffer); // formatar uma string e guardar o resultado em um array
                    add_token(&lista_tokens, &tamanho_lista_tokens, token_entry);

                } else {
                    int decimal = 0;
                    // Verifica se é um número
                    if (is_number(palavra_buffer, &decimal)) {
                        if (decimal == 1) {
                            // Adiciona número decimal
                            char token_entry[50];
                            snprintf(token_entry, sizeof(token_entry), "(NUM_DEC, %s) ", palavra_buffer); // formatar uma string e guardar o resultado em um array
                            add_token(&lista_tokens, &tamanho_lista_tokens, token_entry);

                        } else {
                            // Adiciona número inteiro
                            char token_entry[50];
                            snprintf(token_entry, sizeof(token_entry), "(NUM_INT, %s) ", palavra_buffer); // formatar uma string e guardar o resultado em um array
                            add_token(&lista_tokens, &tamanho_lista_tokens, token_entry);

                        }

                    } else {
                        // Adiciona como identificador (ID)
                        char token_entry[50];
                        snprintf(token_entry, sizeof(token_entry), "(ID, %d) ", ID_counter++); // formatar uma string e guardar o resultado em um array
                        add_token(&lista_tokens, &tamanho_lista_tokens, token_entry);

                        // Adiciona o número inteiro à tabela de símbolos
                        if (find_symbol(symbol_table, symbol_count, palavra_buffer) == -1) {
                            add_symbol(&symbol_table, &symbol_count, palavra_buffer);
                        }

                    }
                }

                // Limpa o buffer
                indice_palavra = 0;
            }
            // Verifica se o caractere é um operador de comparação
            char possivel_comp[3] = {caractere, '\0', '\0'};
            if ((caractere == '>' || caractere == '<' || caractere == '=' || caractere == '!')) {
                // Verifica se é um operador de dois caracteres
                int proximo_caractere = fgetc(arquivo);
                if (proximo_caractere == '=') {
                    possivel_comp[1] = proximo_caractere;  // Operador composto (>=, <=, ==, !=)
                } 
                else {
                    ungetc(proximo_caractere, arquivo);  // Devolve o caractere se não for '='
                }
            }

            // Verifica se o símbolo encontrado é um operador de comparação
            if (buscaComparador(possivel_comp, vetor_comp, tamanho_lista_comp)) {
                // Formata "(COMP,n)" e incrementa o contador
                char token_entry[50];
                snprintf(token_entry, sizeof(token_entry), "(COMP, %d) ", COMP_counter++); // formatar uma string e guardar o resultado em um array
                add_token(&lista_tokens, &tamanho_lista_tokens, token_entry);

                // Adiciona o operador de comparação à tabela de símbolos
                if (find_symbol(symbol_table, symbol_count, possivel_comp) == -1) {
                    add_symbol(&symbol_table, &symbol_count, possivel_comp);
                }
            }
            // Verifica se o caractere é um caractere especial
            else if (buscaCaractere(caractere, char_especiais, tamanho_lista_char_especiais)) {
                // Verifica se o caractere é um dos especiais a serem tratados como (ID, count)
                if (caractere == '.' || caractere == '#' || caractere == '@' || caractere == '$') {
                    // Formata "(ID,n)" e incrementa o contador
                    char token_entry[50];
                    snprintf(token_entry, sizeof(token_entry), "(ID, %d) ", ID_counter++); // formatar uma string e guardar o resultado em um array
                    add_token(&lista_tokens, &tamanho_lista_tokens, token_entry);

                    // Adiciona o caractere à tabela de símbolos
                    char simbolo[2] = {caractere, '\0'};
                    if (find_symbol(symbol_table, symbol_count, simbolo) == -1) {
                        add_symbol(&symbol_table, &symbol_count, simbolo);
                    }
                } else {
                    // Formata '%c' para caracteres especiais não tratados como (ID, count)
                    char token_entry[50];
                    snprintf(token_entry, sizeof(token_entry), "%c ", caractere); // formatar uma string e guardar o resultado em um array
                    add_token(&lista_tokens, &tamanho_lista_tokens, token_entry);
                }
            }

            int proximo_caractere = fgetc(arquivo);
            if ((caractere == '&' && proximo_caractere == '&') || (caractere == '|' && proximo_caractere == '|')) {
                // Adiciona os operadores lógicos à lista de tokens
                char token_entry[50];
                snprintf(token_entry, sizeof(token_entry), "%c%c ", caractere, proximo_caractere); // formatar uma string e guardar o resultado em um array
                add_token(&lista_tokens, &tamanho_lista_tokens, token_entry);
            }
            
            else {
                ungetc(proximo_caractere, arquivo);  // Devolve o caractere se não for o esperado
            }

            if ((caractere == '&' && proximo_caractere != '&') || (caractere == '|' && proximo_caractere != '|')) {
                
                // Adiciona o caractere à tabela de símbolos
                char simbolo[2] = {caractere, '\0'};
                if (find_symbol(symbol_table, symbol_count, simbolo) == -1) {
                    add_symbol(&symbol_table, &symbol_count, simbolo);
                }
                char token_entry[50];
                snprintf(token_entry, sizeof(token_entry), "(ID, %d) ", ID_counter++); // formatar uma string e guardar o resultado em um array
                add_token(&lista_tokens, &tamanho_lista_tokens, token_entry);
            }
        }
    }

    // Fechando o arquivo
    fclose(arquivo);

    // Imprime a lista de tokens gerada
    printf("Lista de Tokens:\n");
    for (int i = 0; i < tamanho_lista_tokens; i++) {
        printf("%s ", lista_tokens[i]);
    }

    printf("\n");
    
    // Imprime a tabela de símbolos
    printf("\nTabela de Simbolos:\n");
    for (int i = 0; i < symbol_count; i++) {
        printf("%s\n", symbol_table[i]);  // Removido o índice
    }

    // Liberar memória alocada
    for (int i = 0; i < tamanho_lista_tokens; i++) {
        free(lista_tokens[i]);
    }
    free(lista_tokens);

    for (int i = 0; i < symbol_count; i++) {
        free(symbol_table[i]);
    }
    free(symbol_table);

    return 0;
}
