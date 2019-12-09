#include <iostream>
#include "functions.h"
using namespace std;

/*
* O functie este declarata sub forma unei structuri de tip inregistrare
*  expresie = expresia functiei
*  cuvinte = contine toate cuvintele ce formeaza expresia matematica
*  lungime = lungimea efectiva a vectorului
*  a,b = un interval de evaluare a functiei
*  n = numarul de puncte de evaluare
*/
struct record {
    char expresie[]; 
    char cuvinte[255][20]; 
    int lungime; 
    float a,b; 
    int n; 
};

typedef record functie;

int main()
{
    
    return 0;
}
