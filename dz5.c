#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct numera
{
    char* izvodjac;
    char* pesma;
    char* putanja;
}Numera;
typedef struct lista
{
    Numera n;
    struct lista* sledeci;
    struct lista* prethodni;
}Lista;
Numera* procitajNumeru(char* red,FILE*fajl)
{
    char* redStari = red;
    char* izvodjac = calloc(500, sizeof(char));

    if (red[1] == 'T' && red[2] == 'i' && red[3] == 't' && red[4] == 'l' && red[5] == 'e')
    {
        Numera* n = malloc(sizeof(Numera));
        if (!n)
        {
            printf("MEM_GRESKA");
            exit(0);
        }
        red = &red[8];
        char* novi = calloc(500, sizeof(char));
        strcpy(novi, red);
        char* singer = strtok(novi, "-");
        singer[strlen(singer)] = 0;
        char* songName = strtok(NULL, "\"");
        songName[strlen(songName)] = 0;
        n->izvodjac = singer;
        n->pesma = songName;
        fscanf(fajl, "%[^\n]\n", red);
        red = &red[13];
        char* path = strtok(red, "\"");
        path[strlen(path)] = 0;
        n->putanja = calloc(500,sizeof(char));
        strcpy(n->putanja, path); //n->putanja = path
        //n->putanja = path;
        return n;
    }
    else return NULL;
}
Lista* napraviListu(FILE* fajl)
{
    Lista* head = NULL, * tail = head, * tmp;
    char* red = calloc(500, sizeof(char));
    if (!red)
    {
        printf("MEM_GRESKA");
        exit(0);
    }
    Numera* n;
    while (fscanf(fajl, "%[^\n]\n", red) == 1)
    {
        n = procitajNumeru(red, fajl);
        if (n)
        {
            tmp = malloc(sizeof(Lista));
            if (!tmp)
            {
                printf("MEM_GRESKA");
                exit(0);
            }
            tmp->n = *n;
            tmp->sledeci = NULL;
            tmp->prethodni = tail;

            if (!head) head = tmp;
            else tail->sledeci = tmp;
            tail = tmp;
        }
    }
    return head;
}
Lista* sort(Lista* listaNumera)
{
    for (Lista* curr=listaNumera;curr!=NULL;curr=curr->sledeci)
    {
        for (Lista* curr2 = curr->sledeci; curr2 != NULL; curr2 = curr2->sledeci)
        {
            if (strcmp(curr->n.izvodjac, curr2->n.izvodjac) > 0)
            {
                Numera tmp = curr->n;
                curr->n = curr2->n;
                curr2->n = tmp;
            }
            else if (strcmp(curr->n.izvodjac, curr2->n.izvodjac) == 0)
            {
                if (strcmp(curr->n.pesma, curr2->n.pesma) > 0)
                {
                    Numera tmp = curr->n;
                    curr->n = curr2->n;
                    curr2->n = tmp;
                }
            }
        }
    }
    return listaNumera;
}
int autorInAutori(char* autor, char** autori,int brAutora)
{
    for (int i = 0; i < brAutora; i++)
    {
        if (strcmp(autor,autori[i])==0) return 1;
    }
    return 0;
}
char** izvuciAutore(Lista* listaNumera,int*brAutora)
{
    char** autori=malloc(500*sizeof(char*));
    if (!autori)
    {
        printf("MEM_GRESKA");
        exit(0);
    }
    Lista* curr = listaNumera;
    while (curr != NULL)
    {
        if (!autorInAutori(curr->n.izvodjac, autori, *brAutora))
        {
            autori[*brAutora] = curr->n.izvodjac;
            *brAutora = *brAutora + 1;
        }
        curr = curr->sledeci;
    }
    return autori;
}
int autorPoklapanje(char* autor1, char* autor2)
{
    if (strcmp(autor1, autor2) == 0) return 1;
    return 0;
}
void fajlovi(char** autori, int brAutora, Lista* listaNumera)
{
    char* fajl = calloc(500, sizeof(char));
    if (!fajl)
    {
        printf("MEM_GRESKA");
        exit(0);
    }
    for (int i = 0; i < brAutora; i++)
    {
        char* pokFajl=fajl;
        for (char* curr = autori[i]; *curr != '\0'; curr++, pokFajl++)
        {
            if (*curr == '.')break;
            *pokFajl = *curr;
        }
        if (*(pokFajl - 1) == ' ')*(pokFajl - 1) = '\0';
        else *pokFajl = '\0';
        strcat(fajl,".m3u");

        FILE* out = fopen(fajl, "w");
        fprintf(out, "#EXTM3U\n");
        Lista* curr = listaNumera;
        while (curr != NULL)
        {
            if (autorPoklapanje(curr->n.izvodjac, autori[i]))
            {
                fprintf(out, "#EXTINF:0,%s-%s\n", curr->n.izvodjac, curr->n.pesma);
                fprintf(out, "%s\n", curr->n.putanja);
            }
            curr = curr->sledeci;
        }
        fclose(out);
    }


}
void main(int argc,char* argv[])
{
    FILE* fajl=fopen(argv[1], "r");
    if(!argv[1])
    {
        printf("ARG_GRESKA");
        exit(0);
    }
    if (!fajl)
    {
        printf("DAT_GRESKA");
        exit(0);
    }

    Lista* listaNumera = napraviListu(fajl);
    listaNumera=sort(listaNumera);
    int brAutora = 0;
    char** autori = izvuciAutore(listaNumera,&brAutora);
    fajlovi(autori, brAutora, listaNumera);
    fclose(fajl);
    exit(0);
}