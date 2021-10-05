/* Libs */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* Constants */
#define TAMNOME 50
#define TAMSOBRENOME 50
#define NUMALUNOS 1000
#define TAMCURSO 4

/* Types */
typedef struct data {
    int dia, mes, ano;
} data;

typedef struct registro {
    char nome[TAMNOME];
    char sobrenome[TAMSOBRENOME];
    data datadenascimento;
    int prontuario;
    char curso[TAMCURSO];
} aluno;

/* Prototypes */
void menu(bool* ptrLoop, aluno *ptrAlunos, int* nextPosition);
int cadastro(aluno* adrsAlunos, int* adrsNextPosition);
void listarTodos(aluno* adrsAlunos, int maxIndice);
void buscar(aluno* adrsAlunos, int* nextPosition);
void deletar(aluno* adrsAlunos, int* nextPosition, int* adrsEncontrados, int qntEncontrados);
void quicksort(aluno* adrsAlunos, int start, int end, int field);
int partition(aluno* adrsAlunos, int start, int end, int field);
void swap(aluno* alunoA, aluno* alunoB);

/* Functions */
int cadastro (aluno* adrsAlunos, int* adrsNextPosition) {
    /**
     * Verificar campos inseridos
    */

    int nextPosition = *adrsNextPosition;

    if (*adrsNextPosition < NUMALUNOS) {

        char nome[TAMNOME], sobrenome[TAMSOBRENOME], curso[TAMCURSO];
        int dia, mes, ano, prontuario;

        aluno newAluno;

        printf("\n> Nome: ");
        fflush(stdin);
        fgets(nome, TAMNOME, stdin);
        nome[strlen(nome) - 1] = 0;

        printf("> Sobrenome: ");
        fgets(sobrenome, TAMSOBRENOME, stdin);
        fflush(stdin);
        sobrenome[strlen(sobrenome) - 1] = 0;

        printf("> Dia de nascimento: ");
        scanf("%d", &dia);

        printf("> Mes de nascimento: ");
        scanf("%d", &mes);

        printf("> Ano de nascimento: ");
        scanf("%d", &ano);

        printf("> Prontuario: ");
        scanf("%d", &prontuario);

        printf("> Curso: ");
        fflush(stdin);
        fgets(curso, TAMCURSO, stdin);

        for (int i = 0; i < *adrsNextPosition; i++) {
            if (adrsAlunos[i].prontuario == prontuario) {
                printf("\n----- PRONTUARIO JA CADASTRADO -----");
                return 1;
            };
        };

        strcpy(newAluno.nome, nome);
        strcpy(newAluno.sobrenome, sobrenome);
        strcpy(newAluno.curso, curso);
        newAluno.datadenascimento.dia = dia;
        newAluno.datadenascimento.mes = mes;
        newAluno.datadenascimento.ano = ano;
        newAluno.prontuario = prontuario;

        adrsAlunos[nextPosition] = newAluno;

        *adrsNextPosition = nextPosition + 1;
        printf("\n----- Aluno Adicionado -----\n");

    } else {
        printf("\n----- Maximo de alunos atingido -----\n");
    };

    return 0;
};

void listarTodos (aluno* adrsAlunos, int maxIndice) {

    if (maxIndice < 0) {
        printf("\n----- NENHUM ALUNO CADASTRADO -----\n");

    } else {
        printf("\n> Alunos Cadastrados: \n");

        for (int i = 0; i <= maxIndice; i++) {
            printf("\n > Nome e Sobrenome: %s %s", adrsAlunos[i].nome, adrsAlunos[i].sobrenome);
            printf("\n > Nascimento: %i/%i/%i", 
                adrsAlunos[i].datadenascimento.dia, 
                adrsAlunos[i].datadenascimento.mes,
                adrsAlunos[i].datadenascimento.ano);
            printf("\n > Prontuario e Curso: %i - %s\n", adrsAlunos[i].prontuario, adrsAlunos[i].curso);
        };
    };
};

