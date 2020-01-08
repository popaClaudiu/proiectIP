/**
 * #############################
 *  Evaluator matematic        *
 * #############################
 *  Realizat de : Popa Claudiu *
 *                    si       *
 *                Rosca Victor *
 * #############################
*/
#define MAX_WIDTH 600
#define MAX_HEIGHT 600
#include "grafica.h"

char c2[10000],k;
int main()
{
    int window1,i;
    char c[10000],result[100];

    window1=initwindow(MAX_WIDTH,MAX_HEIGHT,"evaluatorMatematic",true,true);

    pornesteProgramul(window1);

    getch();
    closegraph();

    return 0;
}
