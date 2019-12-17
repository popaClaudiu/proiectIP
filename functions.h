#include <math.h>
#include <string.h>
#include<iostream>
#include <stdlib.h>
#define infinit 10000000000
#define epsilon 0.000000001
#define pi 3.1415926

/*
    Functii elementare din matematica
*/

bool diferitDeInfinit(float x)
{
    return (infinit - abs(x)) > infinit / 2;
}

int modul(float x)
{
    return diferitDeInfinit(x) ? abs(x) : infinit;
}

bool estePar(float x)
{
    return (modul(x) % 2) == 0;
}

bool esteImpar(float x)
{
    return !estePar(x);
}

float logaritm(float x)
{
    if (x > epsilon && diferitDeInfinit(x))
    {
        return log(x);
    }

    return infinit;
}

float exponential(float x)
{
    return diferitDeInfinit(x) ? exp(x) : infinit;
}

float Plus(float x, float y)
{
    if (diferitDeInfinit(x) && diferitDeInfinit(y))
    {
        return (x + y);
    }
    return infinit;
}

float Minus(float x, float y)
{
    if (diferitDeInfinit(x) && diferitDeInfinit(y))
    {
        return (x - y);
    }

    return infinit;
}

float inmultit(float x, float y)
{
    if (modul(x) < epsilon || modul(y) < epsilon)
    {
        return 0;
    }
    else if (diferitDeInfinit(x) && diferitDeInfinit(y))
    {
        return x * y;
    }
    else
    {
        return infinit;
    }
}

float impartit(float x, float y)
{
    return modul(y) > epsilon ? x / y : infinit;
}

float putere(float x, float y)
{
    int i, yi;
    float p;

    if (x == 0)
        return 0;
    else if (y == 0)
        return 1;
    else
    {
        
        if (!diferitDeInfinit(x) || !diferitDeInfinit(y))
            return infinit;
        else if (y == int(y))
        {            
            std::cout<<"incepem sa inmultim"<<"\n";
            yi = trunc(y);
            p = 1;
            for (i = 1; i <= (yi / 2); i++)
            {
                p *= x;
                p *= p;
                std::cout<<"p="<<p;
            }
            if (!estePar(yi)){
                p *= x; 
                std::cout<<"p="<<p;
            }

            return p;
        }
        else
        {
            return exponential(
                inmultit(y, logaritm(x)));
        }
    }
}

float sinus(float x)
{
    return diferitDeInfinit(x) ? sin(x) : infinit;
}

float cosinus(float x)
{
    return diferitDeInfinit(x) ? cos(x) : infinit;
}

float radical(float x)
{
    if (!diferitDeInfinit(x) || (x < epsilon))
    {
        return infinit;
    }

    return sqrt(x);
}

bool egal(float x, float y)
{
    return (x == y);
}

bool diferit(float x, float y)
{
    return !egal(x, y);
}

bool maiMic(float x, float y)
{
    return (x < y);
}

bool maiMare(float x, float y)
{
    return (x > y);
}

/*
    Functiile programului
*/

/*
*   Functia prioritate
*
*   prioritatea operatorului este direct proportionala de numarul asociat
*/

int prioritate(char caracter)
{
    int pr = 5;

    if (strchr("()", caracter))
    {
        pr = 0;
    }
    else if (strchr("+-", caracter))
    {
        pr = 1;
    }
    else if (strchr("*/", caracter))
    {
        pr = 2;
    }
    else if (caracter == '^') // operatorul putere
    {
        pr = 3;
    }
    else if (strchr("=#<>", caracter)) // operatori relationali
    {
        pr = 4;
    }
    else if (strchr("cslear", caracter)) // functiile cos,sin,ln,exp,abs,rad
    {
        pr = 5;
    }

    return pr;
}

bool esteIntreg(float v)
{
    return (v == int(v));
}

/*
    Functia TipCaracter

    q = constanta p
    X = variabila x
    tip = 100 pentru orice alt caracter aflat in expresie
*/

int tipCaracter(char c){
    
    int tip = 100; 
    if(strchr("0123456789.",c)){
        tip = 1;
    }
    else if(strchr("cosinlgexpabrd",c)){
        tip = 2;
    }else{
        char operatori[]="()+-*/^Xq=#<>";
        int i = 0;
        while(operatori[i]){
            if(c == operatori[i]){
                tip = 3 + i;
                break;
            }
            i++;
        }
    }

    return tip;
}

bool esteNumar(char s)
{
    if(strchr("0123456789", s)){
        return true;
    }
    return false;
}

float valoareaOperandului(char* s, int& cod)
{
    char s1[255];
    int i=0,j=0;

    for(i=0;i<strlen(s);i++){
        if(strchr("0987654321.",s[i])){
            s1[j] = s[i];
            j++;
        }
    }
    
    cod =  atof(s1);
    return atof(s1);
}