void deletar (aluno* adrsAlunos, int* nextPosition, int* adrsEncontrados, int qntEncontrados) {

    for (int i = 0; i < qntEncontrados; i++) {

        if (adrsEncontrados[i] != (*nextPosition - 1)) {
            adrsAlunos[adrsEncontrados[i]] = adrsAlunos[*nextPosition - 1];
        };

        *nextPosition = (*nextPosition) - 1;
    };
};

void buscar (aluno* adrsAlunos, int* nextPosition) {

    fflush(stdin);

    char campoBuscar;
    int indicesEncontrados[1000];
    int encontrados = 0;

    printf("\n> Buscar por: ");
    printf("\n 1- Nome e Sobrenome");
    printf("\n 2- Nome");
    printf("\n 3- Sobrenome");
    printf("\n 4- Prontuario");
    printf("\n 5- Nascimento");
    printf("\n 6- Curso");

    printf("\n\n > Escolha um campo: ");
    scanf("%c", &campoBuscar);
    fflush(stdin);

    if ((*nextPosition - 1) < 0) {
        printf("\n----- NENHUM ALUNO CADASTRADO -----\n");

    } else {
        char nomeBuscar[TAMNOME];
        char sobrenomeBuscar[TAMSOBRENOME];
        int prontuarioBuscar;
        data nascBuscar;
        char cursoBuscar[TAMCURSO];

        switch (campoBuscar) {
            case '1':
                printf("\nNome: ");
                fgets(nomeBuscar, TAMNOME, stdin);
                nomeBuscar[strlen(nomeBuscar) - 1] = 0;

                printf("\nSobrenome: ");
                fflush(stdin);
                fgets(sobrenomeBuscar, TAMNOME, stdin);
                sobrenomeBuscar[strlen(sobrenomeBuscar) - 1] = 0;

                for (int i = 0; i <= (*nextPosition - 1); i++) {
                    if ((strcmp(adrsAlunos[i].nome, nomeBuscar) == 0) && (strcmp(adrsAlunos[i].sobrenome, sobrenomeBuscar) == 0)) {
                        printf("\n > Nome e Sobrenome: %s %s", adrsAlunos[i].nome, adrsAlunos[i].sobrenome);
                        printf("\n > Nascimento: %i/%i/%i", 
                            adrsAlunos[i].datadenascimento.dia, 
                            adrsAlunos[i].datadenascimento.mes,
                            adrsAlunos[i].datadenascimento.ano);
                        printf("\n > Prontuario e Curso: %i - %s\n", adrsAlunos[i].prontuario, adrsAlunos[i].curso);
                        
                        indicesEncontrados[encontrados] = i;
                        encontrados++;
                    };
                };

                break;

            case '2':
                printf("\nNome: ");
                fflush(stdin);
                fgets(nomeBuscar, TAMNOME, stdin);
                nomeBuscar[strlen(nomeBuscar) - 1] = 0;

                for (int i = 0; i <= (*nextPosition - 1); i++) {
                    if (strcmp(adrsAlunos[i].nome, nomeBuscar) == 0) {
                        printf("\n > Nome e Sobrenome: %s %s", adrsAlunos[i].nome, adrsAlunos[i].sobrenome);
                        printf("\n > Nascimento: %i/%i/%i", 
                            adrsAlunos[i].datadenascimento.dia, 
                            adrsAlunos[i].datadenascimento.mes,
                            adrsAlunos[i].datadenascimento.ano);
                        printf("\n > Prontuario e Curso: %i - %s\n", adrsAlunos[i].prontuario, adrsAlunos[i].curso);
                        
                        indicesEncontrados[encontrados] = i;
                        encontrados++;
                    };
                };

                break;

            case '3':
                printf("\nSobrenome: ");
                fflush(stdin);
                fgets(sobrenomeBuscar, TAMNOME, stdin);
                sobrenomeBuscar[strlen(sobrenomeBuscar) - 1] = 0;

                for (int i = 0; i <= (*nextPosition - 1); i++) {
                    if (strcmp(adrsAlunos[i].sobrenome, sobrenomeBuscar) == 0) {
                        printf("\n > Nome e Sobrenome: %s %s", adrsAlunos[i].nome, adrsAlunos[i].sobrenome);
                        printf("\n > Nascimento: %i/%i/%i", 
                            adrsAlunos[i].datadenascimento.dia, 
                            adrsAlunos[i].datadenascimento.mes,
                            adrsAlunos[i].datadenascimento.ano);
                        printf("\n > Prontuario e Curso: %i - %s\n", adrsAlunos[i].prontuario, adrsAlunos[i].curso);
                        
                        indicesEncontrados[encontrados] = i;
                        encontrados++;
                    };
                };

                break;

            case '4':
                printf("\nProntuario: ");
                scanf("%i", &prontuarioBuscar);

                for (int i = 0; i <= (*nextPosition - 1); i++) {
                    if (adrsAlunos[i].prontuario == prontuarioBuscar) {
                        printf("\n > Nome e Sobrenome: %s %s", adrsAlunos[i].nome, adrsAlunos[i].sobrenome);
                        printf("\n > Nascimento: %i/%i/%i", 
                            adrsAlunos[i].datadenascimento.dia, 
                            adrsAlunos[i].datadenascimento.mes,
                            adrsAlunos[i].datadenascimento.ano);
                        printf("\n > Prontuario e Curso: %i - %s\n", adrsAlunos[i].prontuario, adrsAlunos[i].curso);
                        
                        indicesEncontrados[encontrados] = i;                    
                        encontrados++;
                    };
                };

                break;

            case '5':
                printf("\nDia: ");
                scanf("%i", &nascBuscar.dia);

                printf("\nMes: ");
                scanf("%i", &nascBuscar.mes);

                printf("\nAno: ");
                scanf("%i", &nascBuscar.ano);

                for (int i = 0; i <= (*nextPosition - 1); i++) {
                    if (adrsAlunos[i].datadenascimento.dia == nascBuscar.dia &&
                        adrsAlunos[i].datadenascimento.mes == nascBuscar.mes &&
                        adrsAlunos[i].datadenascimento.ano == nascBuscar.ano) {

                        printf("\n > Nome e Sobrenome: %s %s", adrsAlunos[i].nome, adrsAlunos[i].sobrenome);
                        printf("\n > Nascimento: %i/%i/%i", 
                            adrsAlunos[i].datadenascimento.dia, 
                            adrsAlunos[i].datadenascimento.mes,
                            adrsAlunos[i].datadenascimento.ano);
                        printf("\n > Prontuario e Curso: %i - %s\n", adrsAlunos[i].prontuario, adrsAlunos[i].curso);
                        
                        indicesEncontrados[encontrados] = i;
                        encontrados++;
                    };
                };

                break;

            case '6':
                printf("\nCurso: ");
                fflush(stdin);
                fgets(cursoBuscar, TAMNOME, stdin);
                cursoBuscar[strlen(cursoBuscar) - 1] = 0;

                for (int i = 0; i <= (*nextPosition - 1); i++) {
                    if (strcmp(adrsAlunos[i].curso, cursoBuscar) == 0) {
                
                        printf("\n > Nome e Sobrenome: %s %s", adrsAlunos[i].nome, adrsAlunos[i].sobrenome);
                        printf("\n > Nascimento: %i/%i/%i", 
                            adrsAlunos[i].datadenascimento.dia, 
                            adrsAlunos[i].datadenascimento.mes,
                            adrsAlunos[i].datadenascimento.ano);
                        printf("\n > Prontuario e Curso: %i - %s\n", adrsAlunos[i].prontuario, adrsAlunos[i].curso);
                        
                        indicesEncontrados[encontrados] = i;
                        encontrados++;
                    };
                };

                break;

            default:
                printf("\n----- Opcao invalida -----\n");
        };

        if (encontrados == 0) {
            printf("\n----- NENHUM ALUNO ENCONTRADO -----\n");

        } else {
            char delete;
            printf("\n> Deseja remover os alunos encontrados? (s/n): ");
            fflush(stdin);
            scanf("%c", &delete);

            if (delete == 's' || delete == 'S') {
                printf("\n ----- ALUNOS DELETADOS -----\n");
                deletar(adrsAlunos, nextPosition, indicesEncontrados, encontrados);
            };
        };
    };
};

