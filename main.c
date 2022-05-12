#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ANNEE  9999
#define MIN_ANNEE  1900
#define MAX_SIZE_NOM 40
#define MAX_SIZE_PASSWORD  30
#define FILE_NAME  "gestion_bibliotheque.bin"
#define EMPRUNTE_FILE "livres_emprunte.bin"
#define LIVRES_FILE  "livres.bin"
#define MAX_NOM_LIVRE   50
#define MAX_NOM_AUTEUR 50
#define MAX_NOM_etudiant 50
#define MAX_ADDRESS_etudiant 300
#define FILE_HEADER_SIZE  sizeof(etudiant)

// Plan de programme
// 1.Adminstration
//     1.1-ajouter_livre
//     1.2-afficher_livres
//     1.3-chercher_livre
//     1.4-supprimer
//     1.5-listes des etudiant inscrit
//     1.6-listes des empruntes
// 2.etudiant
//     1.1-emprunte
//     1.2-afficher_livres
//     1.3-chercher_livre
//     1.4-profile
// 3.fonctions de affichage 
//     afficher_message_milieu
//     en_tete
//     bienvenue
// 4.fonction aider 
//     Nom_valide
//     livre existe 
//     fichie_existe
// 5.Connextion et inscription
//     login (etudiante , admin)
//     inscription
// 5.menu
//     menu administration
//     menu etudiante

//structure to store date
typedef struct
{
    int aaaa;
    int m;
    int j;
} Date;
typedef struct
{
    char CNE[30];
    char nom[MAX_SIZE_NOM];
    char prenom[MAX_SIZE_NOM];
    char email[50];
    char tel[30];
    char password[MAX_SIZE_PASSWORD];
} etudiant;
typedef struct
{
    char nom[MAX_SIZE_NOM];
    char password[MAX_SIZE_PASSWORD];
}admin;
typedef struct
{
    unsigned int num_livre;
    char titre[MAX_NOM_LIVRE];
    char theme[40];
    char langue[40];
    int nbr_pages;
    int annee_publication;
    char auteurNom[MAX_NOM_AUTEUR];
    char editeurNom[MAX_NOM_AUTEUR];
    char date[60];
} livre;

typedef struct{
    int livre_id;
    etudiant u;
    char date_emprunte[60];
}emprunte;

