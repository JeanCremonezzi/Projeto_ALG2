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
int datecmp(data dataA, data dataB);
char* strLower(char* nome);
int partition(aluno* adrsAlunos, int start, int end, char field);
int push(aluno* adrsAlunos, int* adrsNextPosition);
void delete(aluno* adrsAlunos, int* nextPosition, int* adrsEncontrados, int qntEncontrados);
void find(aluno* adrsAlunos, int* nextPosition, char orderedBy);
void linearSearch (aluno* adrsAlunos, int end, char campoBuscar, aluno alunoBuscar, int* adrsIndexEncontrados, int* qntEncontrados);
void binarySearch (aluno* adrsAlunos, int start, int end, char campoBuscar, aluno alunoBuscar, int* adrsIndexEncontrados, int* qntEncontrados);
void menu(bool* ptrLoop, aluno *ptrAlunos, int* nextPosition, char* ptrOrderedBy);
void printArray(aluno* adrsAlunos, int maxIndice);
int compareAlunos(aluno aluno1, aluno aluno2, char field);
void quicksort(aluno* adrsAlunos, int start, int end, char field);
void swap(aluno* alunoA, aluno* alunoB);
void merge(aluno* adrsAlunos, int start, int middle, int end, char field);
void mergeSort(aluno* adrsAlunos, int start, int end, char field);
int lowest(aluno* adrsAlunos, int start, int end, char field);
void selectionSort(aluno* adrsAlunos, int end, char field);
void insertSort(aluno* adrsAlunos, int end, char field);
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

    for (int i = (qntEncontrados - 1); i >= 0; i--) {

        if (adrsEncontrados[i] != (*nextPosition - 1)) {
            adrsAlunos[adrsEncontrados[i]] = adrsAlunos[*nextPosition - 1];
        };

        *nextPosition = (*nextPosition) - 1;
        
        createFile(adrsAlunos, "alunos", *nextPosition);

    };
};

void linearSearch (aluno* adrsAlunos, int end, char campoBuscar, aluno alunoBuscar, int* adrsIndexEncontrados, int* qntEncontrados) {

    for (int i = 0; i <= end; i++) {
        if (compareAlunos(alunoBuscar, adrsAlunos[i], campoBuscar) == 0) {
                                            
            adrsIndexEncontrados[*qntEncontrados] = i;
            *qntEncontrados += 1;
        };
    };
};

void binarySearch (aluno* adrsAlunos, int start,int end, char campoBuscar, aluno alunoBuscar, int* adrsIndexEncontrados, int* qntEncontrados) {
    int middle;

    while (start <= end) {
        middle = start + (end - start) / 2;

        int resultCompare = compareAlunos(alunoBuscar, adrsAlunos[middle], campoBuscar);

        if (resultCompare == 0) {
            adrsIndexEncontrados[*qntEncontrados] = middle;
            *qntEncontrados += 1;
            
            // Continua buscando elementos na esqueda do vetor
            binarySearch(adrsAlunos, start, (middle - 1), campoBuscar, alunoBuscar, adrsIndexEncontrados, qntEncontrados);
            
            // Continua buscando elementos na direita do vetor
            binarySearch(adrsAlunos, (middle + 1), end, campoBuscar, alunoBuscar, adrsIndexEncontrados, qntEncontrados);

            return;

        } else if (resultCompare == - 1) {
            end = middle - 1;

        } else if (resultCompare == 1) {
            start = middle + 1;
        };
    };
};

int datecmp (data dataA, data dataB) {

    /*
    *   return -1 -> dataA < dataB
    *   return 0 -> dataA = dataB
    *   return 1 -> dataA > dataB
    */

    if (dataA.ano < dataB.ano) {
        return -1;

    } else if (dataA.ano == dataB.ano) {
        if (dataA.mes < dataB.mes) {
            return -1;

        } else if (dataA.mes == dataB.mes) {
            if (dataA.dia < dataB.dia) {
                return -1;

            } else if (dataA.dia == dataB.dia) {
                return 0;
            };
        };
    }

    return 1;
};

