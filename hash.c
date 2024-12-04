#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_TABELA 101

typedef struct Contato {
    char nome[50];
    char telefone[20];
    struct Contato* next;
} Contato;

typedef struct {
    Contato* tabela[TAMANHO_TABELA];
} TabelaHash;

unsigned int hash(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash + *str) % TAMANHO_TABELA;
        str++;
    }
    return hash;
}

TabelaHash* criarTabelaHash() {
    TabelaHash* th = (TabelaHash*)malloc(sizeof(TabelaHash));
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        th->tabela[i] = NULL;
    }
    return th;
}

void adicionarContato(TabelaHash* th, const char* nome, const char* telefone) {
    unsigned int indice = hash(nome);
    Contato* novoContato = (Contato*)malloc(sizeof(Contato));
    strcpy(novoContato->nome, nome);
    strcpy(novoContato->telefone, telefone);
    novoContato->next = th->tabela[indice];
    th->tabela[indice] = novoContato;
    printf("Contato adicionado com sucesso.\n");
}

void buscarContato(TabelaHash* th, const char* nome) {
    unsigned int indice = hash(nome);
    Contato* contato = th->tabela[indice];
    clock_t inicio = clock();
    while (contato) {
        if (strcmp(contato->nome, nome) == 0) {
            clock_t fim = clock();
            double tempo = (double)(fim - inicio) * 1000.0 / CLOCKS_PER_SEC;
            printf("Telefone de %s: %s (tempo de busca: %.2f ms)\n", nome, contato->telefone, tempo);
            return;
        }
        contato = contato->next;
    }
    printf("Contato nao encontrado.\n");
}

void removerContato(TabelaHash* th, const char* nome) {
    unsigned int indice = hash(nome);
    Contato* contato = th->tabela[indice];
    Contato* anterior = NULL;

    while (contato) {
        if (strcmp(contato->nome, nome) == 0) {
            if (anterior) {
                anterior->next = contato->next;
            } else {
                th->tabela[indice] = contato->next;
            }
            free(contato);
            printf("Contato removido com sucesso.\n");
            return;
        }
        anterior = contato;
        contato = contato->next;
    }
    printf("Contato nao encontrado.\n");
}

void exibirContatos(TabelaHash* th) {
    printf("Contatos armazenados:\n");
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Contato* contato = th->tabela[i];
        while (contato) {
            printf("Nome: %s, Telefone: %s\n", contato->nome, contato->telefone);
            contato = contato->next;
        }
    }
}

void liberarTabelaHash(TabelaHash* th) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Contato* contato = th->tabela[i];
        while (contato) {
            Contato* temp = contato;
            contato = contato->next;
            free(temp);
        }
    }
    free(th);
}

int main() {
    TabelaHash* th = criarTabelaHash();
    int opcao;
    char nome[50], telefone[20];

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            printf("Nome: ");
            scanf("%s", nome);
            printf("Telefone: ");
            scanf("%s", telefone);
            adicionarContato(th, nome, telefone);
            break;
        case 2:
            printf("Nome: ");
            scanf("%s", nome);
            buscarContato(th, nome);
            break;
        case 3:
            printf("Nome: ");
            scanf("%s", nome);
            removerContato(th, nome);
            break;
        case 4:
            exibirContatos(th);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    liberarTabelaHash(th);
    return 0;
}