void afficher_message_milieu(const char* message)
{
    int len =0;
    int pos = 0;
//    calculer nombre des spaces a afficher
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
}
void en_tete(char * message)
{
    system("cls");
    printf("\n\n\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############      Gestion de bibliotheque en C     	       ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    afficher_message_milieu(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");
    printf("\n\t\t\t----------------------------------------------------------------------------");
}
void bienvenue()
{
    en_tete("Genie informatique 1 ---- ENSAH ");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                 Bienvenue                 =");
    printf("\n\t\t\t        =                   au                      =");
    printf("\n\t\t\t        =                 Bibliotheque              =");
    printf("\n\t\t\t        =                                   	    =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
}
int Nom_valide(const char *nom)
{
    int NomValid = 1;
    int len = 0;
    int index = 0;
    len = strlen(nom);
    for(index =0; index <len ; ++index)
    {
        if(!(isalpha(nom[index])) && (nom[index] != '\n') && (nom[index] != ' '))
        {
            NomValid = 0;
            break;
        }
    }
    return NomValid;
}

int valid_CNE (const char *CNE)
{
	int valid = 1;
	int len = 0,i;
	len=strlen(CNE);
	if(!isalpha(CNE[0])){
		valid=0;
	}
	else if(len>12){
		valid=0;
	}
	for(i=2;i<len;i++){
		if(isalpha(CNE[i])){
			valid=0;
		}
	}
	return valid;
}

// Ajouter un livre
void ajouter_livre()
{
    int jours;
    livre nouveauLivre = {0};
    FILE *fp = NULL;
    int status = 0;
    int etat = 0,i=0;
    fp = fopen(LIVRES_FILE,"a");
    if(fp == NULL)
    {
        printf("Error fichier n'est pas lire\n");
        exit(1);
    }
    en_tete("Ajouter nouveau livre");
    printf("\n\n\t\t\tENTRER LES INFORMATIONS DE LIVRE:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    do
    {
        printf("\n\t\t\tNumero de livre  = ");
        fflush(stdin);
        scanf("%u",&nouveauLivre.num_livre);
        etat=Livre_existe(nouveauLivre.num_livre);
        if(etat){
            printf("\n\t\t ce numero de livre deja existe");
        }
        i++;
    } while (etat && i<=4);
    if(i>4 || etat){
        exit(1);
    }
    do
    {
        printf("\n\t\t\tNom de livre  = ");
        fflush(stdin);
        fgets(nouveauLivre.titre,MAX_NOM_LIVRE,stdin);
        status = Nom_valide(nouveauLivre.titre);
        if (!status)
        {
            printf("\n\t\t\tle titre entre est incorrecte.");
        }
    }while(!status);
    do
    {
        printf("\n\t\t\theme de livre  = ");
        fflush(stdin);
        fgets(nouveauLivre.theme,40,stdin);
        status = Nom_valide(nouveauLivre.theme);
        if (!status)
        {
            printf("\n\t\t\theme est incorrecte. essayer a� nouveau.");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tLangue de livre = ");
        fflush(stdin);
        fgets(nouveauLivre.langue,40,stdin);
        status = Nom_valide(nouveauLivre.langue);
        if (!status)
        {
            printf("\n\t\tlangue est incorrecte. essayer a� nouveau.");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tAuteur  = ");
        fflush(stdin);
        fgets(nouveauLivre.auteurNom,MAX_NOM_AUTEUR,stdin);
        status = Nom_valide(nouveauLivre.auteurNom);
        if (!status)
        {
            printf("\n\t\t\nom de l'auteur est incorrecte. essayer à nouveau.");
        }
    }
    while(!status);

    printf("\n\t\t\tNombres des pages  = ");
    fflush(stdin);
    scanf("%d",&nouveauLivre.nbr_pages);
    do
    {
        printf("\n\t\t\t\tEditeur  = ");
        fflush(stdin);
        fgets(nouveauLivre.editeurNom,MAX_NOM_AUTEUR,stdin);
        status = Nom_valide(nouveauLivre.editeurNom);
        if (!status)
        {
            printf("\n\t\t\tNom de l'editeur est incorrecte. essayer a� nouveau.");
        }
    }
    while(!status);

    printf("\n\t\t\tAnnee de publication  = ");
    fflush(stdin);
    scanf("%d",&nouveauLivre.annee_publication);

    time_t t;
    time(&t);
    strcpy(nouveauLivre.date,ctime(&t));
    fwrite(&nouveauLivre,sizeof(nouveauLivre), 1, fp);
    fclose(fp);
}

void chercher_livre()
{
    int exist = 0,choix=0,recherche_by=0,livreId;
    char NomLivre[MAX_NOM_LIVRE] = {0};
    livre nouveauLivre = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(LIVRES_FILE,"r");
    if(fp == NULL)
    {
        printf("\n\t\t\tfichier ne peut ouvrir\n");
        exit(1);
    }
    en_tete("RECHRCHE UN LIVRE");
    //put the control on books detail
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tError la lecture de fichier est impossible\n");
        exit(1);
    }
    while(choix == 0){
    printf("\n\t\t\tchercher par :\n");
    printf("\n\t\t\t0 \t : \tID");
    printf("\n\t\t\t1 \t : Titre\n");
    scanf("%d",&recherche_by);
    rewind(fp);
    if(recherche_by==0){
        printf("\n\n\t\t\tEntrer Num de livre:");
        fflush(stdin);
        scanf("%d",&livreId);
        while (fread (&nouveauLivre, sizeof(nouveauLivre), 1, fp))
        {
            if(nouveauLivre.num_livre == livreId)
            {
                exist = 1;
                break;
            }
        }
    }
    else{
        printf("\n\n\t\t\tEntrer le Titre de livre :");
        fflush(stdin);
        fgets(NomLivre,MAX_NOM_LIVRE,stdin);
        while (fread (&nouveauLivre, sizeof(nouveauLivre), 1, fp))
        {
            if(!strcmp(nouveauLivre.titre, NomLivre))
            {
                exist = 1;
                break;
            }
        }
    }
    if(exist)
    {
        printf("\n\t\tNum de livre = %u\n",nouveauLivre.num_livre);
        printf("\t\tTitre de livre = %s",nouveauLivre.titre);
        printf("\n\t\ttheme de livre = %s\n",nouveauLivre.theme);
        printf("\n\t\tlangue de livre = %s\n",nouveauLivre.langue);
        printf("\n\t\tnombre de page de livre = %d\n",nouveauLivre.nbr_pages);
        printf("\n\t\tannee de publication de livre = %d\n",nouveauLivre.annee_publication);
        printf("\t\tAuteur de livre = %s",nouveauLivre.auteurNom);
        printf("\t\tediteur de livre = %s",nouveauLivre.editeurNom);
        printf("\t\tlivre ajoute a  =  %s",nouveauLivre.date);
    }
    else
    {
        printf("\n\t\t\tAUcun livre");
    }
    printf("\n\t\t\t0 : continue la recherche \n");
    printf("\t\t\t1 : arrete la recherche \n");
    scanf("%d",&choix);
    fclose(fp);
    }
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    getchar();
}

int nbr_livres(){
    int i=0;
    FILE *fp=NULL;
    livre L;
    fp = fopen(LIVRES_FILE,"r");
    if(fp==NULL)
        return i;
    else{
        while (fread(&L,sizeof(L),1,fp))
        {
            i++;
        }
        return i;
    }
}

// voir les livres
void afficher_livres()
{
    int exist = 0;
    char titre[MAX_NOM_LIVRE] = {0};
    livre nouveauLivre = {0};
    FILE *fp = NULL;
    int status = 0;
    unsigned int countlivres = 1;
    en_tete("Liste des livres");
    printf("\n\t\t\t\t\tNombre des livres : %d\n",nbr_livres());
    printf("\t\t\t---------------------------------------------------------------------------");
    fp = fopen(LIVRES_FILE,"r");
    if(fp == NULL)
    {
        printf("error lors de lire le fichier\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("error lors de lire le fichier\n");
        exit(1);
    }
    rewind(fp);
    while (fread(&nouveauLivre, sizeof(nouveauLivre), 1, fp))
    {
        printf("\n\t\t\tlivre = %u\n\n",countlivres);
        printf("\t\t\tNum de livre = %u",nouveauLivre.num_livre);
        printf("\n\t\t\tNom de livre = %s",nouveauLivre.titre);
        printf("\n\t\t\theme de livre = %s",nouveauLivre.theme);
        printf("\n\t\t\tlangue de livre = %s",nouveauLivre.langue);
        printf("\n\t\t\tauteur de livre = %s",nouveauLivre.auteurNom);
        printf("\n\t\t\tediteur de livre = %s",nouveauLivre.editeurNom);
        printf("\n\t\t\tPages = %d",nouveauLivre.nbr_pages);
        printf("\n\t\t\tDate d'ajout : %s\n\n",nouveauLivre.date);
        if(livre_demande(nouveauLivre.num_livre)!=0){
        	printf("\n\n\t\t\tCe livre est deja demande");
		}
        printf("\t\t\t----------------------------------------------------------------------\n");
        exist = 1;
        ++countlivres;
    }
    fclose(fp);
    if(!exist)
    {
        printf("\n\t\t\taucun livre existe");
    }
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}

// supprimer livre
void supprimer()
{
    int exist = 0;
    int livre_supp = 0;
    etudiant etudiant_info = {0};
    char titre[MAX_NOM_LIVRE] = {0};
    livre nouveauLivre = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    int status = 0;
    en_tete("Supprimer un livre");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("error lors de lire le fichier\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("error lors de lire le fichier\n");
        exit(1);
    }
    fread (&etudiant_info,FILE_HEADER_SIZE, 1, fp);
    fwrite(&etudiant_info,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\t\t\tEntrer le numero de livre a supprimme :");
    scanf("%d",&livre_supp);
    while (fread (&nouveauLivre, sizeof(nouveauLivre), 1, fp))
    {
        if(nouveauLivre.num_livre != livre_supp)
        {
            fwrite(&nouveauLivre,sizeof(nouveauLivre), 1, tmpFp);
        }
        else
        {
            exist = 1;
        }
    }
    (exist)? printf("\n\t\t\tlivre est supprimer....."):printf("\n\t\t\taucun livre");
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);
}

int Livre_existe(int num)
{
    livre nouveauLivre = {0};
    FILE *fp = NULL;
    int exist = 0;
    fp = fopen(LIVRES_FILE,"r");
    rewind(fp);
    while (fread (&nouveauLivre, sizeof(nouveauLivre), 1, fp))
    {
        if(nouveauLivre.num_livre == num)
        {
            exist = 1;
            break;
        }
    }
    return exist;
}

int livre_demande (int num_livre)
{
    int exist=0;
    FILE *fp=NULL;
    fp=fopen(EMPRUNTE_FILE,"r");
    emprunte emp={0};

//    rewind(fp);
    while (fread(&emp,sizeof(emp),1,fp))
    {
        if(emp.livre_id==num_livre)
        	exist=1;
    }
    fclose(fp);
    return exist;
}

void liste_empruntes ()
{
    int exist=0;
    FILE *fp=NULL;
    fp=fopen(EMPRUNTE_FILE,"r");
    emprunte emp={0};
    en_tete("Liste des empruntes");
    if(fp==NULL){
        printf("\n\t\t\terror lors de lire cette fichier");
        exit(1);
    }
    rewind(fp);
    while (fread(&emp,sizeof(emp),1,fp))
    {
        printf("\n\t\t\t Num de livre : %d",emp.livre_id);
        printf("\n\t\t\t Emprunte par : ");
        printf("\n\t\t\t\t- %s",emp.u.CNE);
        printf("\n\t\t\t\t- %s",emp.u.nom);
        printf("\n\t\t\t\t- %s",emp.u.email);
        printf("\n\t\t\t- %s",emp.u.tel);
        printf("\n\n\t\t\t- %s",emp.date_emprunte);
        printf("\t\t\t------------------------------------------------------");
        exist=1;
    }
    fclose(fp);
    if(!exist)
    {
        printf("\n\t\t\taucun demande d'emprunte existe");
    }
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}

void listes_etudiants(){
    int exist = 0;
    etudiant u = {0};
    FILE *fp = NULL;
    unsigned int countusers = 1;
    en_tete("Liste des etudiants");
    printf("\n\t\t\t\t\tNombre de etudiants : %d\n",nbr_etudiants());
    printf("\t\t\t------------------------------------------------------");
    fp = fopen(FILE_NAME,"r");
    if(fp == NULL)
    {
        printf("error lors de lire le fichier\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("Facing issue while reading file\n");
        exit(1);
    }
    rewind(fp);
    while (fread(&u, sizeof(u), 1, fp))
    {
        printf("\n\t\t\tNombre de utilisteur = %u\n",countusers);
        printf("\n\t\t\tNom = %s",u.nom);
        printf("\n\t\t\tPrenome = %s",u.prenom);
        printf("\n\t\t\tEmail = %s",u.email);
        printf("\n\t\t\tTelephone = %s",u.tel);
        printf("\t\t\t------------------------------------------------------");
        exist = 1;
        ++countusers;
    }
    fclose(fp); 
    if(!exist)
    {
        printf("\n\t\t\taucun etudiant existe");
    }
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}

int nbr_etudiants(){
    int i=0;
    FILE *fp=NULL;
    etudiant u;
    fp = fopen(FILE_NAME,"r");
    if(fp==NULL)
        return i;
    else{
        while (fread(&u,sizeof(u),1,fp))
        {
            i++;
        }
        return i;
    }
}

// emprunter un livre
void emprunter (etudiant user)
{
    int exist=0;
    emprunte emp;
    int num_livre;
    etudiant U;
    FILE *fp=NULL;
    fp=fopen(EMPRUNTE_FILE,"a");
    en_tete("Emprunter un livre");
    int status = 0;
    if(fp == NULL)
    {
        printf("Error fichier n'est pas lire\n");
        exit(1);
    }
    int i=0;
    do
    {
        printf("\n\t\t\tNumero de livre  = ");
        fflush(stdin);
        scanf("%u",&num_livre);
        status=Livre_existe(num_livre);
        if(!status){
            printf("\n\t\t\t ce livre n'existe pas");
        }
        i++;
    } while (!status && i<=3);
    if(i>3 || !status){
        exit(1);
    }
    emp.livre_id=num_livre;
    emp.u=user;

    time_t t;
    time(&t);
    strcpy(emp.date_emprunte,ctime(&t));
    afficher_message_milieu("votre demande a effectue");
    fwrite(&emp,sizeof(emp), 1, fp);
    fclose(fp);
}

// Retourner livre
void retourne_livre(etudiant E)
{
    int exist = 0;
    int livre_ret = 0;
    emprunte emp = {0};
    livre nouveauLivre = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    int status = 0;
    en_tete("Retourner un livre");
    fp = fopen(EMPRUNTE_FILE,"rb");
    if(fp == NULL)
    {
        printf("error lors de lire le fichier\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("error lors de lire le fichier\n");
        exit(1);
    }
    fread (&emp,sizeof(emprunte), 1, fp);
    fwrite(&emp,sizeof(emprunte), 1, tmpFp);
    printf("\n\t\t\tEntre numero de livre : ");
    scanf("%d",&livre_ret);
    while (fread (&emp, sizeof(emp), 1, fp))
    {
        if(emp.livre_id != livre_ret && emp.u.CNE != E.CNE)
        {
            fwrite(&emp,sizeof(emp), 1, tmpFp);
        }
        else
        {
            exist = 1;
        }
    }
    (exist)? printf("\n\t\t\tlivre est retourner....."):printf("\n\t\t\taucun livre");
    fclose(fp);
    fclose(tmpFp);
    remove(EMPRUNTE_FILE);
    rename("tmp.bin",EMPRUNTE_FILE);
}


void profile (etudiant e)
{
    en_tete("Profile");
    printf("\n\t\t\t CNE :\t %s",e.CNE);
    printf("\n\t\t\t Nom :\t %s",e.nom);
    printf("\n\t\t\t Prenome :\t %s",e.prenom);
    printf("\n\t\t\t email :\t %s",e.email);
    printf("\n\t\t\t tel :\t %s",e.tel);
}



void menu_etudiant(etudiant user)
{

    int choix = 0;
   
        en_tete("MENU");
        printf("\n\t\t\t1.Voir les livres");
        printf("\n\t\t\t2.Search un livre");
        printf("\n\t\t\t3.emprinter un livre");
        printf("\n\t\t\t4.Retourner un livre");
        printf("\n\t\t\t5.profile");
        printf("\n\t\t\t0.quitter");
        printf("\n\n\n\t\t\tEntrer le choix => ");
        scanf("%d",&choix);
        switch(choix)
        {
        case 1:
            afficher_livres();
            break;
        case 2:
            chercher_livre();
            break;
        case 3:
            emprunter(user);
            break;
        case 4:
            retourne_livre(user);
            break;
        case 5:
            profile(user);
            break;
        case 0:
            printf("\n\n\n\t\t\t\tMerci\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tChoix incorrecte essaye a nouveau !!!!!...");
        }                                            //Switch Ended
}

void menu_admin()
{

    int choix = 0;
    do
    {
        en_tete("MENU");
        printf("\n\n\n\t\t\t1.Add un livre");
        printf("\n\t\t\t2.Search un livre");
        printf("\n\t\t\t3.Voir les livres");
        printf("\n\t\t\t4.supprimer un livre");
        printf("\n\t\t\t5.listes des etudiants");
        printf("\n\t\t\t6.listes des empruntes");
        printf("\n\t\t\t0.quitter");
        printf("\n\n\n\t\t\tEntrer le choix => ");
        scanf("%d",&choix);
        switch(choix)
        {
        case 1:
            ajouter_livre();
            break;
        case 2:
            chercher_livre();
            break;
        case 3:
            afficher_livres();
            break;
        case 4:
            supprimer();
            break;
        case 5:
            listes_etudiants();
            break;
        case 6:
            liste_empruntes();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tMerci\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tChoix incorrecte essaye a nouveau !!!!!...");
        }
    }
    while(choix!=0);
}
//login
void login(){
    int choix;
    en_tete("Connextion");
    printf("\n\n\n\t\t\t 0 : Connecte comme un utlisateur");
    printf("\n\n\n\t\t\t 1 : Connecte comme un Admin\n\n\t\t\t\t");
    scanf("%d",&choix);
    if(choix==1)
        login_admin();
    else
        login_etudiant();
}


void login_etudiant ()
{
    unsigned char CNE[30] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int L=0;
    etudiant etudiant_info = {0};
    FILE *fp = NULL;
    en_tete("Login");
    fp = fopen(FILE_NAME,"rb");
    int opt=0,choix;
    if(fp == NULL)
    {
        printf("\n\t\t\t0 : cree un compte");
        printf("\n\t\t\t1 : Exite :\n");
        scanf("%d",&opt);
        if(opt==0)
            inscription();
        else
            exit(1);
    }
    else{
        printf("\n\t\t\tvous avez un compte deja \n");
        printf("\n\t\t\t0 : Non");
        printf("\n\t\t\t1 : Oui\n\t\t\t");
        scanf("%d",&opt);
        if(opt==0){
            inscription();
        }
        else{
            
            int valid = 0;
            do{
            	printf("\n\n\n\t\t\tCNE:");
	            fflush(stdin);
	            fgets(CNE,MAX_SIZE_NOM,stdin);
            	valid = valid_CNE(CNE);
            	if(valid==0){
            		printf("\n\t\t\tCNE invalid saisie a nouveau !!");
				}
			}while(valid == 0);
            printf("\n\t\t\t\tPassword:");
            fflush(stdin);
            fgets(password,MAX_SIZE_PASSWORD,stdin);
            while(fread(&etudiant_info,FILE_HEADER_SIZE, 1, fp)){
                if((!strcmp(CNE,etudiant_info.CNE)) && (!strcmp(password,etudiant_info.password)))
                {
                    menu_etudiant(etudiant_info);
                    break;
                }
            }
            printf("\t\t\t\tConnextion est echoue essaye a nouveau !!!!\n\n");
            printf("\n\t\t\tessaye a nouveau \n");
            printf("\n\t\t\t0 : Oui");
            printf("\n\t\t\t1 : Quitter\n\t\t\t");
            scanf("%d",&opt);
            if(opt==0){
                login_etudiant();
            }
            else
            {
                en_tete("Connextion echoue");
                printf("\n\t\t\t\tutlisateur n'est pas connu !!!.");
                getch();
                system("cls");
            }
        }
    }
}

void login_admin()
{
    unsigned char userName[MAX_SIZE_NOM] = "admin\n";
    unsigned char password[MAX_SIZE_PASSWORD] = "admin\n";
    int L=0;
    admin admin_info = {0};
    en_tete("Connecte comme admin");
    do
    {
        fflush(stdin);
        printf("\n\n\n\t\t\t\tUsername:");
        fgets(admin_info.nom,MAX_SIZE_NOM,stdin);
        fflush(stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(admin_info.password,MAX_SIZE_PASSWORD,stdin);
        if((strcmp(userName,admin_info.nom)==0) && (strcmp(password,admin_info.password)==0))
        {
            menu_admin();
        }
        else
        {
            printf("\t\t\t\tConnextion est echoue essaye a nouveau !!!!\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        en_tete("Connextion echoue");
        printf("\t\t\t\tn'est pas connu !!!.");
        getch();
        system("cls");
    }
}

int fichie_existe(const char *path)
{
    // Try to open file
    FILE *fp = fopen(path, "rb");
    int status = 0;
    // fichier existe
    if (fp != NULL)
    {
        status = 1;
        fclose(fp);
    }
    return status;
}
void inscription()
{
    FILE *fp = NULL;
    int status = 0;
    char userName[MAX_SIZE_NOM] = {0};
    char password[MAX_SIZE_PASSWORD] = {0};
    etudiant etudiant_info = {0};
    status = fichie_existe(FILE_NAME);
    fp = fopen(FILE_NAME,"ab");
    printf("\n\t\t\tentrer CNE :\n\t\t\t");
            int valid = 0;
            do{
            	printf("\n\n\n\t\t\tCNE:");
	            fflush(stdin);
	            fgets(etudiant_info.CNE,MAX_SIZE_NOM,stdin);
            	valid = valid_CNE(etudiant_info.CNE);
            	if(valid==0){
            		printf("\n\t\t\tCNE invalid saisie a nouveau !!");
				}
			}while(valid == 0);

            printf("\n\t\t\tentrer Nom :\n\t\t\t");
            fflush(stdin);
            fgets(etudiant_info.nom,MAX_SIZE_NOM,stdin);
            
            printf("\n\t\t\tentrer Prenome :\n\t\t\t");
            fflush(stdin);
            fgets(etudiant_info.prenom,MAX_SIZE_NOM,stdin);

            printf("\n\t\t\tentrer Email :\n\t\t\t");
            fflush(stdin);
            fgets(etudiant_info.email,50,stdin);

            printf("\n\t\t\tentrer Tel :\n\t\t\t");
            fflush(stdin);
            fgets(etudiant_info.tel,50,stdin);

            printf("\n\t\t\tentrer Password :\n\t\t\t");
            fflush(stdin);
            fgets(etudiant_info.password,MAX_SIZE_PASSWORD,stdin);

            fwrite(&etudiant_info,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
            login();
}

int main()
{
//    inscription();

    bienvenue();
    login();
    return 0;
}
