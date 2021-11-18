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
int compareAlunos(aluno aluno1, aluno aluno2, int field);
void quicksort(aluno* adrsAlunos, int start, int end, int field);
void swap(aluno* alunoA, aluno* alunoB);
void merge(aluno* adrsAlunos, int start, int middle, int end, int field);
void mergeSort(aluno* adrsAlunos, int start, int end, int field);
void createFile(aluno* adrsAlunos, char* fileName, int end);
void readFile(aluno* adrsAlunos, char* fileName, int* nextPosition);

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

        createFile(adrsAlunos, "alunos", *adrsNextPosition);

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
        
        createFile(adrsAlunos, "alunos", *nextPosition);

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

int compareAlunos (aluno aluno1, aluno aluno2, int field) {
    int result;

    switch (field) {
        char fullname1[TAMNOME + TAMSOBRENOME];
        char fullname2[TAMNOME + TAMSOBRENOME];

        case 1:
            // Compara nome
            strcpy(fullname1, aluno1.nome);
            strcat(fullname1, aluno1.sobrenome);

            strcpy(fullname2, aluno2.nome);
            strcat(fullname2, aluno2.sobrenome);

            result = strcmp(fullname1, fullname2);

            break;
        
        case 2:
            // Compara sobrenome e nome
            strcpy(fullname1, aluno1.sobrenome);
            strcat(fullname1, aluno1.nome);

            strcpy(fullname2, aluno2.sobrenome);
            strcat(fullname2, aluno2.nome);

            result = strcmp(fullname1, fullname2);

        default:
            printf("\n----- ERROR: CAMPO INVALIDO -----");

            break;
    };

    /*
    *   result < 0 -> aluno1 < aluno2
    *   result = 0 -> aluno1 = aluno2
    *   result > 0 -> aluno1 > aluno2
    */
    return result;
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

    for (int i = start; i < end; i++) {
        if (compareAlunos(adrsAlunos[i], pivot, field) <= 0) {
            indexTrocar++;

            swap(&adrsAlunos[indexTrocar], &adrsAlunos[i]);
        };
    };

    /*
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
    */

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

void merge (aluno* adrsAlunos, int start, int middle, int end, int field) {
    aluno aux[NUMALUNOS];
    int i = start, j = middle + 1, k = 0;

    while (i <= middle && j <= end) {
        if (adrsAlunos[i].prontuario <= adrsAlunos[j].prontuario) {
            aux[k++] = adrsAlunos[i++];

        } else {
            aux[k++] = adrsAlunos[j++];
        };
    };

    while (i <= middle) {
        aux[k++] = adrsAlunos[i++];
    };

    while (j <= end) {
        aux[k++] = adrsAlunos[j++];
    };

    for (i = start, k = 0; i <= end; i++, k++) {
        adrsAlunos[i] = aux[k];
    };
};

void mergeSort (aluno* adrsAlunos, int start, int end, int field) {
    int middle;

    if (start < end) {
        middle = (start + end) / 2;
        mergeSort(adrsAlunos, start, middle, field);
        mergeSort(adrsAlunos, middle + 1, end, field);
        merge(adrsAlunos, start, middle, end, field);
    }
};

void createFile (aluno* adrsAlunos, char* fileName, int end) {

    if (end < 0) {
        printf("\n----- NAO EXISTEM ALUNOS CADASTRADOS -----\n");
        
    } else {

        printf("\nGERANDO ARQUIVO...");

        FILE *arquivo;
        int result;

        arquivo = fopen("alunos", "w");

        if (arquivo == NULL) {
            printf("\n----- NAO FOI POSSIVEL GERAR O ARQUIVO -----\n");
            return;
        };

        for (int index = 0; index <= end; index++) {
        
            result = fwrite(&adrsAlunos[index], sizeof(aluno), 1, arquivo);

            if (result != 1) {
                if (feof(arquivo)) {
                    break;
                };
                printf("\n----- ERRO AO GERAR O ARQUIVO -----\n");
            };
        };

        printf("\nARQUIVO GERADO!\n\n");

        fclose(arquivo);
    };
};

void readFile (aluno* adrsAlunos, char* fileName, int* nextPosition) {

    FILE *arquivo;

    arquivo = fopen(fileName, "r");
    int i, result, end = 0;

    if (arquivo == NULL) {
        printf("\n----- NAO FOI POSSIVEL LER O ARQUIVO -----\n\n");
        return;
    };

    printf("\nLENDO ARQUIVO...");

    for (i = 0; i < NUMALUNOS; i++) {
        result = fread(&adrsAlunos[i], sizeof(aluno), 1, arquivo);

        if (result != 1) {
            if (feof (arquivo)) {
                break;
            };

            printf("\n----- ERRO AO LER ARQUIVO -----\n");
            return;            
        } else {
            *nextPosition = i;
        };
    };

    printf("\nARQUIVO CARREGADO!\n\n");

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
            int sortAlg;
            fflush(stdin);
            printf("\n\n Opcoes de ordenacao:");
            printf("\n 1- Nome e Sobrenome");
            printf("\n 2- Sobrenome e Nome");
            printf("\n 3- Nascimento");
            printf("\n 4- Prontuario");
            printf("\n 5- Curso");
            printf("\n\n Ordenar por: ");
            scanf("%i", &field);

            fflush(stdin);
            printf("\n\n Algoritmos de ordenacao:");
            printf("\n 1- Quick Sort");
            printf("\n 2- Merge Sort");
            printf("\n 3- Insertion Sort");
            printf("\n 4- Selection Sort");
            printf("\n\n Qual metodo utilizar: ");
            scanf("%i", &sortAlg);

            switch (sortAlg) {
                case 1:
                    quicksort(ptrAlunos, 0, (*nextPosition - 1), field);
                    break;

                case 2:
                    mergeSort(ptrAlunos, 0, (*nextPosition - 1), field);
                    break;

                default:
                    break;
            }

            createFile(ptrAlunos, "alunos", *nextPosition);

            printArray(ptrAlunos, (*nextPosition - 1));

            break;

        case '5':
            printf("\n> CRIAR ARQUIVO\n");
            createFile(ptrAlunos, "alunos", *nextPosition);
            
            break;

        case '6':
            printf("\n> LER ARQUIVO\n");
            readFile(ptrAlunos, "alunos", nextPosition);

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

    readFile(alunos, "alunos", &nextPosition);

    bool loop = true;

    while (loop) {
        menu(&loop, alunos, &nextPosition);
    };
};