void swap(aluno* alunoA, aluno* alunoB) {
    aluno aux = *alunoA;
    *alunoA = *alunoB;
    *alunoB = aux;
};

int partition (aluno* adrsAlunos, int start, int end, int field) {

    aluno pivot = adrsAlunos[end];
    int indexTrocar = start - 1;
    char nomePivot[TAMNOME + TAMSOBRENOME];

    switch (field) {
        case 1:
            strcpy(nomePivot, pivot.nome);
            strcat(nomePivot, pivot.sobrenome);

            for (int i = start; i < end; i++) {
                char nomeAluno[TAMNOME + TAMSOBRENOME];
                strcpy(nomeAluno, adrsAlunos[i].nome);
                strcat(nomeAluno, adrsAlunos[i].sobrenome);

                if (strcmp(nomeAluno, nomePivot) <= 0) {
                    indexTrocar++;

                    swap(&adrsAlunos[indexTrocar], &adrsAlunos[i]);
                };
            };

            break;

        case 4:
            for (int i = start; i < end; i++) {
                if (adrsAlunos[i].prontuario <= pivot.prontuario) {
                    indexTrocar++;

                    swap(&adrsAlunos[indexTrocar], &adrsAlunos[i]);
                };
            };

            break;

        case 5:
            for (int i = start; i < end; i++) {
                if (strcmp(adrsAlunos[i].curso, pivot.curso) <= 0) {
                    indexTrocar++;

                    swap(&adrsAlunos[indexTrocar], &adrsAlunos[i]);
                };
            };
            
            break;
        
        default:
            printf("\n----- ERROR: CAMPO INVALIDO -----");

            break;
    };

    swap(&adrsAlunos[indexTrocar + 1], &adrsAlunos[end]);

    return (indexTrocar + 1);
};

