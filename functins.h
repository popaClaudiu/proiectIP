#include <math.h>
#define infinit 10000000000
#define epsilon 0.000000001

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
            yi = trunc(y);
            p = 1;
            for (i = 1; i < yi / 2; i++)
            {
                p *= x;
                p *= p;
            }
            if (estePar(yi))
                p *= x;

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

