/* Libs */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

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
bool datecmp(data dataA, data dataB);
char* strLower(char* nome);
int partition(aluno* adrsAlunos, int start, int end, int field);
int push(aluno* adrsAlunos, int* adrsNextPosition);
void delete(aluno* adrsAlunos, int* nextPosition, int* adrsEncontrados, int qntEncontrados);
void find(aluno* adrsAlunos, int* nextPosition);
void menu(bool* ptrLoop, aluno *ptrAlunos, int* nextPosition);
void printArray(aluno* adrsAlunos, int maxIndice);
void quicksort(aluno* adrsAlunos, int start, int end, int field);
void swap(aluno* alunoA, aluno* alunoB);
void createFile(aluno* adrsAlunos, int end);
int readFile ();

/* Functions */
int push (aluno* adrsAlunos, int* adrsNextPosition) {

    int nextPosition = *adrsNextPosition;

    if (*adrsNextPosition < NUMALUNOS) {

        char nome[TAMNOME], sobrenome[TAMSOBRENOME], curso[TAMCURSO];
        int dia, mes, ano, prontuario;

        aluno newAluno;

        printf("\n> Nome: ");
        fflush(stdin);
        fgets(nome, TAMNOME, stdin);
        nome[strcspn(nome, "\n")] = 0;
        strcmp(nome, strLower(nome));

        fflush(stdin);
        printf("> Sobrenome: ");
        fgets(sobrenome, TAMSOBRENOME, stdin);
        sobrenome[strcspn(sobrenome, "\n")] = 0;
        strcmp(sobrenome, strLower(sobrenome));

        fflush(stdin);
        printf("> Dia de nascimento: ");
        scanf("%d", &dia);

        fflush(stdin);
        printf("> Mes de nascimento: ");
        scanf("%d", &mes);

        fflush(stdin);
        printf("> Ano de nascimento: ");
        scanf("%d", &ano);

        fflush(stdin);
        printf("> Prontuario: ");
        scanf("%d", &prontuario);

        fflush(stdin);
        printf("> Curso: ");
        fgets(curso, TAMCURSO, stdin);
        curso[strcspn(curso, "\n")] = 0;
        strcmp(curso, strLower(curso));

        for (int i = 0; i < *adrsNextPosition; i++) {
            if (adrsAlunos[i].prontuario == prontuario) {
                printf("\n-------- PRONTUARIO JA CADASTRADO --------\n\n");
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
        printf("\n-------- ALUNO ADICIONADO --------\n\n");

    } else {
        printf("\n-------- LIMITE DE ALUNOS CADASTRADOS --------\n\n");
    };

    return 0;
};

void printArray (aluno* adrsAlunos, int maxIndice) {

    if (maxIndice < 0) {
        printf("\n---------- NENHUM ALUNO CADASTRADO ---------\n\n");

    } else {
        printf("\n> Alunos Cadastrados: \n");

        for (int i = 0; i <= maxIndice; i++) {

            printf("\n Aluno %i", (i + 1));
            printf("\n > Nome e Sobrenome: %s %s", adrsAlunos[i].nome, adrsAlunos[i].sobrenome);
            printf("\n > Nascimento: %i/%i/%i", 
                adrsAlunos[i].datadenascimento.dia, 
                adrsAlunos[i].datadenascimento.mes,
                adrsAlunos[i].datadenascimento.ano);
            printf("\n > Prontuario e Curso: %i - %s", adrsAlunos[i].prontuario, adrsAlunos[i].curso);
            printf("\n-----------------//-----------------\n");
        };

        printf("\n\n");
    };
};

void delete (aluno* adrsAlunos, int* nextPosition, int* adrsEncontrados, int qntEncontrados) {

    for (int i = 0; i < qntEncontrados; i++) {

        if (adrsEncontrados[i] != (*nextPosition - 1)) {
            adrsAlunos[adrsEncontrados[i]] = adrsAlunos[*nextPosition - 1];
        };

        *nextPosition = (*nextPosition) - 1;
    };
};

void find (aluno* adrsAlunos, int* nextPosition) {

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
        printf("\n---------- NENHUM ALUNO CADASTRADO ---------\n\n");

    } else {
        char nomeBuscar[TAMNOME];
        char sobrenomeBuscar[TAMSOBRENOME];
        int prontuarioBuscar;
        data nascBuscar;
        char cursoBuscar[TAMCURSO];

        switch (campoBuscar) {
            case '1':
                printf("\n> Nome: ");
                fgets(nomeBuscar, TAMNOME + 1, stdin);
                nomeBuscar[strcspn(nomeBuscar, "\n")] = 0;

                strcpy(nomeBuscar, strLower(nomeBuscar));

                printf("> Sobrenome: ");
                fflush(stdin);
                fgets(sobrenomeBuscar, TAMNOME + 1, stdin);
                sobrenomeBuscar[strcspn(sobrenomeBuscar, "\n")] = 0;
                strcpy(sobrenomeBuscar, strLower(sobrenomeBuscar));

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
                printf("\n> Nome: ");
                fflush(stdin);
                fgets(nomeBuscar, TAMNOME + 1, stdin);
                nomeBuscar[strcspn(nomeBuscar, "\n")] = 0;
                strcpy(nomeBuscar, strLower(nomeBuscar));

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
                printf("\n> Sobrenome: ");
                fflush(stdin);
                fgets(sobrenomeBuscar, TAMNOME + 1, stdin);
                sobrenomeBuscar[strcspn(sobrenomeBuscar, "\n")] = 0;
                strcpy(sobrenomeBuscar, strLower(sobrenomeBuscar));

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
                printf("\n> Prontuario: ");
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
                printf("\n> Dia: ");
                scanf("%i", &nascBuscar.dia);

                printf("> Mes: ");
                scanf("%i", &nascBuscar.mes);

                printf("> Ano: ");
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
                printf("\n> Curso: ");
                fflush(stdin);
                fgets(cursoBuscar, TAMCURSO, stdin);
                cursoBuscar[strcspn(cursoBuscar, "\n")] = 0;
                strcpy(cursoBuscar, strLower(cursoBuscar));

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
                printf("\n-------- OPCAO INVALIDA --------\n");
        };

        if (encontrados == 0) {
            printf("\n----- NENHUM ALUNO FOI ENCONTRADO -----\n\n");

        } else {
            char deleteChoose;
            printf("\n> Deseja remover os alunos encontrados? (s/n): ");
            fflush(stdin);
            scanf("%c", &deleteChoose);

            if (deleteChoose == 's' || deleteChoose == 'S') {
                printf("\n-------- ALUNOS DELETADOS --------");
                delete(adrsAlunos, nextPosition, indicesEncontrados, encontrados);
            };

            printf("\n\n");

        };
    };
};

bool datecmp (data dataA, data dataB) {

    if (dataA.ano < dataB.ano) {
        return true;

    } else if (dataA.ano == dataB.ano) {
        if (dataA.mes < dataB.mes) {
            return true;

        } else if (dataA.mes == dataB.mes) {
            if (dataA.dia <= dataB.dia) {
                return true;
            };
        };
    };

    return false;
};

char* strLower (char* nome) {

    for (int i = 0; nome[i]; i++) {
        nome[i] = tolower(nome[i]);
    };

    return nome;
};

void swap (aluno* alunoA, aluno* alunoB) {
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

        case 2:
            strcpy(nomePivot, pivot.sobrenome);
            strcat(nomePivot, pivot.nome);

            for (int i = start; i < end; i++) {
                char nomeAluno[TAMNOME + TAMSOBRENOME];
                strcpy(nomeAluno, adrsAlunos[i].sobrenome);
                strcat(nomeAluno, adrsAlunos[i].nome);

                if (strcmp(nomeAluno, nomePivot) <= 0) {
                    indexTrocar++;

                    swap(&adrsAlunos[indexTrocar], &adrsAlunos[i]);
                };
            };

            break;
            
        case 3:
            for (int i = start; i < end; i++) {
                if (datecmp(adrsAlunos[i].datadenascimento, pivot.datadenascimento)) {
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

void createFile (aluno* adrsAlunos, int end) {

    if (end < 0) {
        printf("\n ----- NAO EXISTEM ALUNOS CADASTRADOS \n");
        
    } else {

        printf("\n> CRIANDO ARQUIVO...\n");

        FILE *arquivo;
        int result;

        arquivo = fopen("alunos", "w");

        if (arquivo == NULL) {
            printf("\n ----- NAO FOI POSSIVEL CRIAR O ARQUIVO -----\n");
            return;
        };

        for (int index = 0; index <= end; index++) {
        
            result = fwrite(&adrsAlunos[index], sizeof(aluno), 1, arquivo);

            if (result != 1) {
                if (feof(arquivo)) {
                    break;
                };
                printf("\n ----- ERRO NA ESCRITA DO ARQUIVO ----- \n");
            };
        };

        printf("\n-------- ARQUIVO CRIADO --------\n\n");

        fclose(arquivo);
    };
};

int readFile (aluno* adrsAlunos) {

    FILE *arquivo;

    arquivo = fopen("alunos", "r");
    int i, result, end = 0;
    //aluno alunosLidos[NUMALUNOS];

    if (arquivo == NULL) {
        printf("\n ----- NAO FOI POSSIVEL LER O ARQUIVO -----\n");
        return 0;
    };

    for (i = 0; i < NUMALUNOS; i++) {
        result = fread(&adrsAlunos[i], sizeof(aluno), 1, arquivo);

        if (result != 1) {
            if (feof (arquivo)) {
                break;
            };

            printf("\n ----- ERRO NA LEITURA DO ARQUIVO ----- \n");
            return 0;            
        };

    };

    printf("\n-------- ARQUIVO CARREGADO --------\n\n");

    return i;
};

void menu (bool* ptrLoop, aluno *ptrAlunos, int* nextPosition) {

    char option;

    printf("-------- MENU --------");
    printf("\n1- Cadastrar aluno\n");
    printf("2- Listar todos os alunos\n");
    printf("3- Buscar alunos\n");
    printf("4- Ordenar alunos\n");
    printf("5- Criar arquivo\n");
    printf("6- Ler arquivo\n");
    printf("0- Sair\n");

    printf("\nEscolha uma opcao: ");
    scanf("%c", &option);

    switch (option) {
        case '0':
            printf("\n> SAINDO...");
            *ptrLoop = false;
            
            break;

        case '1':
            printf("\n> CADASTRO DE ALUNO");
            push(ptrAlunos, nextPosition);

            break;

        case '2':
            printf("\n> TOTAL DE ALUNOS CADASTRADOS: %i", *nextPosition);
            printArray(ptrAlunos, (*nextPosition - 1));

            break;

        case '3':
            printf("\n> PROCURAR ALUNO");
            find(ptrAlunos, nextPosition);

            break;

        case '4':
            printf("\n> ORDENAR LISTA DE ALUNOS");
            
            int field;
            fflush(stdin);
            printf("\n\n Opcoes de ordenacao:");
            printf("\n 1- Nome e Sobrenome");
            printf("\n 2- Sobrenome e Nome");
            printf("\n 3- Nascimento");
            printf("\n 4- Prontuario");
            printf("\n 5- Curso");
            printf("\n\n Ordenar por: ");
            scanf("%i", &field);

            quicksort(ptrAlunos, 0, (*nextPosition - 1), field);
            printArray(ptrAlunos, (*nextPosition - 1));

            break;

        case '5':
            printf("\n> CRIAR ARQUIVO\n");
            createFile(ptrAlunos, (*nextPosition - 1));
            
            break;

        case '6':
            printf("\n> LER ARQUIVO\n");
            *nextPosition = readFile(ptrAlunos);

            break;

        default:
            printf("\n-------- OPCAO INVALIDA --------\n\n");
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