char* strLower (char* nome) {

    for (int i = 0; nome[i]; i++) {
        nome[i] = tolower(nome[i]);
    };

    return nome;
};

int compareAlunos (aluno aluno1, aluno aluno2, char field) {
    /*
    *   return < 0 -> aluno1 < aluno2
    *   return = 0 -> aluno1 <= aluno2
    *   return = 1 -> aluno1 > aluno2
    *   return > 1 -> Error
    */

    switch (field) {
        char fullname1[TAMNOME + TAMSOBRENOME];
        char fullname2[TAMNOME + TAMSOBRENOME];

        case '1':
            // Compara nome
            strcpy(fullname1, aluno1.nome);
            strcat(fullname1, aluno1.sobrenome);

            strcpy(fullname2, aluno2.nome);
            strcat(fullname2, aluno2.sobrenome);

            return strcmp(fullname1, fullname2);
            
        case '2':
            // Compara sobrenome e nome
            strcpy(fullname1, aluno1.sobrenome);
            strcat(fullname1, aluno1.nome);

            strcpy(fullname2, aluno2.sobrenome);
            strcat(fullname2, aluno2.nome);

            return strcmp(fullname1, fullname2);

        case '3':
            // Compara data nascimento
            return datecmp(aluno1.datadenascimento, aluno2.datadenascimento);
            
        case '4':
            // Compara prontuario
            if (aluno1.prontuario < aluno2.prontuario) {
                return -1;

            } else if (aluno1.prontuario == aluno2.prontuario) {
                return 0;
            };

            return 1;

        case '5':
            // Compara prontuario
            return strcmp(aluno1.curso, aluno2.curso);

        case '6':
            // Compara nome
            return strcmp(aluno1.nome, aluno2.nome);

        case '7':
            // Compara sobrenome
            return strcmp(aluno1.sobrenome, aluno2.sobrenome);

        default:
            printf("\n----- ERROR: CAMPO INVALIDO -----");
            return 2;
    };
};

void swap (aluno* alunoA, aluno* alunoB) {
    aluno aux = *alunoA;
    *alunoA = *alunoB;
    *alunoB = aux;
};

int partition (aluno* adrsAlunos, int start, int end, char field) {

    aluno pivot = adrsAlunos[end];
    int indexTrocar = start - 1;

    for (int i = start; i < end; i++) {

        if (compareAlunos(adrsAlunos[i], pivot, field) <= 0) {
            indexTrocar++;

            swap(&adrsAlunos[indexTrocar], &adrsAlunos[i]);
        };
    };

    swap(&adrsAlunos[indexTrocar + 1], &adrsAlunos[end]);

    return (indexTrocar + 1);
};

void quicksort (aluno* adrsAlunos, int start, int end, char field) {
    if (start < end) {
        int pivot = partition(adrsAlunos, start, end, field);
        
        quicksort(adrsAlunos, start, (pivot - 1), field);
        quicksort(adrsAlunos, (pivot + 1), end, field);
    };
};

