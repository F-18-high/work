#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//liste des pages
 typedef struct page{
	int adresse;
	int T ;
	struct page *page_svt;
}page;


//liste programme
 typedef struct prog{
	char nom[15];
	int taille;
    struct page *page_prog;
	struct prog *prog_svt;
}prog;

//prototypes
page * creation_liste_espace(page *p);
void afficher_espace(page* p);
int trouver_nbrPages(int t,page *p);
int Nbr_Elemt(page* pv);
page * creation_page(page *p, int t);
void afficher_page(page* pv);
prog* charger_prgm( prog * pgm,char l[],int taille, page*p);
page* supprimer_pages_charges( page *p,int taille);
prog* creation_programme(page* pg, prog* s,char n[] ,int t);
void afficher_prog( prog *p);
void afficher_prog_pages( prog *p);
void afficher_pages_prog( prog *p,char l[]);
prog * supprimer_prog( prog *pgm, char l[]);
page* fusionner( page* p, page* pg);
int get_taille(prog *p,char l[]);
page* get_listpage(prog *p,char l[]);
page * supprimerElementEnFin(page * pg);
int charcher(prog *p,char l[]);
void formater(char nom[20]);
char*  etat_memoire(prog *listeProg);


int main()
{
   // system("color 30");
    char choix[15];
    int t;
    char n[15];
    int taille;
    page * p = NULL;
    page *pg;
    prog *pgm=NULL;
	p=(page*)(malloc(sizeof(page)));
	p->adresse=0;
    p->page_svt=NULL;
    p=creation_liste_espace(p);



/*Afficher le menu à l'utilisateur*/
	system("cls");
    system("COLOR 30");
    system("COLOR 30");
    system("cls");
    printf("\n\n");
    printf("\n\t\t\t\t\t\t    Bonjour (^_^) !!\n\t\t\t\t\t   Gestion de la memoire par pagination\n ");




 while (strcmp(choix,"9")!=0) {

    printf("\n                                 +******************************************************+\n");
    printf("                                 |                   Pagination memoire                 |\n");
    printf("                                 |                      ~~ MENU ~~                      |\n");
    printf("                                 +******************************************************+\n");
    printf("                                 |              1 . Charger un programme                |\n");
    printf("                                 |              2 . Afficher les pages vides            |\n");
    printf("                                 |              3 . Afficher la lise des programmes     |\n");
    printf("                                 |              4 . chercher un programme               |\n");
    printf("                                 |              5 . Afficher les programme par pages    |\n");
    printf("                                 |              6 . Terminer l'execution d'un programme |\n");
    printf("                                 |              7 . Afficher la memoire centrale        |\n");
    printf("                                 |              8 . Vider la memoire                    |\n");
    printf("                                 |              9 . Quitter                             |\n");
    printf("                                 ********************************************************\n");

		printf("\n--------> Veuillez selectionner une option: ");
		scanf("%s", &choix);
		printf("\n");


		if (strcmp(choix,"1") == 0) {

			printf("--------> Veuillez saisir le nom du programme a charger: ");
			scanf("%s", &n);
			printf("--------> veuillez saisir la taille de ce programme: ");
			scanf("%d", &taille);

            pgm=charger_prgm(pgm,n, taille, p);
		}
		else if (strcmp(choix,"2") == 0) {
            int l=Nbr_Elemt(p);
         if(l==0){
            printf("\n----------Aucune page vide n'existe dans la memoire !!!! \n\n");
         }
         else{
           printf("\n----------Les pages vides dans la memoire : \n\n");
            afficher_espace(p);
            printf("\n");
         }
		}
		else if (strcmp(choix,"3") == 0) {

            int s=Nbr_Elemt(p);
            if(s==25){
                printf("\n");
                printf("----------la memoire est vide !!!");
                printf("\n");
            }
            else{
                printf ("\n----------La lise des programmes : \n");
                afficher_prog(pgm);
                printf("\n");
            }
		}
		else if (strcmp(choix,"4") == 0) {
            printf("--------> Veuillez saisir le nom du programme a afficher: ");
			scanf("%s", &n);
            int v=charcher(pgm,n);
           if(v==0){
                printf("\n");
             printf("----------Ce programme n'existe pas !!!!\n");

           }
           else{
              printf("\n");
              printf("\n----------Les pages du programme %s : \n\n",n);
              printf("\t    ");
              afficher_pages_prog(pgm,n);
              printf("\n");
           }

		}
		else if (strcmp(choix,"5") == 0) {
		    int s=Nbr_Elemt(p);
                if(s==25){
                printf("\n");
                printf("--------!!!la memoire est vide!!!-------");
                printf("\n");
            }
            else{
               printf("\n----------La Liste des programmes : \n");
               afficher_prog_pages(pgm);
            }

		}
		else if (strcmp(choix,"6") == 0) {

			printf("--------> Veuillez saisir le nom du programme a supprimer: ");
			scanf("%s", &n);
           int v=charcher(pgm,n);
          if(v==0){
             printf("----------Ce programme n'existe pas !!!!!\n");
          }
          else{
            pg=get_listpage(pgm,n);
            pg=supprimerElementEnFin(pg);
            pgm=supprimer_prog(pgm, n);
            printf("--------le programme a ete bien supprime-------\n");
            p=fusionner(p->page_svt,pg);
          }
		}
		else if (strcmp(choix,"7") == 0) {
        etat_memoire(pgm);
		}
		else if(strcmp(choix,"8")==0){
            if(pgm==NULL){
                printf("La m%cmoire est d%cja vide !!!!",130,138);
            }
            else{
                while(pgm!=NULL){
                pg=get_listpage(pgm,pgm->nom);
                pg=supprimerElementEnFin(pg);
                pgm=supprimer_prog(pgm, pgm->nom);
                p=fusionner(p->page_svt,pg);
		    }
		    printf("La m%cmoire a bien %ct%c vid%c ",130,130,130,130);
            }

		}
		else {

            printf(" !!!!!!!! veuillez saisir un numero depuis le menu !!!!!!! \n");

		}
}
 printf("\n\n *~~~~~~~~~~ Merci pour avoir utilise ce programme (^_^) a tres bientot ~~~~~~~~~~*  \n\n");
return 0;
}
struct page * creation_liste_espace(struct page *p){
        struct page* nouveau = NULL;
        nouveau=(struct page*)(malloc(sizeof(struct page)));
        nouveau->adresse=1;
        nouveau->page_svt=NULL;
        nouveau->T=rand()%5+1;
        int size=nouveau->T;
        int i=2;
        p->page_svt=nouveau;
        while (size < 100) {
        struct page * courant = NULL;
        courant=(struct page*)(malloc(sizeof(struct page)));
        courant->adresse=i;
        courant->T=rand()%5+1;
        courant->adresse=(nouveau->adresse)+(nouveau->T)+1;
        courant->page_svt=NULL;
        nouveau->page_svt=courant;
        nouveau= nouveau->page_svt;
        size = size+(courant->T);
        i+=1;
    }
  return p;
}

