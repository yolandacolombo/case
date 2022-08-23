#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//Define a estrutura da pessoa, com nome e idade
typedef struct{
    char nome[100];
    int idade;
}Pessoa;

void ler_frase(char* frase, int tamanho_maximo)
{
    int i;
    do
    {
        fgets(frase, tamanho_maximo, stdin);
        for (i = 0; i < tamanho_maximo && frase[i] != '\0'; i++)
        {
            if ( frase[i] == '\n' )
            {
                frase[i] = '\0';
                break;
            }
        }
    } while ( i == 0 );
}

//Solicita as informações da pessoa
Pessoa ler_pessoa()
{
    Pessoa pes;
    printf("\nNome: ");
    ler_frase(pes.nome, 100);

    printf("Idade: ");
    scanf("%d", &pes.idade);

    return pes;
};

//Função que imprime por categoaria as pessoas cadastradas
void imprime(Pessoa *pes, int qtd_pessoas){
    int opcao, contador = 0;
    int j;

    printf("\nEscolha a opção que deseja imprimir:\n");
    printf("1 - Todos.\n");
    printf("2 - Crianças (0 a 12 anos). \n");
    printf("3 - Adolescentes (13 a 19 anos).\n");
    printf("4 - Adultos (20 65 anos).\n");
    printf("5 - Idosos (mais de 65 anos).\n");
    printf("\n");

    printf("== Digite a sua escolha: ");
    scanf("%d", &opcao);

    switch (opcao){ // os cases 2, 3, 4 e 5 verificam e informam se nenhuma pessoa daquela categora já foi adicionada
    case 1:
        for(j=0; j < qtd_pessoas; j++){
            printf("\nNome: %s\tIdade: %d", pes[j].nome, pes[j].idade);
        }
        break;

    case 2:
        contador = 0;

        for(j=0; j < qtd_pessoas; j++){
            if (pes[j].idade <= 12){
                printf("\nNome: %s\tIdade: %d", pes[j].nome, pes[j].idade);
                contador = 1;
            }
        }
        if (contador == 0){
            printf("\n== Nenhuma criança foi adicionada ainda.\n");
        }

        break;

    case 3:
        contador = 0;

        for(j=0; j < qtd_pessoas; j++){
            if (pes[j].idade >= 13 && pes[j].idade < 20){
                printf("\nNome: %s\tIdade: %d", pes[j].nome, pes[j].idade);
                contador = 1;
            }
        }
        if (contador == 0){
            printf("\n== Nenhum adolescente foi adicionado ainda.\n");
        }

    break;

    case 4:
        contador = 0;

        for(j=0; j < qtd_pessoas; j++){
            if (pes[j].idade >= 20 && pes[j].idade < 65){
                printf("\nNome: %s\tIdade: %d", pes[j].nome, pes[j].idade);
                contador = 1;
            }
        }
        if (contador == 0){
            printf("\n== Nenhum adulto foi adicionado ainda.\n");
        }

        break;

    case 5:
        contador = 0;

        for(j=0; j < qtd_pessoas; j++){
            if (pes[j].idade >= 65){
                printf("\nNome: %s\tIdade: %d", pes[j].nome, pes[j].idade);
                contador = 1;
            }
        }
        if (contador == 0){
            printf("\n== Nenhum idoso foi adicionado ainda.\n");
        }

        break;

    default:
        printf("\n== Essa opção não está disponível.\n");
        break;
    }

}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int escolha, j, k;
    int qtd_pessoas = 0, i = 0;

    Pessoa pessoas[100], menor;

    do{
        printf("\nEscolha o número de uma das opcões abaixo:\n");
        printf("1 - Adicionar uma pessoa nova.\n");
        printf("2 - Exibir lista de pessoas cadastradas por ordem de idade. \n");
        printf("3 - Exibir lista de pessoas cadastradas por ordem alfabética.\n");
        printf("0 - Finalizar.\n");
        printf("\n");

        printf("== Digite a sua escolha: ");
        scanf("%d", &escolha);

        printf("\n");

        switch (escolha){
        case 1: // No case 1 se adiciona novas pessoas, ele verifica se a idade que o usuário está informando é compatível com a realidade
            i = qtd_pessoas;
            qtd_pessoas = qtd_pessoas + 1;

            printf("\n== Entre com os dados da pessoa.");

            pessoas[i] = ler_pessoa();

            while(pessoas[i].idade < 0 || pessoas[i].idade > 130){
                printf("\n== Idade inválida! Adicione a pessoa novamente.\n");
                pessoas[i] = ler_pessoa();
            }

            break;

        case 2: // O case 2 é para imprimir a lista de pessoas cadastradas por ordem de idade, do mais novo para o mais velho
                // ele verifica se já tem pessoas cadastradas
            if (qtd_pessoas == 0){
                printf("\n== Nenhuma pessoa foi adicionada ainda.\n");

                break;
            }

            else{
                for(j=0; j < qtd_pessoas; j++){
                    for(k=j+1; k < qtd_pessoas; k++){
                        if(pessoas[j].idade > pessoas[k].idade){
                            menor = pessoas[k];
                            pessoas[k] = pessoas[j];
                            pessoas[j] = menor;
                        }
                    }
                }

                imprime(pessoas, qtd_pessoas);

                break;
            }

        case 3: // o case 3 imprime as pessoas cadastradas por ordem alfabética
                // também verifica se já tem pessoas cadastradas
            if (qtd_pessoas == 0){
                printf("\n== Nenhuma pessoa foi adicionada ainda.\n");

                break;
            }

            else{
                for(j=0; j < qtd_pessoas; j++){
                    for(k=j+1; k < qtd_pessoas; k++){
                        if(strcmp(pessoas[j].nome, pessoas[k].nome) == 1){
                            menor = pessoas[k];
                            pessoas[k] = pessoas[j];
                            pessoas[j] = menor;
                        }
                    }
                }
            imprime(pessoas, qtd_pessoas);

            break;
            }

        case 0:
            break;

        default: // se o usuário digitar alguma opção diferente das permitidas, avisamos ele para escolher outra
            printf("\n== Essa opção não está disponível, escolha outra.\n");
        }

    }while(escolha != 0); // tudo está dentro de um looping para que o programa não acabe na primera escolha do usuário

    return 0;
}