void quicksort (aluno* adrsAlunos, int start, int end, int field) {

    if (start < end) {
        int pivot = partition(adrsAlunos, start, end, field);
        
        quicksort(adrsAlunos, start, (pivot - 1), field);
        quicksort(adrsAlunos, (pivot + 1), end, field);
    };
};

void menu (bool* ptrLoop, aluno *ptrAlunos, int* nextPosition) {

    char option;

    printf("\n1- Cadastrar aluno\n");
    printf("2- Listar todos os alunos\n");
    printf("3- Buscar alunos\n");
    printf("4- Ordenar alunos\n");
    printf("0- Sair\n");

    printf("\nEscolha uma opcao: ");
    scanf("%c", &option);

    switch (option) {
        case '0':
            printf("\nSaindo...");
            *ptrLoop = false;
            
            break;

        case '1':
            printf("\nEscolheu 1");
            cadastro(ptrAlunos, nextPosition);

            break;

        case '2':
            printf("\nEscolheu 2");
            listarTodos(ptrAlunos, (*nextPosition - 1));

            break;

        case '3':
            printf("\nEscolheu 3");
            buscar(ptrAlunos, nextPosition);

            break;

        case '4':
            printf("\nEscolheu 4");
            
            int field;
            fflush(stdin);
            printf("\nOpçoes de ordenacao:");
            printf("\n1- Nome e Sobrenome");
            printf("\n2- Sobrenome e Nome");
            printf("\n3- Nascimento");
            printf("\n4- Prontuario");
            printf("\n5- Curso");
            printf("\nBuscar por: ");
            scanf("%i", &field);

            quicksort(ptrAlunos, 0, (*nextPosition - 1), field);

            break;

        default:
            printf("\n----- Opcao invalida -----\n");
    };

    fflush(stdin);
};

int main () {
    
    /* Globals */
    aluno alunos[NUMALUNOS];
    memset(alunos, 0, NUMALUNOS * sizeof(aluno));
    int nextPosition = 0;

    bool loop = true;

    while (loop) {
        menu(&loop, alunos, &nextPosition);
    };
};