void afficher_espace(page* p){

     while(p->page_svt->page_svt!=NULL){
         printf(" %d de taille %d  \n\n", p->page_svt->adresse , p->page_svt->T );
         p=p->page_svt;
    }
}

int trouver_nbrPages(int taille , page *p){
int nbr_pages=0 ;

    while (taille > 0 ){
        taille = taille - p->page_svt->T;
        nbr_pages=nbr_pages+1;

        p=p->page_svt;
    }


  return nbr_pages ;
}


int Nbr_Elemt(page* p){
  int n=0;
  while(p->page_svt->page_svt!=NULL){
         n=n+1;
         p=p->page_svt;}
 return n;
}

page * creation_page(page *p, int t){
  page * pg = NULL;
	pg=(page*)(malloc(sizeof(page)));

	pg->adresse=0;
	pg->page_svt=NULL;
	page * nouveau = NULL;
	nouveau=(page*)(malloc(sizeof(page)));
    nouveau->adresse=p->page_svt->adresse;
    nouveau->page_svt=NULL;
    pg->page_svt=nouveau;

    for(int i=2; i<=t+1; i++){
        page * courant = NULL;
        courant=(page*)(malloc(sizeof(page)));
        courant->adresse=p->page_svt->page_svt->adresse;
        courant->page_svt=NULL;
        nouveau->page_svt=courant;
        nouveau= nouveau->page_svt;
        p=p->page_svt;

    	}
   return pg;
}

