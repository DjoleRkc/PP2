/*
 * Napisati program koji u zadatim stringovima vrši konverziju for petlje na programskom jeziku
C u while petlju. Petlja for ima standardan oblik for(preduslov;uslov;postuslov)
{...} uz moguće postojanje dodatnih blanko znaka, gde ... predstavlja bilo kakav sadržaj
koji čini telo petlje. Program treba da na osnovu petlje navedenog oblika formira ekvivalentnu
while petlju uz uklanjanje svih blanko znakova, kako u okviru definicije, tako i u okviru tela
petlje. Smatrati da se petlje ne ugneždavaju, a da string može sadržati i drugi tekst koji
predstavlja ispravan programski kod na programskom jeziku C. Program učitava stringove koji
sadrže programski kod na programskom jeziku C. Smatrati da se for petlja uvek nalazi u jednom
redu. Kraj unosa se označava praznim redom. U slučaju da je niz stringova koji se obrađuje
prazan ispisati poruku GRESKA.
Program napisati prema sledećim stavkama. Prilikom izrade pojedinačne stavke pretpostaviti da
su funkcije iz stavki koje su prethodile trenutnoj date i da njihove funkcionalnosti odgovaraju
datom opisu.
1) Implementirati funkciju char* readLine(); koja čita jedan red sa standardnog ulaza
i vraća pokazivač na taj učitani red.
2) Implementirati funkciju char** readLines(); koja čita niz stringova koji sadrže
programski kod na programskom jeziku C. Funkcija kao povratnu vrednost vraća niz
pokazivača na unete stringove. Kraj niza pokazivača označava se NULL pokazivačem.
3) Implementirati funkciju char** forToWhile (char **srcCode); koja formira novi
niz stringova prema opisanoj obradi na osnovu niza stringova srcCode. Funkcija putem
povratne vrednosti vraća novoformirani niz.
4) Napisati glavni program koji korišćenjem prethodno realizovanih funkcija pročita niz
stringova koji sadrže programski kod na programskom jeziku C, a zatim formira i ispiše
novi niz stringova u kome će sve pojave for petlje biti zamenjene while petljom na
opisani način. Nakon ispisa dodati znak za novi red.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int brojac = 0, broj_elem = 0;
char *readLine()
{
    char *str, character;
    int i=0;
    str = malloc(sizeof(char));
    if (!str)//ako je str==0
    {
        printf("MEM_GRESKA");
        exit(0);
    }
    while ((character=getchar()) != '\n')
    {
        str[i++] = character;
        str = realloc(str, (i+1)*sizeof(char));
        if (!str)//ako je str==0
        {
            printf("MEM_GRESKA");
            exit(0);
        }

    }
    str[i] = '\0';
    if (!strlen(str) && brojac==0)
    {   printf("GRESKA");
        exit(0);
    }
    else (brojac++);
    return str;
}

char **readLines()
{
    char **linije, *linija;
    linije = malloc(sizeof(char*));
    if (!linije)
    {
        printf("MEM_GRESKA");
        exit(0);
    }
    while(1)
    {
        linija = readLine();
        linije[broj_elem++] = linija;
        if (!linija || strlen(linija) == 0) break;
        linije = realloc(linije, (broj_elem+1)*sizeof(char*));
        if (!linije)
        {
            printf("MEM_GRESKA");
            exit(0);
        }
    }
    linije[broj_elem] = NULL;
    return linije;

}


char *remove_space(char* string_for_removal)
{
    char *pointer = string_for_removal;
    do {
        while (*pointer == ' ')
        {
            pointer++;
        }
    } while (*string_for_removal++ = *pointer++);
    return string_for_removal;
}

int detect_for(char **linije)
{
    char *current_string = linije[0];
    int h = 0;
    while (current_string != NULL && strlen(current_string) > 2) {
        for (int j = 0; j < strlen(current_string) - 2; j++) {
            if (current_string[j] == 'f' && current_string[j + 1] == 'o' && current_string[j + 2] == 'r') {
                return h;
            }
        }
        current_string = linije[++h];
    }
    return -1;
}

void after_for(char *linija, char *incr)
{
    int flag = 0;
    for (int i=0;i<strlen(linija) && linija[i] != '}';i++)
    {
        if (linija[i] == '{' && flag==0)
        {
            flag = 1;
        }
        if (flag==1 && linija[i] != ' ') printf("%c", linija[i]);
    }
    printf("%s;}", incr);
}

void after_for2(char *linija)
{
    int flag = 0;
    for (int i=0;i<strlen(linija);i++)
    {
        if (linija[i] == '}' && flag==0)
        {
            flag = 1;
        }
        else if (flag==1) printf("%c", linija[i]);
    }
}

void final(char **linije, int for_index)
{
    for (int i = for_index+1; i < broj_elem-1; i++)
    {
        printf("\n%s", linije[i]);
    }
}

char *forToWhile(char **srcCode, char **linije, int broj_elem)
{
    char *token = strtok(*srcCode, "(");
    char *init;
    char *cond;
    char *incr;
    int for_index = detect_for(linije);
    token = strtok(NULL, ")");
    init = strtok(token, ";");
    cond = strtok(NULL, ";");
    incr = strtok(NULL, ")");
    remove_space(init);
    remove_space(cond);
    remove_space(incr);
    printf("%s;", init);
    printf("while(");
    printf("%s",cond);
    putchar(')');
    return incr;

}



char *checkFor(char *current_string)// vraca for petlju
{
    char *for_str;
    int k=0, h;
    while(current_string != NULL && strlen(current_string) > 2)
    {
        for (int j = 0;j<strlen(current_string)-2;j++)
        {
            h=0;
            if (current_string[j] == 'f' && current_string[j+1] == 'o' && current_string[j+2] == 'r')
            {
                for_str = malloc(100*sizeof(char));
                if (!for_str)
                {
                    printf("MEM_GRESKA");
                    exit(0);
                }
                for (int l=j;l< strlen(current_string);l++)
                {
                    if (current_string[l] == '{') break;
                    for_str[h++] = current_string[l];

                }
                for_str[h] = 0;
                for_str = realloc(for_str, (h)*sizeof(char));
                if (!for_str)
                {
                    printf("MEM_GRESKA");
                    exit(0);
                }
                return for_str;
            }
            else printf("%c", current_string[j]);
        }

    }
}

void print_before_for(char **linije, int forIndex)
{
    for (int i=0;i<forIndex;i++)
    {
        printf("%s\n", linije[i]);
    }
}

int main()
{
    int for_index;//u kojoj liniji se nalazi for

    char *for_str;
    char **linije = readLines();
    int check = detect_for(linije);
    print_before_for(linije, check);
    for_str = checkFor(linije[check]);
    char *incr = forToWhile(&for_str, linije, broj_elem);
    after_for(linije[check], incr);
    after_for2(linije[check]);
    final(linije,check );
    for (int u=0;u<broj_elem;u++) free(linije[u]);
    free(linije);
    free(for_str);
    return 0;
}