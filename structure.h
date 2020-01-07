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