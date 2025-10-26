#include "zbior_ary.h"

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

int stalaQ; // przechowuje q


int policz_reszte(int a, int b) // rezta z dzielenia a przez b, zawsze dodatnia
{
    if (a >= 0)
    {
        return a % b;
    }
    return b + (a % b);
}


zbior_ary ciag_arytmetyczny(int a, int q, int b)
{
    stalaQ = q;
    zbior_ary zbior;
    zbior.rozmiar = 1;
    zbior.ciagi = malloc(sizeof(ciag));
    ciag c = {policz_reszte(a, stalaQ), a, b}; // Jedyny ciąg w zbiorze
    zbior.ciagi[0] = c;
    return zbior;
}


zbior_ary singleton(int a)
{
    zbior_ary zbior;
    zbior.rozmiar = 1;
    zbior.ciagi = malloc(sizeof(ciag));
    ciag c = {policz_reszte(a, stalaQ), a, a}; // Jedyny ciąg w zbiorze
    zbior.ciagi[0] = c;
    return zbior;
}


unsigned moc(zbior_ary A)
{
    int res = 0;
    for (int i = 0; i < A.rozmiar; i++)
    {
        ciag c = A.ciagi[i];
        res += (c.last - c.first) / stalaQ + 1;
    }
    return (unsigned)res;
}


unsigned ary(zbior_ary A)
{
    return (unsigned)A.rozmiar;
}


bool nalezy(zbior_ary A, int b)
{
    int lewy = 0;
    int prawy = A.rozmiar - 1;
    int srodek;

    // Wyszukiwanie binarne
    while (lewy <= prawy)
    {
        srodek = (lewy + prawy) / 2;
        ciag sr_ciag = A.ciagi[srodek];

        if (sr_ciag.reszta > policz_reszte(b, stalaQ))
            prawy = srodek - 1;
        else if (sr_ciag.reszta < policz_reszte(b, stalaQ))
            lewy = srodek + 1;
        else
        {
            if (sr_ciag.first > b)
                prawy = srodek - 1;
            else if (sr_ciag.last < b)
                lewy = srodek + 1;
            else
                return true;
        }
    }
    return false;
}


// Zwraca 1 jesli A jest mniejszy od B
//(reszta A jest mniejsza, a przy równych resztach pierwszy element A jest mniejszy)
bool porownaj(ciag A, ciag B)
{
    if (A.reszta == B.reszta)
        return A.first < B.first;
    else
        return A.reszta < B.reszta;
}


zbior_ary suma(zbior_ary A, zbior_ary B)
{
    zbior_ary res;
    int size = 0;
    ciag *suma = malloc(sizeof(ciag) * (unsigned)(A.rozmiar + B.rozmiar));
    int ind_A = 0, ind_B = 0;
    ciag c;

    // Wybiera pierwszy ciąg
    if (porownaj(A.ciagi[0], B.ciagi[0]))
    {
        c = A.ciagi[0];
        ind_A++;
    }
    else
    {
        c = B.ciagi[0];
        ind_B++;
    }

    // Liczy sumę
    while (ind_A < A.rozmiar || ind_B < B.rozmiar)
    {
        // Wybiera następny ciąg
        bool a_mniejszy; //czy następny ciąg z A jest mniejszy od następnego ciągu z B
        if (ind_A == A.rozmiar)
            a_mniejszy = 0;
        else if (ind_B == B.rozmiar)
            a_mniejszy = 1;
        else
            a_mniejszy = porownaj(A.ciagi[ind_A], B.ciagi[ind_B]);

        if (a_mniejszy)
        {
            if ((A.ciagi[ind_A].reszta > c.reszta) || (A.ciagi[ind_A].first > c.last + stalaQ)) // rozłączne
            {
                suma[size] = c;
                size++;
                c = A.ciagi[ind_A];
            }
            else //mają część wspólną
            {
                c.last = (int)fmax(c.last, A.ciagi[ind_A].last);
            }
            ind_A++;
        }
        else
        {
            if ((B.ciagi[ind_B].reszta > c.reszta) || (B.ciagi[ind_B].first > c.last + stalaQ)) // rozłączne
            {
                suma[size] = c;
                size++;
                c = B.ciagi[ind_B];
            }
            else //mają część wspólną
            {
                c.last = (int)fmax(c.last, B.ciagi[ind_B].last);
            }
            ind_B++;
        }
    }
    suma[size] = c;
    size++;

    // Zapisuje ciągi do wyniku
    res.rozmiar = size;
    res.ciagi = malloc(sizeof(ciag) * (unsigned)size);
    for (int i = 0; i < size; i++)
    {
        res.ciagi[i] = suma[i];
    }
    free(suma);
    return res;
}

