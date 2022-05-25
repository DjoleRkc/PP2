/*
 * Napisati program na programskom jeziku C koji pomaže korisniku u organizaciji sastanaka u toku
jednog dana. Ulančana lista sadrži podatke o terminima sastanaka u toku jednog dana, a svaki
sastanak je definisan vremenom početka i kraja HH:MM-HH:MM, mestom održavanja (jedna reč)
i kratkim opisom sastanka (niz znakova). Program treba da formira i ispiše ulančanu listu
sastanaka na koji korisnik treba da ode u okviru zadatog dana uređenu rastuće po vremenu
početka sastanaka. Ukoliko se dva ili više sastanaka preklapaju, prednost dati onome koji se
odvija na istom mestu kao i prethodni, a u slučaju istog mesta održavanja, prioritet dati onom
koji počinje najranije. U slučaju istog vremena održavanja, izabrati onaj koji je prvi učitan. Ukoliko
je vreme početka ili kraja nekorektno, potrebno je ispisati poruku GRESKA i korektno završiti
program.
Program napisati prema sledećim stavkama.
1) Implementirati funkciju koja čita jedan red sa standardnog ulaza prema formatu koji je zadat
u tekstu zadatka i formira novi element ulančane liste. Ukoliko pročita prazan red, funkcija
treba da vrati vrednost NULL.
2) Implementirati funkciju koja pozivanjem prethodno realizovane funkcije formira jednostruko
ulančanu listu sa podacima o sastancima. Funkcija treba da elemente ulančava u listu u
poretku učitavanja. Kraj unosa se označava praznim redom.
3) Implementirati funkciju koja ispisuje jednostruko ulančanu listu na standardni izlaz.
4) Implementirati funkciju koja na osnovu zadate liste sastanaka formira novu listu koja sadrži
sastanke na koje korisnik treba da ode prema navedenim kriterijumima.
5) Implementirati funkciju koja oslobađa dinamičku memoriju koju zauzima lista koja se prosledi
kao parametar funkcije.
6) Napisati glavni program koji korišćenjem prethodno realizovanih funkcija pročita podatke o
sastancima korisnika, izvrši traženu obradu i ispiše formiranu ulančanu listu. Kraj unosa se
označava praznim redom. Na kraju, program dealocira svu korišćenu dinamičku memoriju.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char* data;
    struct node* next;
} Node;

Node* linija(){
    char *p = NULL,*q,c;
    int i = 0;
    p = malloc((i + 1)*sizeof(char));
    if (!p){
        printf("MEM_GRESKA");
        exit(1);
    }
    while((c = getchar()) != '\n'){
        q = realloc(p, (i + 1) * sizeof (char));
        if(!q){
            printf("MEM_GRESKA");
            exit(1);
        }
        else {
            p = q;
        }
        p[i++] = c;
    }
    q = realloc(p, (i + 1)* sizeof (char));
    if(!q){
        printf("MEM_GRESKA");
        exit(1);
    }
    else {
        p = q;
    }
    p[i] = '\0';
    Node *node = calloc(1,sizeof (Node));
    if (node == NULL){
        exit(1);
    }
    node->data = p;
    node->next = NULL;
    if(i == 0){
        return NULL;
    }
    return node;
}

Node* Napravilistu(){
    Node* head = NULL;
    Node* last = NULL;
    Node* node = linija();
    while ((node)!= NULL){
        if(last == NULL){
            head = node;
        }
        else {
            last->next = node;
        }
        last = node;
        node = linija();
    }
    return head;
}

void printList (Node* head){
    for (Node *current = head; current != NULL; current = current->next){
        int i = 0;
        while(current->data[i] != '\0'){
            printf("%c",current->data[i]);
            i++;
        }
        putchar('\n');
    }
}

int compare(int prvo, int drugo){
    if (prvo == drugo){
        return 0;
    }
    else if (prvo > drugo){
        return 1;
    }
    else {
        return -1;
    }
}

Node* sortList(Node* head){
    for (Node *i = head; i != NULL; i = i->next){
        for(Node *j = i->next; j != NULL; j = j->next){
            int H1,M1,H3,M3,H2,H4,M2,M4;
            int nesto;
            H1 = atoi(i->data);
            M1 = atoi(i->data + 3);
            H2 = atoi(i->data + 6);
            M2 = atoi(i->data + 9);
            H3 = atoi(j->data);
            M3 = atoi(j->data + 3);
            H4 = atoi(j->data + 6);
            M4 = atoi(j->data + 9);
            if(H1 < 0 || H1 > 23 || H2 < H1 || H4 < H3 || (H1 == H2 && M1 > M2) || (H3 == H4 && M3 > M4)){
                printf("GRESKA");
                exit(0);
            }
            if(H2 < 0 || H2 > 23){
                printf("GRESKA");
                exit(0);
            }
            if(H3 < 0 || H3 > 23){
                printf("GRESKA");
                exit(0);
            }
            if(H4 < 0 || H4 > 23){
                printf("GRESKA");
                exit(0);
            }
            if(M1 < 0 || M1 > 59){
                printf("GRESKA");
                exit(0);
            }
            if(M2 < 0 || M2 > 59){
                printf("GRESKA");
                exit(0);
            }
            if(M3 < 0 || M3 > 59){
                printf("GRESKA");
                exit(0);
            }
            if(M4 < 0 || M4 > 59){
                printf("GRESKA");
                exit(0);
            }
            nesto = compare(H1,H3);
            if(nesto){
                if (nesto == 1){
                    char* tmp = i->data;
                    i->data = j->data;
                    j->data = tmp;
                }
            }
            else{
                nesto = compare(M1,M3);
                if(nesto){
                    if(nesto == 1){
                        char* tmp = i->data;
                        i->data = j->data;
                        j->data = tmp;
                    }
                }
            }
        }
    }
    Node *q = head;
    Node *i = head;
    while (i != NULL){
        Node *j = i->next;
        while(j != NULL){
            if (i == head){
                int H1,H2,H3,H4,M1,M2,M3,M4;
                H1 = atoi(i->data);
                M1 = atoi(i->data + 3);
                H2 = atoi(i->data + 6);
                M2 = atoi(i->data + 9);
                H3 = atoi(j->data);
                M3 = atoi(j->data + 3);
                H4 = atoi(j->data + 6);
                M4 = atoi(j->data + 9);
                if (H1 == H3 && H2 == H4 && M1 == M3 && M4 == M2){
                    Node* old = j;
                    j = j->next;
                    free(old);
                    i->next = j;
                }
                else {
                    j = j->next;
                }
            }
            else {
                int H1,H2,H3,H4,M1,M2,M3,M4;
                H1 = atoi(i->data);
                M1 = atoi(i->data + 3);
                H2 = atoi(i->data + 6);
                M2 = atoi(i->data + 9);
                H3 = atoi(j->data);
                M3 = atoi(j->data + 3);
                H4 = atoi(j->data + 6);
                M4 = atoi(j->data + 9);
                if (H1 == H3 && H2 == H4 && M1 == M3 && M4 == M2){
                    int br1 = 0,br2 = 0,x = 12;
                    while((q->data[x]) != ' '){
                        if(q->data[x] == i->data[x] && q->data[x] == j->data[x]){
                            br1++;
                            br2++;
                        }
                        else if(q->data[x] == i->data[x]){
                            br1++;
                        }
                        else if(q->data[x] == j->data[x]){
                            br2++;
                        }
                        x++;
                    }
                    if( x - 12 == br1 && x - 12 != br2){
                        //izbaciti j-ti
                        Node* old = j;
                        j = j->next;
                        free(old);
                        i->next = j;
                    }
                    else if( x - 12 == br2 && x - 12 != br1){
                        //izbaciti i-ti
                        Node* old = i;
                        i = i->next;
                        free(old);
                        q->next = i;
                        j = j->next;
                    }
                    else {
                        //izbaciti j-ti
                        Node* old = j;
                        j = j->next;
                        free(old);
                        i->next = j;
                    }
                }
                else {
                    j = j->next;
                }
            }
        }
        if (i != head){
            q = q->next;
        }
        i = i->next;
    }
    q = head;
    i = head;
    while(i != NULL){
        Node *j = i->next;
        while( j != NULL){
            if( i == head){
                int H2,M2,H3,M3,nesto;
                H2 = atoi(i->data + 6);
                M2 = atoi(i->data + 9);
                H3 = atoi(j->data);
                M3 = atoi(j->data + 3);
                nesto = compare(H3,H2);
                if(nesto){
                    if(nesto == -1){
                        Node* old = j;
                        j = j->next;
                        free(old);
                        i->next = j;
                    }
                    else{
                        j = j->next;
                    }
                }
                else {
                    nesto = compare(M3,M2);
                    if(nesto){
                        if(nesto == -1){
                            Node* old = j;
                            j = j->next;
                            free(old);
                            i->next = j;
                        }
                        else {
                            j = j->next;
                        }
                    }
                    else {
                        Node* old = j;
                        j = j->next;
                        free(old);
                        i->next = j;
                    }
                }
            }
            else {
                int H2,M2,H3,M3,nesto;
                H2 = atoi(i->data + 6);
                M2 = atoi(i->data + 9);
                H3 = atoi(j->data);
                M3 = atoi(j->data + 3);
                nesto = compare(H3,H2);
                if(nesto){
                    if(nesto == -1){
                        //gledamo mesto
                        int br1 = 0,br2 = 0,x = 12;
                        while((q->data[x]) != ' '){
                            if(q->data[x] == i->data[x] && q->data[x] == j->data[x]){
                                br1++;
                                br2++;
                            }
                            else if(q->data[x] == i->data[x]){
                                br1++;
                            }
                            else if(q->data[x] == j->data[x]){
                                br2++;
                            }
                            x++;
                        }
                        if( x - 12 == br1 && x - 12 != br2){
                            //izbaciti j-ti
                            Node* old = j;
                            j = j->next;
                            free(old);
                            i->next = j;
                        }
                        else if( x - 12 == br2 && x - 12 != br1){
                            //izbaciti i-ti
                            Node* old = i;
                            i = i->next;
                            free(old);
                            q->next = i;
                            j = j->next;
                        }
                        else {
                            //izbaciti j-ti
                            Node* old = j;
                            j = j->next;
                            free(old);
                            i->next = j;
                        }
                    }
                    else {
                        j = j->next;
                    }
                }
                else {
                    nesto = compare(M3,M2);
                    if(nesto){
                        if(nesto == -1){
                            int br1 = 0,br2 = 0,x = 12;
                            while((q->data[x]) != ' '){
                                if(q->data[x] == i->data[x] && q->data[x] == j->data[x]){
                                    br1++;
                                    br2++;
                                }
                                else if(q->data[x] == i->data[x]){
                                    br1++;
                                }
                                else if(q->data[x] == j->data[x]){
                                    br2++;
                                }
                                x++;
                            }
                            if( x - 12 == br1 && x - 12 != br2){
                                Node* old = j;
                                j = j->next;
                                free(old);
                                i->next = j;
                            }
                            else if( x - 12 == br2 && x - 12 != br1){
                                Node* old = i;
                                i = i->next;
                                free(old);
                                q->next = i;
                                j = j->next;
                            }
                            else {
                                Node* old = j;
                                j = j->next;
                                free(old);
                                i->next = j;
                            }
                            //gledamo mesto

                        }
                        else {
                            j = j->next;
                        }
                    }
                    else {
                        j = j->next;
                    }
                }
            }
        }
        if (i != head){
            q = q->next;
        }
        i = i->next;
    }
}

void freeList (Node *head){
    Node *current = head;
    while (current != NULL) {
        Node *old = current;
        current = current->next;
        free(old);
    }
}

int main() {
    Node* head = Napravilistu();
    sortList(head);
    printList(head);
    freeList(head);
    exit(0);
    //return 0;
}
