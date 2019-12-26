/**
 * #############################
 *  Evaluator matematic        *
 * #############################
 *  Realizat de : Popa Claudiu *
 *                    si       *
 *                Rosca Victor *
 * #############################
*/

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <conio.h>
#include "grafica.h"
#include "functions.h"

using namespace std;
#define MAX_STIVA 100
#define EROARE_ESTE_O_LITERA_DUPA_O_CIFRA 2
#define EROARE_DUPA_PARANTEZA_NU_ESTE_OP_BINAR 4
#define EROARE_SIRUL_SE_TERMINA_BRUSC 3
#define EROARE_IMPARTIRE_LA_0 5

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
    float x;
    // float a, b;
    // int n;
};

typedef record functie;
functie E;
void citesteFunctie(functie &E);
void formeazaExpresia(functie &E);
void valideazaFunctia(functie &E);
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
    int lung = strlen(E.expresie) + 1;
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
    cout << "Evidentiez variabile";
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

/**
 * Pune zerouri in expresie
 * Eg: (- => (0+ , (+ => (0+
 *
*/
void puneZerouriInExpresie(functie &E)
{
    cout << "zerori" << endl;
    char s[255];
    int n;
    strcpy(s, E.expresie);
    n = strlen(s);

    if (s[0] == '+' || s[0] == '-')
    {
        for (int i = n + 1; i > 0; i--)
        {
            s[i] = s[i - 1];
        }
        s[0] = '0';
    }
    else if ((s[n - 1] == '+' || s[n - 1] == '-') && s[n] == '\0')
    {
        s[n] = '0';
        s[n + 1] = '\0';
    }
    else
    {
        cout << "Expresia:" << s;
        int k = 0, i;
        for (i = 0; i < n; i++)
        {
            if ((s[i] == ')' && strchr("+", s[i - 1]) && s[i - 1] != '\0'))
            {
                cout << "s[i]=" << s[i] << endl;
                cout << "Expresie +):" << i << endl;
                for (k = n; k > i; k--)
                {
                    s[k] = s[k - 1];
                }
                s[i] = '0';

                cout << "s=" << s;
            }
            else if (s[i] == '(' && strchr("+", s[i + 1]) && s[i + 1] != '\0')
            {
                cout << "s[i]=" << s[i] << endl;
                cout << "Expresie (+:" << i << endl;
                for (k = n; k > i; k--)
                {
                    s[k] = s[k - 1];
                }
                s[++i] = '0';

                cout << "s=" << s;
            }
        }
    }

    strcpy(E.expresie, s);
    cout << "Expresia:" << E.expresie << endl;
}

/*
*  Pune spatii in expresie intre caractere de tipuri diferite
*/