zbior_ary iloczyn(zbior_ary A, zbior_ary B)
{
    zbior_ary res;
    int size = 0;
    ciag *iloczyn = malloc(sizeof(ciag) * (unsigned)(A.rozmiar + B.rozmiar));
    int ind_A = 0, ind_B = 0;

    //Liczy iloczyn
    while (ind_A < A.rozmiar && ind_B < B.rozmiar)
    {
        ciag ciag_A = A.ciagi[ind_A];
        ciag ciag_B = B.ciagi[ind_B];
        if (ciag_A.reszta == ciag_B.reszta)
        {
            //ciągi mają część wspólną
            if ((ciag_A.first <= ciag_B.last && ciag_A.last >= ciag_B.last) || (ciag_B.first <= ciag_A.last && ciag_B.last >= ciag_A.last))
            {
                iloczyn[size].reszta = ciag_A.reszta;
                iloczyn[size].first = (int)fmax(ciag_A.first, ciag_B.first);
                iloczyn[size].last = (int)fmin(ciag_A.last, ciag_B.last);
                size++;
            }
        }

        if (ind_A + 1 == A.rozmiar) // rozpatrzono ostatni ciąg A
            ind_B++;
        else if (ind_B + 1 == B.rozmiar) // rozpatrzono ostatni ciąg B
            ind_A++;
        else if (porownaj(A.ciagi[ind_A + 1], B.ciagi[ind_B + 1]))
            ind_A++;
        else
            ind_B++;
    }

    // Zapisuje ciągi do wyniku
    res.rozmiar = size;
    res.ciagi = malloc(sizeof(ciag) * (unsigned)size);
    for (int i = 0; i < size; i++)
    {
        res.ciagi[i] = iloczyn[i];
    }
    free(iloczyn);
    return res;
}

zbior_ary roznica(zbior_ary A, zbior_ary B)
{
    zbior_ary res;
    int size = 0;
    ciag *roznica = malloc(sizeof(ciag) * (unsigned)(A.rozmiar + B.rozmiar));
    int ind_A = 0, ind_B = 0;
    ciag c = A.ciagi[0];

    while (ind_A < A.rozmiar && ind_B < B.rozmiar)
    {
        ciag ciag_B = B.ciagi[ind_B]; //ciąg który będzie odejmowany

        if (c.reszta < ciag_B.reszta || (c.last < ciag_B.first && c.reszta == ciag_B.reszta)) // c jest w całości mniejszy
        {
            roznica[size] = c;
            size++;
            ind_A++;
            if (ind_A < A.rozmiar)
                c = A.ciagi[ind_A];
        }
        else if (c.reszta > ciag_B.reszta || c.first > ciag_B.last) // c jest w całości większy
        {
            ind_B++;
        }
        else if (c.last <= ciag_B.last && c.first >= ciag_B.first) // c jest zawarty w ciag_B
        {
            ind_A++;
            if (ind_A < A.rozmiar)
                c = A.ciagi[ind_A];
        }
        else if (c.last <= ciag_B.last) // górna część c jest wspólna
        {
            c.last = ciag_B.first - stalaQ;
            roznica[size] = c;
            size++;
            ind_A++;
            if (ind_A < A.rozmiar)
                c = A.ciagi[ind_A];
        }
        else if (c.first >= ciag_B.first) // dolna część c jest wspólna
        {
            c.first = ciag_B.last + stalaQ;
            ind_B++;
        }
        else // c zawiera ciag_B
        {
            ciag temp = {c.reszta, c.first, ciag_B.first - stalaQ}; //dolna część c
            roznica[size] = temp;
            size++;
            c.first = ciag_B.last + stalaQ;
            ind_B++;
        }
    }

    // Dopisuje pozostałe ciągi z A
    if (ind_B == B.rozmiar)
    {
        roznica[size] = c;
        size++;
        ind_A++;
        while (ind_A < A.rozmiar)
        {
            roznica[size] = A.ciagi[ind_A];
            size++;
            ind_A++;
        }
    }

    // Zapisuje do wyniku
    res.rozmiar = size;
    res.ciagi = malloc(sizeof(ciag) * (unsigned)size);
    for (int i = 0; i < size; i++)
    {
        res.ciagi[i] = roznica[i];
    }
    free(roznica);
    return res;
}
