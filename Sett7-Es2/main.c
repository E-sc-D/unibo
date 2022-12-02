#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>

struct Studente
{
    // Non usare 0 come numero matricola!!
    // 0 è il numero usato per indicare NULL ovvero che lo Studente non è ancora stato inserito/lo spazio è libero
    int numero_matricola;
    char nome[20];
    char cognome[20];
    int anno_immatricolazione;

    int numero_esami;
    struct PianoStudi *ptrPianoStudi;   // Questo puntatore conterrà l'array di strutture PianoStudi con indice num_esami, che verrà generato all'aggiunta dello studente
};

struct Insegnamento
{
    int codice_insegnamento;
    char descrizione[60];
    int anno_somministrazione;
    int crediti;

};

struct PianoStudi // rivedere forse il nome di questa struct
{
    int codice_insegnamento;
    int voto;
};

struct Studente * cercaStudente(int numero_studenti, struct Studente *studenti, int numero_matricola)
{
    for(int i = 0; i < numero_studenti; i++)
        if(studenti[i].numero_matricola == numero_matricola)
            return &(studenti[i]);
    return NULL;
}

void generaPianoStudi(struct Studente *studente, int numero_insegnamenti, struct Insegnamento *insegnamenti)
{
    system("cls");
    printf("Piano studi:\n");

    printf("Insegnamenti disponibili");
    for (int i = 0; i < numero_insegnamenti; i++)
        printf("\n%d. %s", insegnamenti[i].codice_insegnamento, insegnamenti[i].descrizione);   // esempio: 1. Analisi 1 \n 2. Programmazione \n 3. Sistemi Operativi

    printf("\n");

    studente->ptrPianoStudi = (struct PianoStudi *) malloc(studente->numero_esami * sizeof(struct PianoStudi));
    int i = 0;
    int uscita = 0;
    while(i < studente->numero_esami && uscita == 0)
    {
        printf("\nIterazione n. %d", i);
        int scelta;
        do
        {
            printf("\nSeleziona un insegnamento da aggiungere al piano studi\n\r");
            printf("(range valori accettabili: [1, %d])\n\r", numero_insegnamenti);
            scanf("%d", &scelta);
        }
        while(scelta < 1 || scelta > numero_insegnamenti);

        int voto;
        do
        {
            printf("\nInserisci il voto da aggiungere per %s (0 se non ancora svolto)\n\r", insegnamenti[scelta - 1].descrizione);
            printf("(range valore accettabili: [0, 30])\n\r");
            scanf("%d", &voto);
        }
        while(voto < 0 || voto > 30);

        studente->ptrPianoStudi[i].codice_insegnamento = insegnamenti[scelta - 1].codice_insegnamento;
        studente->ptrPianoStudi[i].voto = voto;

        i++;

        printf("\nVuoi continuare a modificare il piano di studi? (0 per continuare)\n\r", insegnamenti[scelta - 1].descrizione);
        printf("(rimangono %d posti disponibili nel tuo piano di studi)\n\r", studente->numero_esami - i);
        scanf("%d", &uscita);
    }
}

void aggiungiStudente(struct Studente *studenti, int numero_studenti, int numero_insegnamenti, struct Insegnamento *insegnamenti)
{
    int indiceStudente = 0;
    int flag = 0;
    for (indiceStudente = 0; indiceStudente < numero_studenti; indiceStudente++)
    {
        if (studenti[indiceStudente].numero_matricola == 0)
        {
            flag = 1;   // trovato un posto libero di indice "indiceStudente"
            break;
        }
    }

    if (flag == 0)
    {
        printf("Attenzione: il vettore di studenti e completo. Non si possono aggiungere ulteriori studenti");
        printf("\nPremi invio per tornare al menu principale");
        getch();
        return;
    }

    struct Studente s;
    printf("Inserisci il numero matricola dello studente\n\r");
    scanf("%d", &s.numero_matricola);

    while(s.numero_matricola == 0)
    {
        printf("\nAttenzione! Non puoi inserire 0 come numero matricola. Riprova"); // 0 corrisponde a null

        printf("Inserisci il numero matricola dello studente\n\r");
        scanf("%d", &s.numero_matricola);
    }

    if (cercaStudente(numero_studenti, studenti, s.numero_matricola) != NULL)
    {
        printf("\nErrore: lo studente inserito e gia presente! Premi invio per tornare al menu principale");
        getch();
        return;
    }

    printf("\nInserisci il nome dello studente\n\r");
    scanf("%s", &s.nome);

    printf("\nInserisci il cognome dello studente\n\r");
    scanf("%s", &s.cognome);

    printf("\nInserisci l'anno di immatricolazione dello studente\n\r");
    scanf("%d", &s.anno_immatricolazione);

    printf("\nInserisci il numero di esami dello studente\n\r");
    scanf("%d", &s.numero_esami);

    generaPianoStudi(&s, numero_insegnamenti, insegnamenti);

    studenti[indiceStudente] = s;
    printf("\nStudente aggiunto correttamente!");
}

void aggiungiVotoAPianoStudi(struct Studente *studente, int numero_insegnamenti, struct Insegnamento *insegnamenti)
{
    if (studente == NULL)
        return;
    
    int scelta;
    do
    {
        printf("\nSeleziona un insegnamento da aggiungere al piano studi\n\r");
        printf("(range valori accettabili: [1, %d])\n\r", numero_insegnamenti);
        scanf("%d", &scelta);
    }
    while(scelta < 1 || scelta > numero_insegnamenti);

    int voto;
    do
    {
        printf("\nInserisci il voto da aggiungere per %s (0 se non ancora svolto)\n\r", insegnamenti[scelta - 1].descrizione);
        printf("(range valore accettabili: [0, 30])\n\r");
        scanf("%d", &voto);
    }
    while(voto < 0 || voto > 30);

    int i = 0;
    

    studente->ptrPianoStudi[i].codice_insegnamento = insegnamenti[scelta - 1].codice_insegnamento;
    studente->ptrPianoStudi[i].voto = voto;

}

void mostraInfoStudente(struct Studente *studente)
{
    if (studente == NULL)
        return;

    system("cls");
    printf("\nNumero matricola: %d", studente->numero_matricola);
    printf("\nNome: %s", studente->nome);
    printf("\nCognome: %s", studente->cognome);
    printf("\nAnno di immatricolazione: %d", studente->anno_immatricolazione);

    printf("\n\rPremi invio per tornare al menu principale\n\r");
    getch();
}

void azzeraStudente(struct Studente *studente)
{
    studente->numero_matricola = 0;
    strcpy(studente->nome, "");
    strcpy(studente->cognome, "");
    studente->anno_immatricolazione = 0;
    studente->numero_esami = 0;
    studente->ptrPianoStudi = NULL;
}

void azzeraStudenti(int numero_studenti, struct Studente *studenti)
{
    for(int i = 0; i < numero_studenti; i++)
        azzeraStudente(&(studenti[i]));
}

int main ()
{
    struct Insegnamento insegnamenti[3] =
    {
        { 1, "Analisi 1", 2022, 6 },
        { 2, "Programmazione", 2022, 6 },
        { 3, "Sistemi operativi", 2022, 6 }
    };

    int numero_studenti = 10;
    struct Studente *studenti = (struct Studente *) malloc(numero_studenti * sizeof(struct Studente));   // creo un array di numero_studenti strutture

    azzeraStudenti(numero_studenti, studenti);

    printf("%d\n", *studenti);
    printf("%d\n", studenti);

    aggiungiStudente(studenti, numero_studenti, sizeof(insegnamenti) / sizeof(struct Insegnamento), insegnamenti);

    return 0;
}