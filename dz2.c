/*Napisati program koji proverava da li je partija generalizovane igre IKS – OKS koja se igra na
tabli N x M završena. Partija ima pobednika ukoliko je neko uspeo da poveže 4 znaka vodoravno,
uspravno ili dijagonalno.
Program treba da:
1) Učita dimenzije matrice, a zatim u novom redu i matricu celih brojeva. Polje 1 označava
da je na tom mestu igrao prvi igrač (IKS), polje 2 da je na tom mestu igrao drugi igrač
(OKS), a polje 0 da tu još uvek niko nije igrao. Matrica može biti zadata u više redova.
2) Ispiše učitanu matricu. Svaka vrsta matrice treba da bude ispisana u zasebnom redu.
Svaki element treba da bude razdvojen tačno jednim blanko znakom. Nakon poslednjeg
elementa vrste ne treba da se ispiše blanko znak, već znak za novi red.
3) Proveri da li je neko od igrača pobedio i ispiše POBEDIO JE PRVI IGRAC, odnosno
POBEDIO JE DRUGI IGRAC u slučaju da je partija završena i završi program.
4) Ukoliko partija nije završena odredi koliko je puta igrao prvi i koliko puta drugi igrač i
ispiše: PRVI IGRAC NA POTEZU - ukoliko su igrači igrali isti broj puta, DRUGI IGRAC
NA POTEZU – ukoliko je prvi igrač igrao jedan puta više nego drugi igrač,
NEREGULARNA PARTIJA – u svim ostalim slučajevima.
5) Nije potrebno proveravati ispravnost unetih podataka, osim situacije koja je navedena u
stavci 4.
*/

