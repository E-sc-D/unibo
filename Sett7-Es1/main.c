#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void robConnect();
int robConfig();
int verificaDuplicato();
void azzeraStruct();
void mostraInfoStanza();
void aggiungiStanza();
void robDisconnect();
struct Stanza {
    char nome[20];
    int larghezza;
    int lunghezza;
    int area;
    int ostacoli;
    int priorita;
};

int main() {

    int numero_stanze = 5;
    //robConnect();    // connettiti al robot (loading)
    //int numero_stanze = robConfig(); // uso robConfig() per chiedere all'utente il numero di stanze

    struct Stanza *ptrStanza = (struct Stanza *) malloc(numero_stanze * sizeof(struct Stanza));

    azzeraStruct(ptrStanza, numero_stanze);


    aggiungiStanza(ptrStanza, numero_stanze);
    mostraInfoStanza("Paolo", ptrStanza, numero_stanze);




    return 0;
}

void robConnect() { // Funzione che simula l'effetto di caricamento
    
    int percentage = 0;
    char loading[] = "--------------------";
    
   while (percentage <= 100) {
       printf("\t\tConnessione a Rob8");
       printf("\n\t\t");

       for (int i = 0; i < strlen(loading); i++) {
           printf("%c", loading[i]);
       }
       
       loading[percentage/5] = 'o';
       
       printf(" %d%%", percentage);
       
       percentage += 5;
       
       usleep(50 * 1000);    // 50 millisecondi (50*1000 microsecondi)
       system("cls");
   }
}

int robConfig() {   // Funzione che chiede all'utente quante stanze ci sono nella casa e torna il loro numero
    int numero_stanze;

    printf("\nBenvenuto nella pagina di configurazione");
    printf("\nInserisci il numero di stanze presenti nella tua casa");
    scanf("%d", &numero_stanze);


    return numero_stanze;
}


void aggiungiStanza(struct Stanza *ptrStanza, int numero_stanze) {
    int flag = 0;
    int i = 0;
    for (i = 0; i < numero_stanze; i++) {
        if (strcmp(ptrStanza[i].nome, "") == 0) {
            flag = 1;   // trovato un posto libero "i"
            break;
        }
    }

    if (flag = 0) {
        printf("Attenzione: il vettore di stanze e completo. Non si possono aggiungere ulteriori stanze");
        return;
    }

    struct Stanza s;
    printf("Inserisci il nome della stanza");
    scanf("%s", &s.nome);

    if (verificaDuplicato(*ptrStanza, numero_stanze, s.nome) == 1){
        printf("\nErrore: la stanza inserita e gia presente!");
        return;
    }

    printf("\nInserisci la larghezza della stanza");
    scanf("%d", &s.larghezza);

    printf("\nInserisci la lunghezza della stanza");
    scanf("%d", &s.lunghezza);

    printf("\nInserisci l'area della stanza");
    scanf("%d", &s.area);

    printf("\nInserisci il numero di ostacoli della stanza");
    scanf("%d", &s.ostacoli);

    printf("\nInserisci la priorita di pulizia della stanza");
    scanf("%d", &s.priorita);

    ptrStanza[i] = s;   // i è l'indice della struttura non occupata

    //calcolaPriorita?

}

void mostraInfoStanza(char nomeStanza[], struct Stanza *ptrStanza, int numero_stanze) { // Funzione che stampa le informazioni di una stanza dato il nome
    int i = 0;
    int flag = 0;
    for(i = 0; i < numero_stanze; i++) {
        if (strcmp(nomeStanza, ptrStanza[i].nome) == 0){    // Cerco la stanza con il nome inserito dall'utente
            flag = 1;   // è stata trovata una stanza con il nome insterito
            break;
        }
    }

    if (flag == 0) {
        printf("\nNon e stata trovata una stanza con il nome inserito");
        return;
    }

    printf("\nNome: %s", ptrStanza[i].nome);
    printf("\nStanza numero: %d", i);
    printf("\nNome: %s", ptrStanza[i].nome);
    printf("\nLarghezza: %d", ptrStanza[i].larghezza);
    printf("\nLunghezza: %d", ptrStanza[i].lunghezza);
    printf("\nArea: %d", ptrStanza[i].area);
    printf("\nOstacoli: %d", ptrStanza[i].ostacoli);
    printf("\nPriorita: %d", ptrStanza[i].priorita);
}

int verificaDuplicato(struct Stanza *ptrStanza, int numero_stanze, char nome[]) {   // Funzione che dato il nome della stanza controlla se ci sono duplicati
    int flag = 0;
    for(int i = 0; i < numero_stanze; i++) {
        if (strcmp(ptrStanza[i].nome, nome) == 0) {
            return 1;   // esiste un duplicato
        }
    }

    return 0;   // non ci sono duplicati
}

void azzeraStruct(struct Stanza *ptrStanza, int numero_stanze) {
    for (int i = 0; i < numero_stanze; i++) {
        strcpy(ptrStanza[i].nome, "");  // corrisponde a ptrStanza[i].nome = ""; che pero non si puo fare
        ptrStanza[i].larghezza = 0;
        ptrStanza[i].lunghezza = 0;
        ptrStanza[i].area = 0;
        ptrStanza[i].ostacoli = 0;
        ptrStanza[i].priorita = 0;
    }
}

void robDisconnect(){
    system("cls");
    printf("Disconnessione avvenuta con successo.");
    exit(0); //programma terminato correttamente
}