void afficher_page(page* pv){
     while(pv->page_svt->page_svt!=NULL){
         printf(" %d ", pv->page_svt->adresse);
         pv=pv->page_svt;
    }
}


page * supprimer_pages_charges(page *pr,int taille){
      page *nouveau;
      for (int i=0; i<taille ;i++){
       nouveau=pr->page_svt;
       pr->page_svt=pr->page_svt->page_svt;
        free(nouveau);
       }
  return pr;
}


void afficher_prog(prog *p){
     while(p!=NULL){
        printf("-----------------# %s \n",p->nom);
        p=p->prog_svt;
    }
}

void afficher_prog_pages(prog *p){
     while(p!=NULL){
        printf("-----------------# %s  :",p->nom);
        afficher_page(p->page_prog);
        printf("\n");
        p=p->prog_svt;
    }
}

prog* creation_programme(page* pg, prog* s,char n[] ,int t){
   prog* p;
   p = (prog*)malloc(sizeof(prog));
   strcpy(p->nom,n);
   p->taille=t;
   p->page_prog = pg;
   p->prog_svt = s;
 return p;
}

prog* charger_prgm( prog * pgm,char l[],int taille, page *p){
  if(taille<=0){
     printf("----------!!!taille insuportable!!!! \n");
  }
  else{
       page * nv = NULL;
       int t=trouver_nbrPages(taille,p);
       int n=Nbr_Elemt(p);
       int v=charcher(pgm,l);
  if(v==0){
      if (t>n){
         printf("----------!!!Memoire pleine!!! \n");
      }
    else{
          page * Pg = NULL;
	      Pg=(page*)(malloc(sizeof(page)));
          Pg=creation_page(p, t);
          page * nv = NULL;
        nv=(page*)(malloc(sizeof(page)));
        nv=supprimer_pages_charges(p,t);
         printf("\n");
         if (pgm==NULL){
            pgm=creation_programme(Pg,NULL,l,t);
            printf("--------------le programme a ete bien enregistre \n");
         }
         else{
            prog *tmp;
            tmp=(prog*)(malloc(sizeof(prog)));
            tmp=pgm;
            while(tmp->prog_svt != NULL){

                 tmp = tmp->prog_svt;
            }
           tmp->prog_svt = creation_programme(Pg,NULL,l,t);
           printf("--------------le programme a ete bien enregistre \n");
         }
       }
   }
  else{
    printf("----------!!!!ce programme existe deja!!!! ");
  }
  }
 return pgm;
}

void afficher_pages_prog(prog *p,char l[]){

    while(p!=NULL){

         if(strcmp(l,p->nom)==0){
         afficher_page(p->page_prog);
          }
         p=p->prog_svt;
    }
}

int charcher(prog *p,char l[]){
   int v=0;
    while(p!=NULL){

         if(strcmp(l,p->nom)==0){
             v=1;
          }
         p=p->prog_svt;
    }
  return v;
}

page* get_listpage(prog *p,char l[]){

  prog * tmp = (prog * ) malloc(sizeof(prog * ));
  tmp = p;
  while (tmp) {
    if (strcmp(tmp->nom, l) == 0) {
      return tmp->page_prog;
    }
    tmp = tmp->prog_svt;
  }
}

prog * supprimer_prog(prog *pgm, char l[]){
    if(pgm == NULL)
        return NULL;
    if(strcmp(l,pgm->nom)==0)
    {
        prog* tmp = pgm->prog_svt;
        free(pgm);
        tmp = supprimer_prog(tmp, l);
        return tmp;
    }
    else
    {
        pgm->prog_svt = supprimer_prog(pgm->prog_svt,l);
        return pgm;
    }
 }

