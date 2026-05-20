#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Paciente {
    char nome[101];
    int gravidade;
    struct Paciente *prox;
} Paciente;

Paciente *head = NULL;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inserirPaciente(char nome[], int gravidade) {
    Paciente *novo = (Paciente*) malloc(sizeof(Paciente));
    strcpy(novo->nome, nome);
    novo->gravidade = gravidade;
    novo->prox = NULL;

    if (head == NULL) {
        head = novo;
        return;
    }

    if (gravidade < head->gravidade) {
        novo->prox = head;
        head = novo;
        return;
    }

    Paciente *atual = head;
    while (atual->prox != NULL && atual->prox->gravidade <= gravidade) {
        atual = atual->prox;
    }
    novo->prox = atual->prox;
    atual->prox = novo;
}

void chamarPaciente() {
    if (head == NULL) {
        printf("\nFila vazia.\n\n");
        return;
    }

    Paciente *temp = head;
    printf("\nChamando paciente: %s\n", temp->nome);
    printf("Prioridade: %d\n\n", temp->gravidade);
    head = head->prox;
    free(temp);
}

void mostrarFila() {
    if (head == NULL) {
        printf("\nFila vazia.\n\n");
        return;
    }

    Paciente *atual = head;
    printf("\n===== FILA =====\n");
    while (atual != NULL) {
        printf("%s - prioridade %d\n", atual->nome, atual->gravidade);
        atual = atual->prox;
    }
    printf("================\n\n");
}

int main() {
    int opcao;

    do {
        printf("1 - Novo paciente\n");
        printf("2 - Chamar paciente\n");
        printf("3 - Mostrar fila\n");
        printf("0 - Sair\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: {
                char nome[101];
                int gravidade;

                printf("\nNome do paciente: ");
                fgets(nome, 101, stdin);

                if (strchr(nome, '\n') != NULL) {
                    nome[strcspn(nome, "\n")] = '\0';
                } else {
                    limparBuffer();
                }

                printf("\nPrioridade:\n");
                printf("1 - Vermelho\n");
                printf("2 - Laranja\n");
                printf("3 - Amarelo\n");
                printf("4 - Verde\n");
                printf("5 - Azul\n");
                printf("Escolha: ");
                scanf("%d", &gravidade);
                limparBuffer();

                inserirPaciente(nome, gravidade);
                printf("\nPaciente inserido com sucesso.\n\n");
                break;
            }

            case 2:
                chamarPaciente();
                break;

            case 3:
                mostrarFila();
                break;

            case 0:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\nOpcao invalida.\n\n");
        }
    } while (opcao != 0);

    return 0;
}