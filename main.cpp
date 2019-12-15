#include <iostream>

#include "functions.h"
using namespace std;
#define MAX_STIVA 100

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
    char cuvinte[100][10];
    int lungime;
    float a, b;
    int n;
};

typedef record functie;
functie E;

void afiseazaCuvinte()
{
    for (int i = 0; i < E.lungime; i++)
    {

        cout << "i" << i << "-" << E.cuvinte[i];

        cout << endl;
    }
}

void afiseazaStivaOp(char op[], int top)
{
    for (int i = 0; i <= top; i++)
    {
        cout << op[i];
    }
}

void trim(char *s)
{
    char a[10];
    int j = 0;

    for (int i = 0; i < 5; i++)
    {
        if (s[i] != ' ')
        {
            a[j] = s[i];
            j++;
        }
    }
    strncpy(s, a, 4);
}

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
        if (s[i] != ' ')
        {
            s[j++] = sir[i];
        }
    }
}

/**
 * Sterge un cuvant de lungime stop-start
*/
void Delete(char *sir, int start, int stop)
{
    strcpy(sir, sir + start + stop + 1);
    cout << "Expresia dupa stergere:" << sir << endl;
    afiseazaCuvinte();
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
        Copy(E.cuvinte[lung], sir, 0, p);
        lung++;
        E.lungime = lung;
        Delete(sir, 0, p);
    }

    if (p == 0)
    {
        strcpy(E.cuvinte[--lung], " )");
    }
}