page* fusionner(page* p,page* pg)
{
    page* temp1=p;
    page* temp2=pg;

      if(temp1==NULL)
      {
         return temp2;
      }
      else if(temp2==NULL)
      {
         return temp1;
      }
      else if ((temp1->adresse) <= (temp2->adresse))
     {
          temp1->page_svt = fusionner(temp1->page_svt,temp2);
          return(temp1);
     }
      else
     {
         temp2->page_svt = fusionner(temp1,temp2->page_svt);
          return(temp2);
     }
}


page * supprimerElementEnFin(page * pg)
{
    if(pg == NULL)
        return NULL;
    if(pg->page_svt == NULL)
    {
        free(pg);
        return NULL;
    }

    page* tmp = pg;
    page* ptmp = pg;
    while(tmp->page_svt != NULL)
    {
        ptmp = tmp;
        tmp = tmp->page_svt;
    }
    ptmp->page_svt= NULL;
    free(tmp);
    return pg;
}

/****************************************Affichage**************************************************/

char*  etat_memoire(struct prog *listeProg){

    struct prog *p;
    p=listeProg;

    char T[100][10]={"--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--"};

    while(p!=NULL){
              struct page *temp;
               temp=p->page_prog;
                while(temp->page_svt->page_svt!=NULL){

                temp=temp->page_svt;

                int j=temp->adresse;
                strcpy(T[j-1],p->nom);
            }
            temp=NULL;

            p=p->prog_svt;
    }


   printf("\n\t+************************+\n\t");
   printf("|\t\t\t\t\t\t\t\t     |\n");
   printf("\t|\t\t\t   Memoire Centrale   \t\t\t     |\n");
   printf("\t|\t\t\t\t\t\t\t\t     |\n");
   printf("\t+****++****++****++****++****++****++****++****++****++****+\n\t");
    for (int i=0;i<10;i++){
        formater(T[i]);
    }
    printf("\n");
   printf("\t+****++****++****++****++****++****++****++****++****++****+\n\t");
    for (int i=10;i<20;i++){
        formater(T[i]);
    }
    printf("\n");
   printf("\t+****++****++****++****++****++****++****++****++****++****+\n\t");
    for (int i=20;i<30;i++){
        formater(T[i]);
    }
    printf("\n");
   printf("\t+****++****++****++****++****++****++****++****++****++****+\n\t");
    for (int i=30;i<40;i++){
        formater(T[i]);
    }
    printf("\n");
   printf("\t+****++****++****++****++****++****++****++****++****++****+\n\t");
    for (int i=40;i<50;i++){
        formater(T[i]);
    }
    printf("\n");
   printf("\t+****++****++****++****++****++****++****++****++****++****+\n\t");

    for (int i=50;i<60;i++){
        formater(T[i]);}

    printf("\n");
   printf("\t+****++****++****++****++****++****++****++****++****++****+\n\t");

    for (int i=60;i<70;i++){
        formater(T[i]);
    }
   printf("\t+****++****++****++****++****++****++****++****++****++****+\n\t");

    for (int i=70;i<80;i++){
        formater(T[i]);

    }

   printf("\t+****++****++****++****++****++****++****++****++****++****+\n\t");

    for (int i=80;i<90;i++){
        formater(T[i]);
    }

    printf("\t+****++****++****++****++****++****++****++****++****++****+\n\t");

    for (int i=90;i<100;i++){
        formater(T[i]);
    }

    printf("\t+****++****++****++****++****++****++****++****++****++****+\n\t");


    return T;
}


void formater(char nom[20]) {

  char var [20] = "";
  int b = strlen(nom);
  if (b == 12) {
    printf("|%s|", nom);
    //system("PAUSE");
  } else {
    int m = 12 - strlen(nom);
    int i;
    for (i = 0; i < m / 2; i++) {
      var [i] = ' ';
    }
    for (i = m / 2; i < b + m / 2; i++) {
      var [i] = nom[i - m / 2];
    }
    for (i = b + m / 2; i < b + m; i++) {
      var [i] = ' ';
    }

    printf("|%s|",var);

  }

}
