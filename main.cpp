#include <iostream>
#include "functions.h"
using namespace std;

/**
* O functie este declarata sub forma unei structuri de tip inregistrare
*  expresie = expresia functiei
*  cuvinte = contine toate cuvintele ce formeaza expresia matematica
*  lungime = lungimea efectiva a vectorului
*  a,b = un interval de evaluare a functiei
*  n = numarul de puncte de evaluare
*/
struct record
{
    char expresie[256];
    char cuvinte[255][20];
    int lungime;
    float a, b;
    int n;
} E;

typedef record functie;

/**
 * Transforma un sir de caractere  din litere mari in litere mici si returneaza sirul transformat
*/
char *lower(char sir[])
{
    int i = 0;
    while (sir[i] != 0)
    {
        if (sir[i] >= 'A' && sir[i] <= 'Z')
            sir[i] += 32;
        i++;
    }

    return sir;
}

/**
 * Returneaza pozitia unui caracter dintr-un sir de caractere
*/
int Pos(char caracter, char v[255])
{
    int pos = 0;

    for (int i = 0; i < strlen(v) && pos == 0; i++)
    {
        if (v[i] == caracter)
            pos = i;
    }
    return pos;
}

/**
 * Insereaza spatiu la o pozitie data
*/
void insereazaSpatiu(functie &E, int k)
{
    int lung = strlen(E.expresie) + 1; // de refacut
    char s[255];
    
    strcpy(s, E.expresie);
    for (int i = lung; i > k; i--)
    {
        s[i] = s[i - 1];
    }
    s[k] = ' ';

    strcpy(E.expresie, s);
}

/**
 * Copie un cuvant de lungime stop-start
*/
void Copy(char *s, char sir[255], int start, int stop)
{
    int j = 0;
    int i;
    for (i = start; i < stop; i++)
    {
        s[j] = sir[i];
        j++;
    }
}

/**
 * Sterge un cuvant de lungime stop-start
*/
void Delete(char *sir, int start, int stop)
{
    strcpy(sir, sir + start + stop);
}

/*
* Transforma In Vector
* desparte in cuvinte E.expresie, memorand cuvintele in E.cuvinte
*/
void transformaInVector(functie &E)
{
    int p = 1;
    char sir[256];

    strcat(E.expresie, " )");
    strcpy(sir, E.expresie);
    int lung = 0;

    while (sir != 0 && p != 0)
    {
        p = Pos(' ', sir);
        lung++;
        Copy(E.cuvinte[lung], sir, 0, p);
        Delete(sir, 0, p);
    }

    E.lungime = lung;
}

void evidentiazaVariabilele(functie &E)
{
    int i;
    if (E.expresie[1] == 'x')
        E.expresie[1] = 'X';
    if (E.expresie[strlen(E.expresie)] == 'x')
        E.expresie[strlen(E.expresie)] = 'X';
        

    for (i = 1; i < strlen(E.expresie); i++)
    {
        if (E.expresie[i] == 'x')
        {
            if (i < strlen(E.expresie) && i > 1)
            {
                if (E.expresie[i - 1] != 'e' && E.expresie[i + 1] != 'p')
                {
                    E.expresie[i] = 'X';
                }
            }
        }
    }
}

/*
    Pune spatii in expresie intre caractere de tipuri diferite
*/

void puneSpatiiInExpresie(functie &E)
{
    int i, t1, t2;

    evidentiazaVariabilele(E);

    i = 0;
    while (i < strlen(E.expresie) && strlen(E.expresie) < 256)
    {
        t1 = tipCaracter(E.expresie[i]);
        t2 = tipCaracter(E.expresie[i + 1]);
        if ( !((5 <= t1 && t1 > 10 ) && (t2 == 1)) || (strchr("=#<>", E.expresie[i - 2])) )
        {
            if( (t1 != t2) || ((t1 == tipCaracter('(')) && (t2 == t1)) || ((t1 == tipCaracter(')')) && (t2 == t1)))
            {
                insereazaSpatiu(E, i + 1);
                i++;
            }
        }
        i++;
    }
}

/*
 *    Citeste functia
*/
void citesteFuntie(functie& E)
{
    printf("Dati expresia!\n");
    printf("f(x)=");
    cin.getline(E.expresie, 255);
    strcpy(E.expresie, lower(E.expresie));

    printf("Dati intervalul !\n");
    printf("a=");
    scanf("%f", &E.a);
    printf("b=");
    scanf("%f", &E.b);

    printf("Dati nr. de puncte = ");
    scanf("%d", &E.n);

    puneSpatiiInExpresie(E);
    transformaInVector(E);
}

int main()
{   
    
    return 0;
}