void evidentiazaVariabilele(functie &E)
{
    int i;
    if (E.expresie[0] == 'x')
        E.expresie[0] = 'X';
    if (E.expresie[strlen(E.expresie)] == 'x')
        E.expresie[strlen(E.expresie)] = 'X';

    for (i = 0; i < strlen(E.expresie); i++)
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
*  Pune spatii in expresie intre caractere de tipuri diferite
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
        if (!((5 <= t1 && t1 > 10) && (t2 == 1)) || (strchr("=#<>", E.expresie[i - 2])))
        {

            if ((t1 != t2) || ((t1 == tipCaracter('(')) && (t2 == t1)) || ((t1 == tipCaracter(')')) && (t2 == t1)))
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
void citesteFuntie(functie &E)
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
    afiseazaCuvinte();

    for (int i = 0; i < E.lungime; i++)
    {
        trim(E.cuvinte[i]);
    }
}

/**
 *  Returneaza valoare functiei in punctul x
*/
float valoareFunctiei(functie E, float x)
{
    float valoareOperand, x_1, x_2;
    int i, cod;
    int top1, top2;           // varfurile celor doua stive
    float operand[MAX_STIVA]; // stiva operanzilor
    char op[MAX_STIVA];       // stiva operatorilor

    for (i = 0; i < MAX_STIVA; i++)
    {
        operand[i] = 0;
        op[i] = '@';
    }

    top1 = 0;
    top2 = 1;
    op[top2] = '(';
    i = -1;
    E.lungime++;
    while (i < E.lungime && top2 > 0)
    {
        i++;
        cout << endl
             << "E.cuv=" << E.cuvinte[i] << endl;
        if (esteNumar(*E.cuvinte[i]))
        {
            top1++;
            valoareOperand = valoareaOperandului(E.cuvinte[i], cod);
            operand[top1] = valoareOperand;
            cout << "In varful stivei am adaugat constanta:" << operand[top1] << endl;
        }
        else
        {
            cout << "Am intrat in else" << endl;
            if (strchr("qX(", E.cuvinte[i][0]) && E.cuvinte[i][0] != ' ')
            {
                cout << "Am intrat in if2" << endl;
                switch (E.cuvinte[i][0])
                {
                case 'q':
                    top1++;
                    operand[top1] = pi;
                    cout << "In varful stivei PI este :" << operand[top1] << endl;
                    break;
                case 'X':
                    top1++;
                    operand[top1] = x;
                    cout << "In varful stivei X este:" << operand[top1] << endl;
                    break;
                case '(':
                    top2++;
                    op[top2] = '(';
                    break;
                default:
                    break;
                }
            }
            else
            {
                cout << "Am intrat in else 2" << endl;
                cout << "Operatorul din varful stivei:" << op[top2] << endl;
                cout << "Cuvantul:" << E.cuvinte[i][0] << endl;

                while (
                    top2 > 0 && (!strchr("()", op[top2])) &&
                    (prioritate(op[top2]) >= prioritate(E.cuvinte[i][0])))
                {
                    cout << "Am intrat in while" << endl;
                    if (top1 > 1)
                        x_1 = operand[top1 - 1];
                    x_2 = operand[top1];
                    // break;
                    cout << "x_2=" << x_2 << endl;
                    if (strchr("=#<>+-/*^sclear", op[top2]))
                    {
                        switch (op[top2])
                        {
                        case '=':
                            cout << "Egalez";
                            valoareOperand = egal(x_1, x_2);
                            break;

                        case '#':
                            cout << "InEgalez";
                            valoareOperand = diferit(x_1, x_2);
                            break;

                        case '<':
                            cout << "Maimic";
                            valoareOperand = maiMic(x_1, x_2);
                            break;

                        case '>':
                            cout << "MaiMare";
                            valoareOperand = maiMare(x_1, x_2);
                            break;

                        case '+':
                            cout << "Adun:" << x_1 << "+" << x_2;
                            valoareOperand = Plus(x_1, x_2);
                            break;

                        case '-':
                            cout << "Scad";
                            valoareOperand = Minus(x_1, x_2);
                            break;

                        case '*':
                            cout << "Inmultesc";
                            valoareOperand = inmultit(x_1, x_2);
                            break;

                        case '/':
                            cout << "Impart";
                            valoareOperand = impartit(x_1, x_2);
                            break;
                        case '^':
                            cout << "Putere:" << x_1 << "^" << x_2;
                            valoareOperand = putere(x_1, x_2);
                            break;
                        case 's':
                            cout << "Sinus";
                            valoareOperand = sinus(x_2);
                            break;

                        case 'c':
                            cout << "Cosinus";
                            valoareOperand = cosinus(x_2);
                            break;

                        case 'l':
                            cout << "Logaritm";
                            valoareOperand = logaritm(x_2);
                            break;

                        case 'e':
                            cout << "Exponentiala";
                            valoareOperand = exponential(x_2);
                            break;

                        case 'a':
                            cout << "Modul";
                            valoareOperand = modul(x_2);
                            break;

                        case 'r':
                            cout << "radical";
                            valoareOperand = radical(x_2);
                            break;
                        default:
                            break;
                        }

                        if (strchr("+-^*/><=", op[top2]) && top1 > 1)
                        {
                            cout << "Am intrat in if 3" << endl;
                            top1--;
                        }
                        if (strchr("=#<>+-/*^sclear", op[top2]) && top1 > 0)
                        {
                            cout << "Am intrat in if 4" << endl;
                            operand[top1] = valoareOperand;
                            cout << endl
                                 << "In varful stivei este operanzilor:" << operand[top1] << endl;
                            top2--;
                        }
                    }
                }
                if (top2 > 0 && !esteNumar(E.cuvinte[i][0]))
                {
                    cout << endl
                         << "Top2>0" << endl;
                    cout << "Ecuv:" << E.cuvinte[i][0];
                    cout << endl;
                    if (op[top2] != '(' || E.cuvinte[i][0] != ')')
                    {
                        cout << "Adaug in stiva operatorilor" << endl;
                        top2++;
                        op[top2] = E.cuvinte[i][0];
                        afiseazaStivaOp(op, top2);
                    }
                    else
                    {
                        cout << "Scad din stiva operatorilor" << endl;
                        top2--;
                        afiseazaStivaOp(op, top2);
                    }
                }
            }
        }
    }

    if (top2 == 0)
    {
        cout << "Returnez:" << operand[1] << endl;
        return operand[1];
    }
    else
    {
        cout << "Varful stivei operanzilor:" << operand[1] << endl;
        cout << "In varful stivei top2 este:" << op[top2] << " top2=" << top2 << endl;

        for (int i = 0; i <= top2; i++)
        {
            cout << op[top2] << endl;
        }

        return infinit;
    }
}

void afisare(functie E)
{
    int i;
    float x, y;
    for (i = 0; i <= E.lungime; i++)
    {
        x = E.a + i * (E.b - E.a) / (E.n - 1);
        y = valoareFunctiei(E, x);
        if (diferitDeInfinit(y))
            cout << (i + 1) << "->" << x << "->" << y;
        else
            cout << i + 1 << "." << x << "->nedefinit !";
    }
}

int main()
{

    citesteFuntie(E);
    cout << "Expresia:" << E.expresie << endl;
    afiseazaCuvinte();

    afisare(E);

    return 0;
}
