#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include "utils.c"
#include "dataCollection.c"
#include "list.c"


struct Casella* crea_tabellone();
void genera_tabellone();
int genera_numero_in_range();
void genera_serpenti();
void genera_scale();
struct Giocatore* istanzia_giocatori();
void stampa_tabellone();
struct StringArray* string_read();
void gioca_snakes_and_ladders();
int lancia_dado();
void print_table();



struct Giocatore
{
    int id;
    int posizione; // posizione del giocatore sulla tabella
    char simbolo;   // simbolo con cui verrà identificato il giocatore sulla tavola
};

struct Casella
{
    int numero; // numero della casella
    int effetto;    // L'effetto può essere andare avanti oppure indietro, per es (+6 posizioni oppure -10). Se è 0 indica che non ha nessun effetto
};

int main() 
{
    srand(time(NULL));

    gioca_snakes_and_ladders(3);

    return 0;
}

void gioca_snakes_and_ladders(int numero_giocatori) {
    int numero_caselle = 100;
    struct Casella* tabellone = crea_tabellone();   // creo un tabellone e lo riempio di snakes and ladders
    struct Giocatore* giocatori = istanzia_giocatori(numero_giocatori); // creo i giocatori e assegno la loro posizione a 0

    int dado = 0;

    //struct Array *coda_giocatori = NULL;
    List coda_giocatori;
    coda_giocatori = list_new(); // istanzio la coda

    for (int i = 0; i < numero_giocatori; i++) {
        var indice;
        indice = var_set_int(i);
        list_push_back(&coda_giocatori, indice);    // Inserisco l'indice dei giocatori nella coda
    }

    int indice_giocatore_attuale = 0;
    struct Giocatore* giocatore_attuale = NULL;
    int c;
    //  Turno
    do {
        indice_giocatore_attuale = var_get_int(list_pop_front(&coda_giocatori)); // ottengo l'indice del giocatore facendo pop della coda
        giocatore_attuale = &giocatori[indice_giocatore_attuale]; // assegno a giocatore_attuale l'indirizzo del giocatore in turno nella struttura giocatori

        printf("\nInserisci 'd' per lanciare il dado");
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        dado = lancia_dado();
        //print_table(tabellone, numero_caselle, giocatori, numero_giocatori);
        if ((giocatore_attuale->posizione + dado) >= 99) {
            //il giocatore ha vinto
            giocatore_attuale-> posizione = 99;
            break;
        }

        giocatore_attuale->posizione += dado;    // aumento la posizione del giocatore di dado posti

        if (tabellone[giocatore_attuale->posizione].effetto > 0) {
            // chiedi domanda
        } else {
            giocatore_attuale->posizione += tabellone[giocatore_attuale->posizione].effetto;
        }

        list_push_back(&coda_giocatori, var_set_int(indice_giocatore_attuale)); // rimetto il giocatore nella coda
    } while (giocatore_attuale->posizione != 99);

    if (giocatore_attuale->posizione == 99) {   // Verifico la vincita
        // Vinto
    }






}

struct Casella* crea_tabellone()
{
    int numero_caselle = 100;
    struct Casella* tabellone = (struct Casella*) malloc(numero_caselle * sizeof(struct Casella));

    genera_tabellone(tabellone, numero_caselle);

    //stampa_tabellone(tabellone, numero_caselle);

    return tabellone;

}

void genera_tabellone(struct Casella *tabellone, int numero_caselle) // Questo metodo genera il tabellone e assegna quindi anche quali caselle sono scivoli e quali scale
{
    int contatore = 1;
    for(int i = 0; i < numero_caselle; i++)   // Scorro l'array di caselle
    {
        tabellone[i].numero = contatore;    // Assegno il numero a ogni casella partendo da 1
        contatore++;

        tabellone[i].effetto = 0;   // Azzero gli effetti di ogni casella
    }

    int max_serpenti = 10; //  numero massimo di serpenti
    int min_serpenti = 4;  // numero minimo di serpenti
    int num_serpenti = genera_numero_in_range(min_serpenti, max_serpenti);  // genero randomicamente un numero di serpenti tra min_serpenti e max_serpenti
    printf("Numero serpenti: %d", num_serpenti);

    genera_serpenti(tabellone, numero_caselle, num_serpenti);  // Genero i serpenti sul tabellone

    int max_scale = 10; // numero massimo di scale
    int min_scale = 4;  // numero minimo di scale
    int num_scale = genera_numero_in_range(min_scale, max_scale); // genero randomicamente un numero di scale tra min_scale e max_scale
    printf("\nNumero scale: %d\r\n", num_serpenti);

    genera_scale(tabellone, numero_caselle, num_scale);
}

void genera_serpenti(struct Casella* tabellone, int numero_caselle, int numero_serpenti)
{
    int indice_casella = 0; // Indice della casella per cui sto generando l'effetto
    int indice_coda = 0;    // Indice della coda di tabellone[indice_casella]. Ogni serpente e scala ha una coda e una testa
    int effetto = 0, max_effetto = 0, min_effetto = 0;

    for(int i = 0; i < numero_serpenti; i++) {
        do {
            do {
                indice_casella = genera_numero_in_range(1, numero_caselle - 2);  // genero un indice_casella randomico compreso tra 1 e numero_caselle - 2 (perché la prima casella è la partenza e l'ultima è la vincita)
            } while (tabellone[indice_casella].effetto != 0);   // Genera finché non trovi un posto non occupato da serpenti o scale

            max_effetto = -1;   // L'effetto serpente per esistere deve far scendere i giocatori di almeno 1 posizione
            min_effetto = -indice_casella;  // Il serpente non può sforare inferiormente il tabellone


            effetto = genera_numero_in_range(min_effetto, max_effetto); // genero randomicamente il valore dell'effetto tra min_effetto e max_effetto

            indice_coda = indice_casella - abs(effetto); // ottengo l'indice della casella della coda del serpente; uso abs(x) perché l'effetto è negativo

        } while (tabellone[indice_coda].effetto != 0);  // Rigenero un nuovo indice_casella e di conseguenza un indice_coda finché non trovo una coda libera (non occupata da serpenti o scale)

        tabellone[indice_casella].effetto = effetto;    // assegno l'effetto generato
    }
}

