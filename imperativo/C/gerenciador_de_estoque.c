#include <stdio.h>
#include <ctype.h>
#include <string.h>

   struct Produto { 
       char nome [100];
       char codigo [7];
       char cor [50];
       char fornecedor [100];
       int dia_lancamento, mes_lancamento, ano_lancamento;
       float preco;
       int quantidade;
   };




int nome_valido(char nome[]) { 
    nome[strcspn(nome, "\n")] = '\0'; 
    int tamanho_nome = strlen(nome);
    if (tamanho_nome == 0 || tamanho_nome > 100) return 0; 
    int caractere_valido = 0;

    for (int i = 0; nome[i] != '\0'; i++) { 
        char a = nome[i];
        if (isalpha(a) || a == ' ' || a == '-' || a == '\'' || isdigit(a)) {
            caractere_valido++;
        }
        else { 
            return 0;
        }
    }

    if (caractere_valido >= 4) { 
        return 1;
    }
    else { 
        return 0;
    }
}

   
int codigo_valido(char codigo[]) { 
    codigo[strcspn(codigo, "\n")] = '\0';

    if (strlen(codigo) != 6) { 
        return 0;
    }

    for (int i = 0; i < 6; i++) { 
        if (!isdigit(codigo[i])) {
            return 0;
        }
    }
    return 1;
}


int cor_valida(char cor[]) { 
    cor[strcspn(cor, "\n")] = '\0';
    int tamanho_cor = strlen(cor);
    if (tamanho_cor == 0 || tamanho_cor > 50) return 0; 

    for (int i = 0; cor[i] != '\0'; i++) { 
        char a = cor[i];
        if (!(isalpha(a) || a == ' ' || a == '-')) {
            return 0;
        }
    }

    if (tamanho_cor >= 3) {
        return 1;
    }
    else {
        return 0;
    }
}


int fornecedor_valido(char fornecedor[]) {
    fornecedor[strcspn(fornecedor, "\n")] = '\0'; 
    int tamanho_fornecedor = strlen(fornecedor);
    if (tamanho_fornecedor == 0 || tamanho_fornecedor > 100) return 0; 
    int caractere_valido = 0, tem_espaco = 0;

    for (int i = 0; fornecedor[i] != '\0'; i++) { 
        char a = fornecedor[i];
        if (isalpha(a) || a == ' ' || a == '-' || a == '\'') {
            caractere_valido++;

            if (a == ' ') { 
                tem_espaco = 1;
            }
        }
        else { 
            return 0;
        }
    }

    if (caractere_valido >= 4 && tem_espaco != 0) {
        return 1;
    }
    else { 
        return 0;
    }
}

  
int data_valida(int dia, int mes, int ano) { 
    if (dia < 1 || dia > 31) return 0; 
    if (mes < 1 || mes > 12) return 0; 
    if (ano < 1000 || ano > 2026) return 0; 
    return 1;
}

   
int preco_valido(float preco) { 
    if (preco <= 0 || preco > 99999) return 0; 
    return 1;
}

   
int quantidade_valida(int quantidade) { 
    if (quantidade < 0 || quantidade > 99999) return 0; 
    return 1;
}

   
int codigo_cadastrado_antes(struct Produto lista[], int qnt, char codigo[]) {
    for (int i = 0; i < qnt; i++) {
        if (strcmp(lista[i].codigo, codigo) == 0) { 
            return i;
        }
    }
    return -1;
}






