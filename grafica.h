#include <iostream>
#include <graphics.h>
#include <winbgim.h>

using namespace std;
#define MAX 50
#define APASAT 1
#define RELAXAT 2

void patrat(int x,int y,int lat)
{
    line(x-lat/2,y-lat/2,x-lat/2,y+lat/2);
    line(x-lat/2,y+lat/2,x+lat/2,y+lat/2);
    line(x+lat/2,y+lat/2,x+lat/2,y-lat/2);
    line(x+lat/2,y-lat/2,x-lat/2,y-lat/2);
}
void dreptunghi(int x,int y,int lat,int inalt)
{
    line(x-lat/2,y-inalt/2,x-lat/2,y+lat/2);
    line(x+lat/2,y+lat/2,x+lat/2,y-lat/2);
}

struct buton
{
    char text[MAX];
    int marime;
    int x,y;
    int x1,y1,x2,y2;
};

void initButon(buton& b, char text0[MAX], int x0, int y0, int m0)
{
    strcpy(b.text,text0);
    b.x=x0;
    b.y=y0;
    b.marime=m0;
    settextstyle(SIMPLEX_FONT,HORIZ_DIR,b.marime);
    b.x1=x0-textwidth(b.text)/2-5;
    b.x2=x0+textwidth(b.text)/2+5;
    b.y1=y0-textheight(b.text)/2-5;;
    b.y2=y0+textheight(b.text)/2+5;
}

void deseneazaButon(buton b, int stil)
{
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, b.marime);
    setcolor(COLOR(255, 204, 102));
    setfillstyle(SOLID_FILL,COLOR(255, 204, 102));
    bar(b.x1,b.y1,b.x2,b.y2);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    if (stil==RELAXAT)
    {
        setbkcolor(COLOR(255, 204, 102));
        setcolor(BLACK);
        outtextxy((b.x1+b.x2)/2,(b.y1+b.y2)/2+2,b.text);
        setcolor(WHITE);
        line(b.x1-1,b.y1-1,b.x2-1,b.y1-1);
        line(b.x1-1,b.y1-1,b.x1-1,b.y2-1);
        setcolor(COLOR(230, 153, 0));
        line(b.x1+1,b.y2+1,b.x2+1,b.y2+1);
        line(b.x2+1,b.y1+1,b.x2+1,b.y2+1);
    }
    else
    {
        setbkcolor(COLOR(255, 204, 102));
        setcolor(BLACK);
        outtextxy((b.x1+b.x2)/2+2,(b.y1+b.y2)/2+4,b.text);
        setcolor(WHITE);
        line(b.x1+1,b.y2+1,b.x2+1,b.y2+1);
        line(b.x2+1,b.y1+1,b.x2+1,b.y2+1);
        setcolor(COLOR(230, 153, 0));
        line(b.x1-1,b.y1-1,b.x2-1,b.y1-1);
        line(b.x1-1,b.y1-1,b.x1-1,b.y2-1);
    }
}

/*void fabuton(buton& b,int b.x1,int b.y1,int b.x2,int b.y2)
{
    if(stil==RELAXAT)
    {
        bar3d();
    }
    else
    {
        bar();
    }
}*/
void plaseazaButoane()
{
    buton b;
    initButon(b,"<",0,300,2);
    buton c;
    initButon(c,">",400,300,2);
    char tasta;
    do
    {
        deseneazaButon(b,RELAXAT);
        tasta=getch();
        deseneazaButon(b,APASAT);

        deseneazaButon(c,RELAXAT);

        deseneazaButon(c,APASAT);
        delay(250);
    }
    while(tasta!=27);
}

void Trasare30careuri(float num1,float num2,int window1,int window2)
{
    int i,j,nr,page,asciiValue,v[101];
    int result;
    char key;

    page=0;
    while(1)
    {
        setcurrentwindow(window1);
        /*setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();*/

        rectangle(0,300,600,600);
        rectangle(100,100,500,150);
        rectangle(100,200,500,300);
        settextstyle(BOLD_FONT,HORIZ_DIR,4);//Fontu,Directia,Marimea
        outtextxy(150,60,"Introdu Functia");//Afisare text : "Introdu Functia"
        for(i=50;i<=400;i=i+50)
            line(i+100,100,i+100,150);
        for(i=25;i<=400;i=i+25)
            line(i+100,200,i+100,300);

        nr=1;
        for(i=0; i<=600; i=i+100)
        {
            if(i==300)
            {
                for(j=100; j<=600; j=j+100) //Trasam cele 18 triunghiuri
                {
                    line(j,i,j,600);
                    line(0,i+60*(j/100),600,i+60*(j/100));
                }
            }
            if(i>=300)
            {
                for(j=0; j<=500; j=j+100)
                {

                    if(nr==6)
                    {
                        settextstyle(BOLD_FONT,HORIZ_DIR,6);
                        outtextxy(j+5,i+5,"DEL");
                        outtextxy(j+30,i+5+60,"/");
                        outtextxy(j+30,i+5+120,"X");
                        outtextxy(j+30,i+5+180,"-");
                        outtextxy(j+30,i+5+240,"+");
                        nr++;
                    }
                    if(nr==5)
                    {
                        settextstyle(BOLD_FONT,HORIZ_DIR,6);
                        outtextxy(j+20,i+5,"AC");
                        outtextxy(j+30,i+5+60,"9");
                        outtextxy(j+30,i+5+120,"6");
                        outtextxy(j+30,i+5+180,"3");
                        outtextxy(j+30,i+5+240,"=");
                        nr++;
                    }
                    if(nr==4)
                    {
                        settextstyle(BOLD_FONT,HORIZ_DIR,6);
                        outtextxy(j+30,i+5,")");
                        outtextxy(j+30,i+5+60,"8");
                        outtextxy(j+30,i+5+120,"5");
                        outtextxy(j+30,i+5+180,"2");
                        outtextxy(j+30,i+5+240,".");
                        nr++;
                    }
                    if(nr==3)
                    {
                        settextstyle(BOLD_FONT,HORIZ_DIR,6);
                        outtextxy(j+30,i+5,"(");
                        outtextxy(j+30,i+5+60,"7");
                        outtextxy(j+30,i+5+120,"4");
                        outtextxy(j+30,i+5+180,"1");
                        outtextxy(j+30,i+5+240,"0");
                        nr++;
                    }
                    if(nr==2)
                    {
                        settextstyle(BOLD_FONT,HORIZ_DIR,6);
                        outtextxy(j+30,i+5,">");
                        outtextxy(j+30,i+5+60,"^");
                        outtextxy(j+5,i+5+120,"RAD");
                        outtextxy(j+5,i+5+180,"exp");
                        outtextxy(j+30,i+5+240,"e");
                        nr++;
                    }
                    if(nr==1)
                    {
                        settextstyle(BOLD_FONT,HORIZ_DIR,6);
                        outtextxy(30,i+5,"<");
                        outtextxy(5,i+5+60,"sin");
                        outtextxy(5,i+5+120,"cos");
                        outtextxy(20,i+5+180,"ln");
                        outtextxy(20,i+5+240,"PI");
                        nr++;
                    }
                }
            }
        }

        /*setcurrentwindow(window2);
        switch(key)
        {
            case '<':
                if(num1<num2) result=num1;
                else result=num2;
                break;

            case '>':
                   if(num1>num2) result=num1;
                   else result=num2;
                   break;

            case ')':

            case '(':

            default:
                nr=0;
                while(result!=0)
                {
                    v[nr]=result%10;
                    nr++;
                    result=result/10;
                }
                break;
        }*/

        //page=1-page;
        delay(500);
    }
}
