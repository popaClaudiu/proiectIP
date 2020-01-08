#include <iostream>
#include <stdio.h>
#define MAX_STIVA 100
#define EROARE_ESTE_O_LITERA_DUPA_O_CIFRA 2
#define EROARE_DUPA_PARANTEZA_NU_ESTE_OP_BINAR 4
#define EROARE_SIRUL_SE_TERMINA_BRUSC 3
#define EROARE_IMPARTIRE_LA_0 5
#define EROARE_RADICAL_SAU_LOGARITM_DIN_NR_NEGATIV 6
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
    char cuvinte[100][10];
    int lungime;
    float x;
};
typedef record functie;
functie E;
int greseala = 0;

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

/**
 * Scoate spatiile dintr-un sir de caractere
*/
void trimWhiteSpaces(char *s)
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
    printf("Expresia dupa stergere: %s \n", sir);
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
        E.lungime = ++lung;
        Delete(sir, 0, p);
    }

    if (p == 0)
    {
        strcpy(E.cuvinte[--lung], " )");
    }
}

/**
 * Evidentiaza variabilele din expresie
 * Pune
*/
void evidentiazaVariabilele(functie &E)
{
    printf("Evidentiez Variabilele");
    int i, n = strlen(E.expresie);
    if (esteVariabila(E.expresie[0]))
        E.expresie[0] = 'X';
    if (esteVariabila(E.expresie[n]))
        E.expresie[n] = 'X';

    for (i = 1; i < n; i++)
    {
        if (esteVariabila(E.expresie[i]))
        {
            if (nuEsteOperatorulExponent(E.expresie, i))
            {
                E.expresie[i] = 'X';
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
    printf("Pun zerouri\n");
    char s[255];
    int n;
    strcpy(s, E.expresie);
    n = strlen(s);

    if (s[0] == '+' || s[0] == '-')
    {
        desplaseazaSirul(s, n + 1, 0);
        s[0] = '0';
    }
    else if ((s[n - 1] == '+' || s[n - 1] == '-') && s[n] == '\0')
    {
        s[n] = '0';
        s[n + 1] = '\0';
    }
    else
    {
        printf("Expresia: %s\n", s);
        int k = 0, i;
        for (i = 0; i < n; i++)
        {
            if ((s[i] == ')' && strchr("+", s[i - 1]) && s[i - 1] != '\0'))
            {
                printf("s[%d]=%c\n", i, s[i]);
                printf("Expresie de tipul +) %d\n", i);
                desplaseazaSirul(s, n, i);
                s[i] = '0';
                printf("s=%s\n", s);
            }
            else if (s[i] == '(' && strchr("+", s[i + 1]) && s[i + 1] != '\0')
            {
                printf("s[%i]=%c\n", i, s[i]);
                printf("Expresie de tipul (+ %d\n", i);
                desplaseazaSirul(s, n, i);
                s[++i] = '0';
                printf("s=%s\n", s);
            }
        }
    }
    strcpy(E.expresie, s);
    printf("Expresia: %s\n", E.expresie);
}

bool esteOperatie(int t1, int t2, int i)
{
    return (!((5 <= t1 && t1 > 10) && (t2 == 1)) || (strchr("=#<>", E.expresie[i - 2])));
}

bool seAflaInParanteza(int t1, int t2, int i)
{
    return ((t1 != t2) || ((t1 == tipCaracter('(')) && (t2 == t1)) || ((t1 == tipCaracter(')')) && (t2 == t1)));
}

/*
*  Pune spatii in expresie intre caractere de tipuri diferite
*/
void puneSpatiiInExpresie(functie &E)
{
    int pozitie, t1, t2;

    puneZerouriInExpresie(E);
    evidentiazaVariabilele(E);

    pozitie = 0;
    while (pozitie < strlen(E.expresie) && strlen(E.expresie) < 256)
    {
        t1 = tipCaracter(E.expresie[pozitie]);
        t2 = tipCaracter(E.expresie[pozitie + 1]);
        if (esteOperatie(t1, t2, pozitie))
        {
            if (seAflaInParanteza(t1, t2, pozitie))
            {
                insereazaSpatiu(E, pozitie + 1);
                pozitie++;
            }
        }
        pozitie++;
    }
}

/**
 * Pregateste functia pentru evaluare
*/
void formeazaExpresia(functie &E)
{
    puneZerouriInExpresie(E);
    puneSpatiiInExpresie(E);
    transformaInVector(E);

    for (int i = 0; i < E.lungime; i++)
    {
        trimWhiteSpaces(E.cuvinte[i]);
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

    if (strchr(E.expresie, 'x'))
    {
        printf("Dati o valoare pentru x:");
        scanf("%f", &E.x);
    }
    valideazaFunctia(E);
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
        printf("E.cuv=%s\n", E.cuvinte[i]);
        if (esteNumar(*E.cuvinte[i]))
        {
            top1++;
            valoareOperand = valoareaOperandului(E.cuvinte[i], cod);
            operand[top1] = valoareOperand;
            printf("In varful stivei am adaugat constanta: %f \n", operand[top1]);
        }
        else
        {
            if (strchr("qeX(", E.cuvinte[i][0]) && E.cuvinte[i][0] != ' ' && E.cuvinte[i][1] != 'x')
            {
                switch (E.cuvinte[i][0])
                {
                case 'q':
                    top1++;
                    operand[top1] = pi;
                    printf("In varful stivei este PI: %f\n", operand[top1]);
                    break;
                case 'e':
                    top1++;
                    operand[top1] = e;
                    printf("In varful stivei este constanta Euler: %f\n", operand[top1]);
                    break;
                case 'X':
                    top1++;
                    operand[top1] = x;
                    printf("In varful stivei X este: %f\n", operand[top1]);
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
                printf("In varful stivei operatorilor este: %c\n", op[top2]);
                printf("Cuvantul:%c\n", E.cuvinte[i][0]);
                while (
                    top2 > 0 && (!strchr("()", op[top2])) &&
                    (prioritate(op[top2]) >= prioritate(E.cuvinte[i][0])))
                {
                    if (top1 > 1)
                        x_1 = operand[top1 - 1];
                    x_2 = operand[top1];
                    printf("x_2=%f\n", x_2);
                    if (strchr("=#<>+-/*^scleart", op[top2]))
                    {
                        switch (op[top2])
                        {
                        case '=':
                            printf("Egalez : %f cu %f\n", x_1, x_2);
                            valoareOperand = egal(x_1, x_2);
                            break;

                        case '#':
                            printf("Inegalez : %f cu %f\n", x_1, x_2);
                            valoareOperand = diferit(x_1, x_2);
                            break;

                        case '<':
                            cout << "Maimic";
                            printf("%f < %f\n", x_1, x_2);
                            valoareOperand = maiMic(x_1, x_2);
                            break;

                        case '>':
                            printf("%f > %f\n", x_1, x_2);
                            valoareOperand = maiMare(x_1, x_2);
                            break;

                        case '+':
                            printf("%f + %f\n", x_1, x_2);
                            valoareOperand = Plus(x_1, x_2);
                            break;

                        case '-':
                            printf("%f - %f\n", x_1, x_2);
                            valoareOperand = Minus(x_1, x_2);
                            break;

                        case '*':
                            printf("%f * %f\n", x_1, x_2);
                            valoareOperand = inmultit(x_1, x_2);
                            break;

                        case '/':
                            printf("%f / %f\n", x_1, x_2);
                            valoareOperand = impartit(x_1, x_2);
                            break;
                        case '^':
                            printf("%f^%f\n", x_1, x_2);
                            valoareOperand = putere(x_1, x_2);
                            break;
                        case 's':
                            printf("sin(%f)\n", x_2);
                            valoareOperand = sinus(x_2);
                            break;

                        case 'c':
                            printf("cosin(%f)\n", x_2);
                            valoareOperand = cosinus(x_2);
                            break;

                        case 'l':
                            printf("log(%f)\n", x_2);
                            valoareOperand = logaritm(x_2);
                            break;

                        case 'e':
                            printf("exp(%f)\n", x_2);
                            valoareOperand = exponential(x_2);
                            break;

                        case 'a':
                            printf("abs(%f)\n", x_2);
                            valoareOperand = modul(x_2);
                            break;

                        case 'r':
                            printf("rad(%f)\n", x_2);
                            valoareOperand = radical(x_2);
                            break;

                        case 't':
                            printf("tan(%f)\n", x_2);
                            valoareOperand = tangent(x_2);
                            break;
                        default:
                            break;
                        }

                        if (strchr("+-^*/><=", op[top2]) && top1 > 1)
                        {
                            printf("Scad din stiva operanzilor\n");
                            top1--;
                        }
                        if (strchr("=#<>+-/*^scleart", op[top2]) && top1 > 0)
                        {
                            printf("Scad din stiva operatorilor\n");
                            operand[top1] = valoareOperand;
                            printf("\n In varful stivei operanzilor este:%f\n", operand[top1]);
                            top2--;
                        }
                    }
                }
                if (top2 > 0 && !esteNumar(E.cuvinte[i][0]))
                {
                    printf("Top2 > 0");
                    printf("E.cuv:%c \n", E.cuvinte[i][0]);
                    if (op[top2] != '(' || E.cuvinte[i][0] != ')')
                    {
                        printf("Adaug in stiva operatorilor\n");
                        top2++;
                        op[top2] = E.cuvinte[i][0];
                        afiseazaStivaOp(op, top2);
                    }
                    else
                    {
                        printf("Scad din stiva operatorilor\n");
                        top2--;
                        afiseazaStivaOp(op, top2);
                    }
                }
            }
        }
    }

    if (top2 == 0)
    {
        printf("Returnez: %f\n", operand[1]);
        return operand[1];
    }
    else
    {
        printf("Varful stivei operanzilor:%f\n", operand[1]);
        printf("In varful stivei operatorilor top2 este:%d. top2=%d\n", op[top2], top2);
        for (int i = 0; i <= top2; i++)
        {
            cout << op[top2] << endl;
        }

        return infinit;
    }
}

void afiseazaGreseli(int greseli[2][10],int j);

bool esteOLiteraDupaOCifra(char *s, int i)
{
    return (strchr("0987654321.", s[i]) && strchr("xX", s[i + 1]) && s[i + 1] != '\0');
}

bool dupaParantezaEsteOperatorBinar(char *s, int i)
{
    return (strchr(")", s[i]) && (strchr("0987654321.", s[i + 1]) || strchr("+-*/^", s[i - 1])) && s[i + 1] != '\0');
}

bool esteImpartireLa0(char *s, int i)
{
    return (strchr("/", s[i]) && strchr("xX", s[i + 1]) && E.x == 0);
}

bool esteRadicalSauLogaritmDinNumarNegativ(char *s, int i)
{
    return (strchr("dg", s[i]) && (s[i + 2] == '-' || (strchr("xX",s[i+2]) && E.x < 0)));
}

/**
 * Valideaza expresia functiei date
*/
void valideazaFunctia(functie &E)
{
    cout << "Validez expresia: " << E.expresie << endl;
    char s[255];
    strcpy(s, E.expresie);
    int n = strlen(s), greseli[2][10], nrGreseli = 0, i;
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
            int sirulSeTerminaBrusc = 0, j;
            for (j = i + 1; j < n && !sirulSeTerminaBrusc; j++)
            {
                if (strchr("x0987654321+-*^/", s[j]) && s[j + 1] == '\0')
                {
                    sirulSeTerminaBrusc = 1;
                }
                else if (strchr("+-*^/", s[j - 1]) && s[j] == ')')
                {
                    sirulSeTerminaBrusc = 1;
                }
                if (s[j] == ')')
                {
                    break;
                }
            }
            if (sirulSeTerminaBrusc)
            {
                greseala = 1;
                greseli[0][nrGreseli] = j--;
                greseli[1][nrGreseli] = EROARE_SIRUL_SE_TERMINA_BRUSC;
                nrGreseli++;
            }
        }
        else if (esteImpartireLa0(s, i))
        {
            greseala = 1;
            greseli[0][nrGreseli] = i;
            greseli[1][nrGreseli] = EROARE_IMPARTIRE_LA_0;
            nrGreseli++;
        }
        else if (esteRadicalSauLogaritmDinNumarNegativ(s, i))
        {
            greseala = 1;
            greseli[0][nrGreseli] = i;
            greseli[1][nrGreseli] = EROARE_RADICAL_SAU_LOGARITM_DIN_NR_NEGATIV;
            nrGreseli++;
        }
    }

    if (greseala)
    {
        afiseazaGreseli(greseli, nrGreseli);
        strcpy(E.expresie, "\0");
    }
    else
    {
        printf("EXPRESIE CORECTA \n");
    }
}

/**
 * Afiseaza rezultatul expresiei
*/
void afisare(functie E)
{
    float y = valoareFunctiei(E, E.x);

    if (diferitDeInfinit(y))
    {
        printf("f(%f)=%f", E.x, y);
    }
    else
    {
        printf("f(%f)=INPUT INVALID", E.x);
    }
}

/* A utility function to reverse a string  */
void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}

void floatToString(float x , char* sir)
{
    int parte_intreaga,contor=0;
    float parte_rationala;
    char cifra[3];
    parte_intreaga = (int) x;

    while(parte_intreaga)
    {
      contor++;
      itoa(parte_intreaga%10,cifra,10);
      strcat(sir,cifra);
      parte_intreaga /= 10;
    }

    x = x / 10 * contor;

    parte_rationala = x;
    strcat(sir,".");

    parte_rationala *= 100;
    itoa((unsigned int)parte_rationala%100, cifra, 10);
    strcat(sir,cifra);


}