void puneSpatiiInExpresie(functie &E)
{
    int i, t1, t2;

    valideazaFunctia(E);
    puneZerouriInExpresie(E);
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

void formeazaExpresia(functie &E)
{
    puneZerouriInExpresie(E);
    puneSpatiiInExpresie(E);
    transformaInVector(E);

    for (int i = 0; i < E.lungime; i++) // Scot spatiile din fiecare cuvant
    {
        trim(E.cuvinte[i]);
    }
}

/*
 *    Citeste functia
*/
void citesteFunctie(functie &E)
{
    printf("Dati expresia!\n");
    printf("f(x)=");
    scanf("%s", E.expresie);
    strcpy(E.expresie, lower(E.expresie));

    if(strchr(E.expresie,'x')){
        printf("Dati o valoare pentru x:");
        scanf("%f", &E.x);
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
            if (strchr("qeX(", E.cuvinte[i][0]) && E.cuvinte[i][0] != ' ')
            {
                cout << "Am intrat in if2" << endl;
                switch (E.cuvinte[i][0])
                {
                case 'q':
                    top1++;
                    operand[top1] = pi;
                    cout << "In varful stivei PI este :" << operand[top1] << endl;
                    break;
                case 'e':
                    top1++;
                    operand[top1] = e;
                    cout << "In varful stivei este constanta Euler :" << operand[top1] << endl;
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
                    cout << "x_2=" << x_2 << endl;
                    if (strchr("=#<>+-/*^sclear", op[top2]))
                    {
                        switch (op[top2])
                        {
                        case '=':
                            printf("Egalez : %f cu %f\n",x_1,x_2);
                            valoareOperand = egal(x_1, x_2);
                            break;

                        case '#':
                            printf("Inegalez : %f cu %f\n",x_1,x_2);
                            valoareOperand = diferit(x_1, x_2);
                            break;

                        case '<':
                            cout << "Maimic";
                            printf("%f < %f\n",x_1,x_2);
                            valoareOperand = maiMic(x_1, x_2);
                            break;

                        case '>':
                            printf("%f > %f\n",x_1,x_2);
                            valoareOperand = maiMare(x_1, x_2);
                            break;

                        case '+':
                            printf("%f + %f\n",x_1,x_2);
                            valoareOperand = Plus(x_1, x_2);
                            break;

                        case '-':
                            printf("%f - %f\n",x_1,x_2);
                            valoareOperand = Minus(x_1, x_2);
                            break;

                        case '*':
                            printf("%f * %f\n",x_1,x_2);
                            valoareOperand = inmultit(x_1, x_2);
                            break;

                        case '/':
                            printf("%f / %f\n",x_1,x_2);
                            valoareOperand = impartit(x_1, x_2);
                            break;
                        case '^':
                            printf("%f^%f\n",x_1,x_2);
                            valoareOperand = putere(x_1, x_2);
                            break;
                        case 's':
                            printf("sin(%f)\n",x_2);
                            valoareOperand = sinus(x_2);
                            break;

                        case 'c':
                            printf("cosin(%f)\n",x_2);
                            valoareOperand = cosinus(x_2);
                            break;

                        case 'l':
                            printf("log(%f)\n",x_2);
                            valoareOperand = logaritm(x_2);
                            break;

                        case 'e':
                            printf("exp(%f)\n",x_2);
                            valoareOperand = exponential(x_2);
                            break;

                        case 'a':
                            printf("abs(%f)\n",x_2);
                            valoareOperand = modul(x_2);
                            break;

                        case 'r':
                            printf("rad(%f)\n",x_2);
                            valoareOperand = radical(x_2);
                            break;
                        default:
                            break;
                        }

                        if (strchr("+-^*/><=", op[top2]) && top1 > 1)
                        {
                            cout << "Am intrat in if 3. Scad din stiva operatorilor" << endl;
                            top1--;
                        }
                        if (strchr("=#<>+-/*^sclear", op[top2]) && top1 > 0)
                        {
                            cout << "Am intrat in if 4. Scad din stiva operanzilor" << endl;
                            operand[top1] = valoareOperand;
                            cout << endl
                                 << "In varful stivei operanzilor este:" << operand[top1] << endl;
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

/**
 * Afiseaza greselile gasite in expresia functiei
*/
void afiseazaGreseli(int greseli[2][10], int j){
    for (int i = 0; i < j; i++)
    {
        switch (greseli[1][i])
        {
        case EROARE_ESTE_O_LITERA_DUPA_O_CIFRA:
            printf("La pozitia %d. Dupa o cifra nu poate urma  o litera.\n", greseli[0][i]);
            break;

        case EROARE_SIRUL_SE_TERMINA_BRUSC:
            printf("La pozitia %d. Dupa o ( sirul se termina brusc.\n", greseli[0][i]);
            break;
        case EROARE_DUPA_PARANTEZA_NU_ESTE_OP_BINAR:
            printf("La pozitia %d. Dupa o ) nu poate urma un numar sau paranteza se termina brusc.\n", greseli[0][i]);
            break;
        case EROARE_IMPARTIRE_LA_0:
            printf("La pozitia %d. Nu poti imparti la 0.\n", greseli[0][i]);
            break;
        }
    }
}

bool esteOLiteraDupaOCifra(char *s, int i)
{
    return (strchr("0987654321.", s[i]) && strchr("x", s[i + 1]) && s[i + 1] != '\0');
}

bool dupaParantezaEsteOperatorBinar(char *s, int i)
{
    return (strchr(")", s[i]) && (strchr("0987654321.", s[i + 1]) || strchr("+-*/^", s[i - 1])) && s[i + 1] != '\0');
}
bool esteImpartireLa0(char *s, int i)
{
    return (strchr("/",s[i]) && strchr("x",s[i+1]) && E.x == 0);
}
/**
 * Valideaza expresia functiei date
*/
void valideazaFunctia(functie &E)
{
    cout << "Validez expresia: " << E.expresie << endl;
    char s[255];
    strcpy(s, E.expresie);
    int n = strlen(s), greseli[2][10], nrGreseli = 0, i, greseala = 0;
    for (i = 0; i < 10; i++)
    {
        greseli[0][i] = 0;
        greseli[1][i] = 0;
    }
    for (i = 0; i < n; i++)
    {
        if (esteOLiteraDupaOCifra(s, i))
        {
            greseala = 1;
            greseli[0][nrGreseli] = i;
            greseli[1][nrGreseli] = EROARE_ESTE_O_LITERA_DUPA_O_CIFRA;
            nrGreseli++;
        }
        else if (dupaParantezaEsteOperatorBinar(s, i))
        {
            greseala = 1;
            greseli[0][nrGreseli] = i;
            greseli[1][nrGreseli] = EROARE_DUPA_PARANTEZA_NU_ESTE_OP_BINAR;
            nrGreseli++;
        }
        else if (strchr("(", s[i]))
        {
            int sirulSeTerminaBrusc = 0;
            for (int nrGreseli = i + 1; nrGreseli < n && !sirulSeTerminaBrusc; nrGreseli++)
            {
                if (strchr("x0987654321+-*^/", s[nrGreseli]) && s[nrGreseli + 1] == '\0')
                {
                    sirulSeTerminaBrusc = 1;
                }
            }
            if (sirulSeTerminaBrusc)
            {
                greseala = 1;
                greseli[0][nrGreseli] = i;
                greseli[1][nrGreseli] = EROARE_SIRUL_SE_TERMINA_BRUSC;
                nrGreseli++;
            }
        }else if(esteImpartireLa0(s,i)){
                greseala = 1;
                greseli[0][nrGreseli] = i;
                greseli[1][nrGreseli] = EROARE_IMPARTIRE_LA_0;
                nrGreseli++;
        }
    }

    if (greseala)
    {
        afiseazaGreseli(greseli,nrGreseli);
        strcpy(E.expresie, "\0");
        citesteFunctie(E);
        formeazaExpresia(E);
    }else{
        cout << "EXPRESIE CORECTA";
    }
}


void afisare(functie E)
{
    float y = valoareFunctiei(E, E.x);

    if (diferitDeInfinit(y))
    {
        printf("f(%f)=%f", E.x, y);
    }
    else
    {
        printf("f(%f)=nedefinit", E.x);
    }
}

char c2[10000],k;

int main()
{
    int window1,i;
    char c[10000],result[100];

    citesteFunctie(E);
    afiseazaCuvinte();

    afisare(E);


   // window1=initwindow(600,600,"evaluatorMatematic",true,true);

   /* cin>>k;

    settextstyle(BOLD_FONT,HORIZ_DIR,2);
    outtextxy(150,205,"Valoare Functie/f(x)");
    rectangle(0,235,600,265);//Dreptunghi sub textul Valoare Functie/f(x)
    for(i=50; i<=600; i=i+50)
        line(i,235,i,265);

    for(i=0;i<=11;i++)
        citireX2(window1,k,i);*/
    //cinTastatura(window1,c);

    //citesteString(window1);

    /*settextstyle(BOLD_FONT,HORIZ_DIR,2);
    outtextxy(150,151,"Citeste Necunoscuta X");
    rectangle(0,172,600,200);//Dreptunghide sub textul Citeste Necunoscuta X
    for(i=50; i<=600; i=i+50)
        line(i,172,i,200);*/


    //citesteString(window1);

    getch();
    closegraph();
    return 0;
}
