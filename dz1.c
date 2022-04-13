/*Napisati program koji na osnovu zadatog niza celih brojeva koji predstavlja cene goriva po
uzastopnim danima određuje najduže sekvence nerastućih i neopadajučih perioda izmena cena
goriva izraženih u danima. Negativne vrednosti u nizu ukazuju da za te dane nije dostupan
podatak o ceni goriva i za te dane se uzima informacija od najbližeg prethodnog dana sa
pozitivnom cenom goriva.
Program treba da:
1) Učita dužinu niza celih brojeva u jednom redu, zatim i same brojeve u narednom redu.
2) Ispiše elemente učitanog niza u jednom redu razdvojene tačno jednim blanko znakom.
3) Svaku negativnu vrednost u nizu zameni vrednošću koja je se nalazi levo od date
vrednosti i najmanje je udaljena. Smatrati da je prvi element niza uvek pozitivna
vrednost.
4) Ispiše elemente rezultujućeg niza u jednom redu razdvojene tačno jednim blanko
znakom.
5) Odredi, a zatim ispiše najpre dužinu najdužeg nerastućeg perioda, a potom i dužinu
najdužeg neopadajućeg perioda, u zasebnom redu razdvojene tačno jednim blanko
znakom.
*/

#include <stdio.h>
#include <stdlib.h>
#define NAJVECA_DUZINA_NIZA 1000

int main() {
    int duzina_niza, najblizi, max_neopadajuci=0, max_nerastuci=0, brojac_neopadajucih=1, brojac_nerastucih = 1;
    scanf("%d", &duzina_niza);
    int niz[NAJVECA_DUZINA_NIZA];
    if (duzina_niza > NAJVECA_DUZINA_NIZA || duzina_niza <= 0)
    {
        exit(0);
    }
    for (int i = 0; i < duzina_niza; i++)
    {
        scanf("%d", niz+i);
    }
    for (int j=0;j<duzina_niza-1;j++)
    {
        printf("%d ", niz[j]);
    }
    printf("%d", niz[duzina_niza-1]);

    for (int m=1;m<duzina_niza;m++)
    {
        if (niz[m] >= 0)
        {
            najblizi = niz[m];
        }
        else niz[m] = najblizi;
    }
    putchar('\n');
    for (int j=0;j<duzina_niza-1;j++)
    {
        printf("%d ", niz[j]);
    }
    printf("%d", niz[duzina_niza-1]);

    for (int k=0; k<duzina_niza-1;k++)
    {
        if (niz[k+1] >= niz[k])
        {
            brojac_neopadajucih++;
        }
        else
        {
            if (brojac_neopadajucih > max_neopadajuci) max_neopadajuci = brojac_neopadajucih;
            brojac_neopadajucih = 1;
        }
    }
    if (brojac_neopadajucih > max_neopadajuci) max_neopadajuci = brojac_neopadajucih;
    //u poslednjoj iteraciji nece uci u else, pa nece ni izvrsiti proveru. Bez ponovne provere pravi problem ako poslednji element treba da bude u nizu neop./neras.

    for (int p=0; p<duzina_niza-1;p++)
    {
        if (niz[p] >= niz[p+1])
        {
            brojac_nerastucih++;
        }
        else
        {
            if (brojac_nerastucih > max_nerastuci) max_nerastuci = brojac_nerastucih;
            brojac_nerastucih = 1;
        }

    }
    if (brojac_nerastucih > max_nerastuci) max_nerastuci = brojac_nerastucih;
    //u poslednjoj iteraciji nece uci u else, pa nece ni izvrsiti proveru. Bez ponovne provere pravi problem ako poslednji element treba da bude u nizu neop./neras.

    putchar('\n');
    printf("%d %d", max_nerastuci, max_neopadajuci);
}