void genera_scale(struct Casella* tabellone, int numero_caselle, int numero_scale)
{
    int indice_casella = 0; // Indice della casella per cui sto generando l'effetto
    int indice_testa = 0;    // Indice della testa di tabellone[indice_casella]. La testa della scala è la posizione tabellone[indice_testa] dove il giocatore arrivera dopo aver salito le scale
    int effetto = 0, max_effetto = 0, min_effetto = 0;

    for(int i = 0; i < numero_scale; i++) {
        do {
            do {
                indice_casella = genera_numero_in_range(1,  numero_caselle - 2);  // genero un indice_casella randomico compreso tra 1 e numero_caselle - 2 (perché la prima casella è la partenza e l'ultima è la vincita)
            } while (tabellone[indice_casella].effetto == 0);   // Genera finché non trovi un posto non occupato da serpenti o scale

            max_effetto = numero_caselle - indice_casella;   // La scala non può sforare superiormente la tabella
            min_effetto = 1;  // La scala per esistere deve avere grandezza almeno 1


            effetto = genera_numero_in_range(min_effetto, max_effetto); // genero randomicamente il valore dell'effetto tra min_effetto e max_effetto

            indice_testa = indice_casella + effetto; // ottengo l'indice della casella della testa della scala

        } while (tabellone[indice_testa].effetto != 0);  // Rigenero un nuovo indice_casella e di conseguenza un indice_testa finché non trovo una testa libera (non occupata da serpenti o scale)

        tabellone[indice_casella].effetto = effetto;    // assegno l'effetto generato
    }
}

int genera_numero_in_range(int min, int max)
{
    int numero = (rand() % (max - min + 1)) + min;

    return numero;
}

struct Giocatore* istanzia_giocatori(int numero_giocatori) {    //creo i giocatori e assegno la loro posizione a 0
    struct Giocatore* giocatori = (struct Giocatore*) malloc(numero_giocatori * sizeof(struct Giocatore));

    for(int i = 0; i < numero_giocatori; i++) {
        giocatori[i].id = i;
        giocatori[i].posizione = 0;
    }

    return giocatori;
}


void stampa_tabellone(struct Casella* tabellone, int numero_caselle)
{
    printf("\nTabellone effetti");
    for(int i = 0; i < numero_caselle; i++)    // Stampo il tabellone con partenza che corrisonde a t[0][0] e fine t[10][10]
    {
        if ((i % 10) == 0)
        {
            printf("\n");
        }
        printf("[%03+d]", tabellone[i].effetto);
    }
    printf("\n\n");

    printf("\nTabellone con numeri delle caselle");
    for(int i = 0; i < numero_caselle; i++)    // Stampo il tabellone con partenza che corrisonde a t[0][0] e fine t[9][9]
    {
        if ((i % 10) == 0)
        {
            printf("\n");
        }
        printf("[%03d]", tabellone[i].numero);
    }
}

struct StringArray* string_read(char *path)
{
    
    struct StringArray *stringArray;
    char array[1000];
    FILE *stream = fopen(path,"r");
    int count = 0;
    char c;

    if(stream == NULL)
    {
        printf("file non trovato o path sbagliato");
        return NULL;
    }

     while(fgets(array, 1000, stream))//contiamo il numero di righe
    {
        count++;
    }  

    stringArray = malloc(sizeof(struct StringArray) * count);//allochiamo l'array di stringhe
    rewind(stream);//riportiamo indietro il puntatore del lettore di file
    int i = 0;

    while(fgets(array, 1000, stream))//ogni giro legge una riga e la salva dentro l'array di stringhe
    {
        (stringArray[i]).array = malloc(StringLen(array)*sizeof(char));//malloca la stringa da salvare
        (stringArray[i]).n = StringLen(array);//stringlen conta i caratteri fino a quando non trova \0
        strcpy((stringArray[i]).array,array);
        i++;
    }  

    fclose(stream);
    return stringArray;
}

int lancia_dado() {
    int dado = genera_numero_in_range(1,6);
    return dado;
}

void print_table(struct Casella* tabellone, int numero_caselle, struct Giocatore* giocatori, int numero_giocatori)
{
    char cornersChar = '+', rowsChar = '-', columnsChar = '|';
    int innerCellWidth = 3, innerCellHeight = 3, tableWidth = 10, tableHeight = 10;
    int cellWidth = innerCellWidth + 1;
    int cellHeight = innerCellHeight + 1;
    int cont = 0;

    for(int y = 0; y <= (tableHeight * cellHeight); y++)
    {
        for(int x = 0; x <= (tableWidth * cellWidth); x++)
        {
            if(x % cellWidth == 0 && y % cellHeight == 0) // Cell corners
            {
                printf("%c", cornersChar);
            }
            else if(y % cellHeight == 0) // Rows
            {
                printf("%c", rowsChar);
            }
            else if(x % cellWidth == 0) // Columns
            {
                printf("%c", columnsChar);
            }
            else // Cell inside
            {
                printf("%d", tabellone[cont]);
                cont++;
            }
        }
        printf("\n");
    }
}