#include <stdio.h>
#include <stdlib.h>
int main(){
    int broj_kolona, broj_vrsta, **m, brojac_prvi=0, brojac_drugi=0, game_end, br_poteza1=0, br_poteza2=0, a;
    scanf("%d%d", &broj_vrsta, &broj_kolona);
    if (broj_vrsta <= 0 || broj_kolona <= 0)
    {
        exit(0);
    }
    m = calloc(broj_vrsta, sizeof(int*));
    if (m==NULL)
    {
        printf("Alokacija neuspesna.");
        exit(0);
    }

    for (int i=0; i<broj_vrsta;i++)
    {
        m[i] = calloc(broj_kolona, sizeof(int));
        if (m[i]==NULL)
        {
            printf("Alokacija neuspesna.");
            free(m);
            exit(0);
        }
        for (int j=0; j<broj_kolona; j++)
        {
            scanf("%d", &m[i][j]);
        }

    }

    for (int k=0;k<broj_vrsta;k++)
    {
        for (int l=0;l<broj_kolona-1;l++)
        {
            printf("%d ", m[k][l]);
        }
        printf("%d", m[k][broj_kolona-1]);
        putchar('\n');
    }

    if (broj_vrsta<4 && broj_kolona<4)
    {
        for (int t=0;t<broj_vrsta;t++)
        {
            for (int h=0;h<broj_kolona;h++)
            {
                if (m[t][h]==1) brojac_prvi++;
                else if (m[t][h]==2) brojac_drugi++;
            }
        }
        if (brojac_prvi==brojac_drugi)
        {
            printf("PRVI IGRAC NA POTEZU"); brojac_prvi=0; brojac_drugi=0;
        }
        else if(brojac_prvi == brojac_drugi+1)
        {
            printf("DRUGI IGRAC NA POTEZU"); brojac_prvi=0; brojac_drugi=0;
        }
        else printf("NEREGULARNA PARTIJA"); brojac_prvi=0; brojac_drugi=0;

    }

    if (broj_vrsta >=4 || broj_kolona >= 4)
    {
        //horizontalno
        for (int t=0;t<broj_vrsta;t++)
        {
            for (int h=0;h<broj_kolona;h++)
            {
                if (m[t][h]==1) brojac_prvi++, br_poteza1++;
                else if (m[t][h]==2) brojac_drugi++, br_poteza2++;
                else brojac_prvi = 0; brojac_drugi=0;
            }
            if (brojac_prvi >= 4) game_end = 1;
            else if (brojac_drugi >= 4) game_end = 2;
            else if (brojac_prvi<4 && brojac_drugi<4) game_end = 0;
        }
        brojac_prvi=0;
        brojac_drugi=0;

        if (game_end == 1)
        {
            printf("POBEDIO JE PRVI IGRAC");
            putchar('\n');
            for (int u=0;u<broj_vrsta;u++) free(m[u]);
            free(m);
            return 0;
        }
        else if (game_end == 2)
        {
            printf("POBEDIO JE DRUGI IGRAC");
            putchar('\n');
            for (int u=0;u<broj_vrsta;u++) free(m[u]);
            free(m);
            return 0;
        }
        //vertikalno
        for (int t=0;t<broj_kolona;t++)
        {
            for (int h=0;h<broj_vrsta;h++)
            {
                if (m[h][t]==1) brojac_prvi++, br_poteza1++;
                else if (m[h][t]==2) brojac_drugi++, br_poteza2++;
                else brojac_prvi = 0; brojac_drugi=0;
            }
            if (brojac_prvi >= 4) game_end = 1;
            else if (brojac_drugi >= 4) game_end = 2;
            else if (brojac_prvi<4 && brojac_drugi<4) game_end = 0;
        }
        brojac_prvi=0;
        brojac_drugi=0;
        if (game_end == 1)
        {
            printf("POBEDIO JE PRVI IGRAC");
            putchar('\n');
            for (int u=0;u<broj_vrsta;u++) free(m[u]);
            free(m);
            return 0;
        }
        else if (game_end == 2)
        {
            printf("POBEDIO JE DRUGI IGRAC");
            putchar('\n');
            for (int u=0;u<broj_vrsta;u++) free(m[u]);
            free(m);
            return 0;
        }
        //dijagonalno (gore levo-dole desno i dole desno-gore levo)
        for (int t=0;t<broj_vrsta-4;t++)
        {
            for (int h=t, a=0; h<broj_vrsta && a<broj_kolona;h++,a++)
            {
                if (m[h][a]==1) brojac_prvi++, br_poteza1++;
                else if (m[h][a]==2) brojac_drugi++, br_poteza2++;
                else brojac_prvi = 0; brojac_drugi=0;
            }
            if (brojac_prvi >= 4) game_end = 1;
            else if (brojac_drugi >= 4) game_end = 2;
            else if (brojac_prvi<4 && brojac_drugi<4) game_end = 0;
        }
        brojac_prvi=0;
        brojac_drugi=0;
        if (game_end == 1)
        {
            printf("POBEDIO JE PRVI IGRAC");
            putchar('\n');
            for (int u=0;u<broj_vrsta;u++) free(m[u]);
            free(m);
            return 0;
        }
        else if (game_end == 2)
        {
            printf("POBEDIO JE DRUGI IGRAC");
            putchar('\n');
            for (int u=0;u<broj_vrsta;u++) free(m[u]);
            free(m);
            return 0;
        }

        for (int t = 0; t < broj_vrsta; t++)
        {
            for (int h = broj_kolona - 1; h >= 0; h--)
            {
                if (m[t][h] == 1)
                {
                    brojac_prvi++, br_poteza1++;
                    if (h < broj_kolona - 1 && t - 1>0 && m[t - 1][h + 1]!=1) brojac_prvi = 1;
                }
                else if (m[t][h] == 2)
                {
                    brojac_drugi++, br_poteza2++;
                    if (h < broj_kolona - 1 && t-1>0 && m[t - 1][h + 1]!=2) brojac_drugi = 1;
                }

            }
            if (brojac_prvi >= 4) game_end = 1;
            else if (brojac_drugi >= 4) game_end = 2;
            else if (brojac_prvi < 4 && brojac_drugi < 4) game_end = 0;
        }
        if (game_end == 1)
        {
            printf("POBEDIO JE PRVI IGRAC");
            putchar('\n');
            for (int u=0;u<broj_vrsta;u++) free(m[u]);
            free(m);
            return 0;
        }
        else if (game_end == 2)
        {
            printf("POBEDIO JE DRUGI IGRAC");
            putchar('\n');
            for (int u=0;u<broj_vrsta;u++) free(m[u]);
            free(m);
            return 0;
        }

        if (game_end==0)
        {
            {
                if (br_poteza1==br_poteza2)
                {
                    printf("PRVI IGRAC NA POTEZU");
                }
                else if(br_poteza1 == br_poteza2+1)
                {
                    printf("DRUGI IGRAC NA POTEZU");
                }
                else printf("NEREGULARNA PARTIJA");
            }
        }
    }

    for (int u=0;u<broj_vrsta;u++) free(m[u]);
    free(m);
    putchar('\n');
}