void cadastrar_produto(struct Produto estoque[], int *qnt) { 
    if (*qnt >= 1000) { 
        printf("Limite de cadastros atingido! \n");
        return;
    }

    printf("Para realizar o cadastro do seu produto, digite:\n");
    char codigo_testar[7];
    int resposta = -1, atualizar, pos = *qnt;

   
    do {
        printf("Codigo do produto (6 digitos): "); 
        fgets(codigo_testar, sizeof(codigo_testar), stdin);
        codigo_testar[strcspn(codigo_testar, "\n")] = '\0';
        while (getchar() != '\n');

        if (!codigo_valido(codigo_testar)) { 
            printf("Esse codigo nao e valido. Digite novamente.\n");
            continue;
        }

        resposta = codigo_cadastrado_antes(estoque, *qnt, codigo_testar); 
        if (resposta != -1) {
            printf("Esse codigo ja esta cadastrado.\nDeseja atualizar os dados desse produto? (Escolha o numero que corresponde a opcao) \n1-SIM\n2-NAO ");
            scanf("%d", &atualizar);
            while (getchar() != '\n');
            if (atualizar == 1) { 
                pos = resposta;
                break;
            }
            else { 
                return;
            }
        }
        else { 
            pos = *qnt;
            strcpy(estoque[pos].codigo, codigo_testar);
            break;
        }
    } while (!codigo_valido(estoque[pos].codigo));

   
    do {
        printf("Nome do produto: "); 
        fgets(estoque[pos].nome, sizeof(estoque[pos].nome), stdin);
        if (!nome_valido(estoque[pos].nome)) { 
            printf("Esse nome nao e valido. Digite novamente.\n");
        }
    } while (!nome_valido(estoque[pos].nome));

   
    do {
        printf("Cor do gloss: "); 
        fgets(estoque[pos].cor, sizeof(estoque[pos].cor), stdin);
        if (!cor_valida(estoque[pos].cor)) { 
            printf("Essa cor nao e valida. Digite novamente.\n");
        }
    } while (!cor_valida(estoque[pos].cor));

   
    do {
        printf("Fornecedor (Nome e Sobrenome/Empresa): "); 
        fgets(estoque[pos].fornecedor, sizeof(estoque[pos].fornecedor), stdin);
        if (!fornecedor_valido(estoque[pos].fornecedor)) { 
            printf("Esse fornecedor nao e valido. Digite novamente.\n");
        }
    } while (!fornecedor_valido(estoque[pos].fornecedor));

   
    do {
        printf("Data de lancamento (dia/mes/ano): "); 
        scanf("%d/%d/%d", &estoque[pos].dia_lancamento, &estoque[pos].mes_lancamento, &estoque[pos].ano_lancamento);
        while (getchar() != '\n');
        if (!data_valida(estoque[pos].dia_lancamento, estoque[pos].mes_lancamento, estoque[pos].ano_lancamento)) { 
            printf("Essa data nao e valida. Digite novamente.\n");
        }
    } while (!data_valida(estoque[pos].dia_lancamento, estoque[pos].mes_lancamento, estoque[pos].ano_lancamento));

   
    do {
        printf("Preco do produto (ex: 29.90): R$ "); 
        scanf("%f", &estoque[pos].preco);
        while (getchar() != '\n');
        if (!preco_valido(estoque[pos].preco)) { 
            printf("Esse preco nao e valido. Digite novamente.\n");
        }
    } while (!preco_valido(estoque[pos].preco));

   
    do {
        printf("Quantidade em estoque: "); 
        scanf("%d", &estoque[pos].quantidade);
        while (getchar() != '\n');
        if (!quantidade_valida(estoque[pos].quantidade)) { 
            printf("Essa quantidade nao e valida. Digite novamente.\n");
        }
    } while (!quantidade_valida(estoque[pos].quantidade));

    if (resposta == -1) { 
        (*qnt)++;
    }
}

void chamar_cadastro(struct Produto estoque[], int *qnt) { 
    int chamar = 1;
    while (chamar == 1 && *qnt < 1000) { 
        cadastrar_produto(estoque, qnt);
        if (*qnt >= 1000) {
            printf("Limite do cadastro ja foi atingido! \n");
            break;
        }
        printf("Deseja cadastrar outro produto? (Escolha o numero que corresponde a opcao)\n1-SIM\n2-NAO\n"); 
        scanf("%d", &chamar);
        while (getchar() != '\n'); 
    }
}