void merge (aluno* adrsAlunos, int start, int middle, int end, char field) {
    aluno aux[NUMALUNOS];
    int i = start, j = middle + 1, k = 0;
    
    while (i <= middle && j <= end) {
        if (compareAlunos(adrsAlunos[i], adrsAlunos[j], field) <= 0) {
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

void mergeSort (aluno* adrsAlunos, int start, int end, char field) {
    int middle;

    if (start < end) {
        middle = (start + end) / 2;
        mergeSort(adrsAlunos, start, middle, field);
        mergeSort(adrsAlunos, middle + 1, end, field);
        merge(adrsAlunos, start, middle, end, field);
    };
};

int lowest (aluno* adrsAlunos, int start, int end, char field) {
    int menor = start;

    for (int i = start + 1; i <= end; i++) {
        if (compareAlunos(adrsAlunos[i], adrsAlunos[menor], field) <= 0) {
            menor = i;
        };
    };

    return menor;
};

void selectionSort (aluno* adrsAlunos, int end, char field) {
    int indexMenor;

    for (int i = 0; i <= end; i++) {
        indexMenor = lowest(adrsAlunos, i, end, field);
        swap(&adrsAlunos[i], &adrsAlunos[indexMenor]);
    };
};

void insertSort (aluno* adrsAlunos, int end, char field) {

    for (int index = 1; index <= end; index++) {
        aluno pivot = adrsAlunos[index];
        int indexAux = index - 1;

        while (compareAlunos(pivot, adrsAlunos[indexAux], field) <= 0 && indexAux >= 0) {
            adrsAlunos[indexAux + 1] = adrsAlunos[indexAux];
            --indexAux;
        };

        adrsAlunos[indexAux + 1] = pivot;
    };
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

aluno createAlunoBuscar (char campoBuscar) {
    aluno alunoBuscar;

    switch (campoBuscar) {
        case '1':
            printf("\n> Nome: ");
            fgets(alunoBuscar.nome, TAMNOME + 1, stdin);
            alunoBuscar.nome[strcspn(alunoBuscar.nome, "\n")] = 0;
            strcpy(alunoBuscar.nome, strLower(alunoBuscar.nome));

            printf("> Sobrenome: ");
            fflush(stdin);
            fgets(alunoBuscar.sobrenome, TAMNOME + 1, stdin);
            alunoBuscar.sobrenome[strcspn(alunoBuscar.sobrenome, "\n")] = 0;
            strcpy(alunoBuscar.sobrenome, strLower(alunoBuscar.sobrenome));

            break;

        case '2':
            printf("> Sobrenome: ");
            fflush(stdin);
            fgets(alunoBuscar.sobrenome, TAMNOME + 1, stdin);
            alunoBuscar.sobrenome[strcspn(alunoBuscar.sobrenome, "\n")] = 0;
            strcpy(alunoBuscar.sobrenome, strLower(alunoBuscar.sobrenome));

            campoBuscar = '7';

            break;

        case '3':
            printf("\n> Dia: ");
            scanf("%i", &alunoBuscar.datadenascimento.dia);

            printf("> Mes: ");
            scanf("%i", &alunoBuscar.datadenascimento.mes);

            printf("> Ano: ");
            scanf("%i", &alunoBuscar.datadenascimento.ano);

            break;

        case '4':
            printf("\n> Prontuario: ");
            scanf("%i", &alunoBuscar.prontuario);

            break;

        case '5':
            printf("\n> Curso: ");
            fflush(stdin);
            fgets(alunoBuscar.curso, TAMCURSO, stdin);
            alunoBuscar.curso[strcspn(alunoBuscar.curso, "\n")] = 0;
            strcpy(alunoBuscar.curso, strLower(alunoBuscar.curso));

            break;

        case '6':
            printf("\n> Nome: ");
            fgets(alunoBuscar.nome, TAMNOME + 1, stdin);
            alunoBuscar.nome[strcspn(alunoBuscar.nome, "\n")] = 0;
            strcpy(alunoBuscar.nome, strLower(alunoBuscar.nome));

            break;

        default:
            printf("\n-------- OPCAO INVALIDA --------\n");
    };

    return alunoBuscar;
};

void find (aluno* adrsAlunos, int* nextPosition, char orderedBy) {
    
    if ((*nextPosition) <= 0) {
        printf("\n\n----- NENHUM ALUNO CADASTRADO -----\n\n");

    } else {

        char campoBuscar;
        int indexEncontrados[NUMALUNOS];
        int qntEncontrados = 0;

        fflush(stdin);

        printf("\n> Buscar por: ");
        printf("\n 1- Nome e Sobrenome");
        printf("\n 2- Sobrenome");
        printf("\n 3- Nascimento");
        printf("\n 4- Prontuario");
        printf("\n 5- Curso");
        printf("\n 6- Nome");
                
        printf("\n\n > Escolha um campo: ");
        scanf("%c", &campoBuscar);
        fflush(stdin);

        aluno alunoChave = createAlunoBuscar(campoBuscar);
        
        if (campoBuscar == orderedBy) {
            binarySearch(adrsAlunos, 0, (*nextPosition - 1), campoBuscar, alunoChave, indexEncontrados, &qntEncontrados);

        } else {
            linearSearch(adrsAlunos, (*nextPosition - 1), campoBuscar, alunoChave, indexEncontrados, &qntEncontrados);
        };

        if (qntEncontrados == 0) {
            printf("\n----- NENHUM ALUNO FOI ENCONTRADO -----\n\n");

        } else {
            char deleteChoose;

            for (int i = 0; i < qntEncontrados; i++) {
                int indexEncontrado = indexEncontrados[i];

                printf("\n > Nome e Sobrenome: %s %s", adrsAlunos[indexEncontrado].nome, adrsAlunos[indexEncontrado].sobrenome);
                printf("\n > Nascimento: %i/%i/%i", 
                adrsAlunos[indexEncontrado].datadenascimento.dia, 
                adrsAlunos[indexEncontrado].datadenascimento.mes,
                adrsAlunos[indexEncontrado].datadenascimento.ano);
                printf("\n > Prontuario e Curso: %i - %s\n", adrsAlunos[indexEncontrado].prontuario, adrsAlunos[indexEncontrado].curso);
            };

            printf("\n> Deseja remover os alunos encontrados? (s/n): ");
            fflush(stdin);
            scanf("%c", &deleteChoose);

            if (deleteChoose == 's' || deleteChoose == 'S') {
                printf("\n-------- ALUNOS DELETADOS --------");
                delete(adrsAlunos, nextPosition, indexEncontrados, qntEncontrados);
            };

            printf("\n\n");

        };
    };
};

void menu (bool* ptrLoop, aluno *ptrAlunos, int* nextPosition, char* ptrOrderedBy) {

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
            find(ptrAlunos, nextPosition, (*ptrOrderedBy));

            break;

        case '4':
            printf("\n> ORDENAR LISTA DE ALUNOS");
            
            char field;
            int sortAlg;
            fflush(stdin);
            printf("\n\n Opcoes de ordenacao:");
            printf("\n 1- Nome e Sobrenome");
            printf("\n 2- Sobrenome e Nome");
            printf("\n 3- Nascimento");
            printf("\n 4- Prontuario");
            printf("\n 5- Curso");
            printf("\n\n Ordenar por: ");
            scanf("%c", &field);

            fflush(stdin);
            printf("\n\n Algoritmos de ordenacao:");
            printf("\n 1- Quick Sort");
            printf("\n 2- Merge Sort");
            printf("\n 3- Selection Sort");
            printf("\n 4- Insertion Sort");
            printf("\n\n Qual metodo utilizar: ");
            scanf("%i", &sortAlg);

            switch (sortAlg) {
                case 1:
                    quicksort(ptrAlunos, 0, (*nextPosition - 1), field);
                    break;

                case 2:
                    mergeSort(ptrAlunos, 0, (*nextPosition - 1), field);
                    break;

                case 3:
                    selectionSort(ptrAlunos, (*nextPosition - 1), field);
                    break;

                case 4:
                    insertSort(ptrAlunos, (*nextPosition - 1), field);
                    break;

                default:
                    break;
            };

            *ptrOrderedBy = field;
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
    char orderedBy = 0;

    readFile(alunos, "alunos", &nextPosition);

    bool loop = true;

    while (loop) {
        menu(&loop, alunos, &nextPosition, &orderedBy);
    };
};