void busca_codigo(struct Produto lista[], int *qnt) { 
    char codigo_buscar[7];
    int codigo_achado = -1; 
    printf("Digite o codigo do produto que voce deseja buscar: "); 
    fgets(codigo_buscar, sizeof(codigo_buscar), stdin);
    codigo_buscar[strcspn(codigo_buscar, "\n")] = '\0';
    while (getchar() != '\n');

    for (int i = 0; i < *qnt; i++) {
        if (strcmp(lista[i].codigo, codigo_buscar) == 0) {
            codigo_achado = i;
            break;
        }
    }
    if (codigo_achado != -1) { 
        printf("O codigo foi encontrado! \nDados do produto:\nNome: %s\nCor: %s\nFornecedor: %s\nData de lancamento: %d/%d/%d\nPreco: R$ %.2f\nQuantidade em estoque: %d\n",
            lista[codigo_achado].nome,
            lista[codigo_achado].cor,
            lista[codigo_achado].fornecedor,
            lista[codigo_achado].dia_lancamento,
            lista[codigo_achado].mes_lancamento,
            lista[codigo_achado].ano_lancamento,
            lista[codigo_achado].preco,
            lista[codigo_achado].quantidade);
    }
    else { 
        printf("Esse codigo nao possui cadastro no nosso estoque! Se desejar cadastra-lo, digite 1 no nosso menu!\n");
    }
}







void troca(struct Produto lista[], int pos1, int pos2) { 
    struct Produto p = lista[pos1];
    lista[pos1] = lista[pos2];
    lista[pos2] = p;
}

void selection_sort(struct Produto lista[], int quantidade, int mes_ordenar) { 
    for (int i = 0; i < quantidade; i++) { 
        if (lista[i].mes_lancamento != mes_ordenar) {
            continue;
        }

        int min = i;
        for (int j = i + 1; j < quantidade; j++) { 
            if (lista[j].mes_lancamento != mes_ordenar) {
                continue;
            }

            if (lista[j].dia_lancamento < lista[min].dia_lancamento) { 
                min = j;
            }
        }
        troca(lista, i, min); 
    }
}

void produto_mes_lancamento(struct Produto lista[], int *qnt) { 
    struct Produto lancamentos[*qnt]; 
    int quantidade = 0, mes_busca;
    printf("Digite o mes que voce deseja buscar: ");
    scanf("%d", &mes_busca);
    while (getchar() != '\n');
    for (int i = 0; i < *qnt; i++) { 
        if (lista[i].mes_lancamento == mes_busca) {
            lancamentos[quantidade] = lista[i];
            quantidade++;
        }
    }
    selection_sort(lancamentos, quantidade, mes_busca); 
    if (quantidade == 0) { 
        printf("Nenhum produto foi lancado no mes %d.\n", mes_busca);
    }
    else { 
        printf("Quantidade de produtos lancados no mes %d: %d produtos:\n", mes_busca, quantidade);
        for (int a = 0; a < quantidade; a++) {
            printf("\n- DIA DE LANCAMENTO: %d \nDADOS: %s | %s | %s | R$ %.2f | Estoque: %d unidades",
                lancamentos[a].dia_lancamento,
                lancamentos[a].nome,
                lancamentos[a].codigo,
                lancamentos[a].cor,
                lancamentos[a].preco,
                lancamentos[a].quantidade);
        }
        printf("\n");
    }
}






void aplicar_desconto(struct Produto lista[], int *qnt) { 
    char codigo_buscar[7];
    int codigo_achado = -1;
    printf("Digite o codigo do produto que deseja aplicar o desconto: ");
    fgets(codigo_buscar, sizeof(codigo_buscar), stdin);
    codigo_buscar[strcspn(codigo_buscar, "\n")] = '\0';
    while (getchar() != '\n');

    for (int i = 0; i < *qnt; i++) { 
        if (strcmp(lista[i].codigo, codigo_buscar) == 0) {
            codigo_achado = i;
            break;
        }
    }

    if (codigo_achado == -1) { 
        printf("Esse codigo nao possui cadastro no nosso estoque!\n");
        return;
    }

    printf("Produto encontrado: %s\nPreco atual: R$ %.2f\n", lista[codigo_achado].nome, lista[codigo_achado].preco);

    int percentual;
    do {
        printf("Digite o percentual de desconto que deseja aplicar (1 a 99): "); 
        scanf("%d", &percentual);
        while (getchar() != '\n');
        if (percentual < 1 || percentual > 99) { 
            printf("Percentual invalido. Digite um valor entre 1 e 99.\n");
        }
    } while (percentual < 1 || percentual > 99);

    float preco_antigo = lista[codigo_achado].preco; 
    lista[codigo_achado].preco = preco_antigo * (1.0 - percentual / 100.0); 

    printf("Desconto de %d%% aplicado com sucesso!\nPreco anterior: R$ %.2f\nNovo preco: R$ %.2f\n",
        percentual, preco_antigo, lista[codigo_achado].preco);
}








void atualizar_estoque(struct Produto lista[], int *qnt) { 
    char codigo_buscar[7];
    int codigo_achado = -1;
    printf("Digite o codigo do produto que deseja atualizar o estoque: ");
    fgets(codigo_buscar, sizeof(codigo_buscar), stdin);
    codigo_buscar[strcspn(codigo_buscar, "\n")] = '\0';
    while (getchar() != '\n');

    for (int i = 0; i < *qnt; i++) { 
        if (strcmp(lista[i].codigo, codigo_buscar) == 0) {
            codigo_achado = i;
            break;
        }
    }

    if (codigo_achado == -1) { 
        printf("Esse codigo nao possui cadastro no nosso estoque!\n");
        return;
    }

    printf("Produto encontrado: %s\nQuantidade atual em estoque: %d unidades\n", lista[codigo_achado].nome, lista[codigo_achado].quantidade);

    int tipo;
    do {
        printf("O que deseja fazer?\n1-Entrada (adicionar unidades)\n2-Saida (retirar unidades)\n"); 
        scanf("%d", &tipo);
        while (getchar() != '\n');
        if (tipo != 1 && tipo != 2) { 
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (tipo != 1 && tipo != 2);

    int unidades;
    do {
        printf("Digite a quantidade de unidades: "); 
        scanf("%d", &unidades);
        while (getchar() != '\n');
        if (unidades <= 0 || unidades > 99999) { 
            printf("Quantidade invalida. Digite novamente.\n");
        }
    } while (unidades <= 0 || unidades > 99999);

    int qtd_antiga = lista[codigo_achado].quantidade; 

    if (tipo == 1) { 
        lista[codigo_achado].quantidade = qtd_antiga + unidades;
        printf("Entrada registrada com sucesso!\nQuantidade anterior: %d unidades\nNova quantidade: %d unidades\n",
            qtd_antiga, lista[codigo_achado].quantidade);
    }
    else { 
        if (unidades > qtd_antiga) { 
            printf("Quantidade insuficiente em estoque! Nao e possivel retirar %d unidades de um estoque com %d.\n", unidades, qtd_antiga);
            return;
        }
        lista[codigo_achado].quantidade = qtd_antiga - unidades;
        printf("Saida registrada com sucesso!\nQuantidade anterior: %d unidades\nNova quantidade: %d unidades\n",
            qtd_antiga, lista[codigo_achado].quantidade);
    }
}





int main() {
    struct Produto Estoque[1000]; 
    int opcao, qnt = 0;
    do {
        printf("\n=======================================================\n"); 
        printf("             LOJA DE GLOSS\n");
        printf("       Brilhando e facilitando sua vida <3!!!\n");
        printf("=======================================================\n"); 
        printf("1 - Cadastrar produto\n");
        printf("2 - Buscar produto por codigo\n");
        printf("3 - Buscar produto por mes de lancamento\n");
        printf("4 - Aplicar desconto em produto\n");
        printf("5 - Atualizar estoque de produto\n");
        printf("0 - Fechar\n");
        printf("-------------------------------------------------------\n"); 
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        while (getchar() != '\n');
        switch (opcao) { 
            case 1:
                chamar_cadastro(Estoque, &qnt);
                break;
            case 2:
                busca_codigo(Estoque, &qnt);
                break;
            case 3:
                produto_mes_lancamento(Estoque, &qnt);
                break;
            case 4:
                aplicar_desconto(Estoque, &qnt);
                break;
            case 5:
                atualizar_estoque(Estoque, &qnt);
                break;
            case 0:
                printf("Volte sempre que precisar!");
                break;
            default:
                printf("Opcao invalida! Tente novamente!");
        }
    } while (opcao != 0);
    return 0;
}
