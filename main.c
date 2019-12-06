#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CHAR_SIZE 500

typedef struct{
  char prenom[MAX_CHAR_SIZE];
  char nom[MAX_CHAR_SIZE];
  char adresse[MAX_CHAR_SIZE];
  int importance;
} coordonnees;

typedef struct{
  coordonnees c;
  char obj[MAX_CHAR_SIZE];
  char corps[MAX_CHAR_SIZE];
} email;

//Menu
void afficherMenu(char*);
void afficherMenuAdmin(char*);

//Fonctions utilisateur de base
void envoyerMail();
void loginAdmin(char*);

//Fonctions administrateur
void saisirCoordonnes();
void listerCoordonnees();
void rechercherCoordonnees();
void rechercherParNom();
void rechercherParPrenom();
void rechercherParAdresse();
void rechercherParPriorite();


int main(){
  char mdpAdmin[MAX_CHAR_SIZE] = "n";
  char *ptr_mdpAdmin;
  ptr_mdpAdmin = mdpAdmin;
  afficherMenu(ptr_mdpAdmin);
  return 0;
}

void afficherMenu(char *mdp)
{
  system("clear");
  int choix;
  char *tmp_ptr_mdp = mdp;
  do
  {
     printf("\nBienvenu dans le repondeur mail!\n\n");
     printf("1) Envoyer un mail.\n");
     printf("2) Passer à l'interface aministrateur.\n");
     printf("3) Fermer l'application.\n\n");
     printf("Veuillez choisir une option parmis celle proposée dans le menu ci-dessus : ");
     scanf(" %d",&choix);

     switch (choix)
     {
         case 1: envoyerMail();
              break;
         case 2: loginAdmin(tmp_ptr_mdp);
              break;
         case 3: printf("Au revoir!\n");
             exit(0);
             break;
         default: system("clear");
             break;
     }
  } while (choix != 3);
}

void envoyerMail()
{

}

void loginAdmin(char *mdp)
{
  char inputMdp[MAX_CHAR_SIZE];
  char choix;
  char *tmp_ptr_mdp = mdp;
  do
  {
      system("clear");
      printf("\nVeuillez rentrer le mot de passe pour vous identifier à l'interface d'administration : ");
      scanf("%s", inputMdp);
      if(strcmp(inputMdp, mdp) == 0)
      {
        printf("\nMot de passe correct! Vous allez être redirigé vers le menu administrateur. \n");
        system("clear");
        afficherMenuAdmin(tmp_ptr_mdp);
      }
      else
      {
        bool exit_intern_loop = false;
        do {
          if (exit_intern_loop)
          {
            break;
          }
          printf("\nMot de passe incorrect! Voulez-vous réessayer? (o/n) ");
          scanf(" %c", &choix);
          switch (choix) {
            case 'o': exit_intern_loop = true; break;
            case 'n': afficherMenu(tmp_ptr_mdp); break;
            default : printf("Veuillez répondre avec 'o' (oui) ou 'n' (non)."); system("clear"); break;
          }
        } while(choix != 'o' || choix != 'n');
      }
  } while (strcmp(inputMdp, mdp) != 0);
}

void afficherMenuAdmin(char *mdp)
{
    system("clear");
    int choix;
    char *tmp_ptr_mdp = mdp;
    do
    {
       printf("\nBienvenu dans le repondeur mail (Menu Administrateur)!\n\n");
       printf("1) Saisir nouvelles coordonnées.\n");
       printf("2) Lister les coordonnées.\n");
       printf("3) Rechercher une coordonnée.\n");
       printf("4) Supprimer une coordonnée.\n");
       printf("5) Saisir un mot clé et sa réponse associée.\n");
       printf("6) Lister les mot clés et leur réponse associée.\n");
       printf("7) Rechercher un mot clé et sa réponse associée.\n");
       printf("8) Supprimer un mot clé et sa réponse associée.\n");
       printf("9) Se deconnecter.\n\n");
       printf("Veuillez choisir une option parmis celle proposée dans le menu ci-dessus : ");
       scanf(" %d",&choix);

       switch (choix)
       {
           case 1: saisirCoordonnes(); afficherMenuAdmin(tmp_ptr_mdp);
                break;
           case 2: listerCoordonnees(); afficherMenuAdmin(tmp_ptr_mdp);
                break;
           case 3: rechercherCoordonnees(); afficherMenuAdmin(tmp_ptr_mdp);
               break;
           case 4: printf("4");
               break;
           case 5: printf("5");
                break;
           case 6: printf("6");
                break;
           case 7: printf("7");
               break;
           case 8: printf("8");
               break;
           case 9: system("clear"); afficherMenu(tmp_ptr_mdp);
               break;
           default: system("clear");
               break;
       }
    } while (choix != 9);
}

void saisirCoordonnes()
{
  FILE *sourceBdd;
  sourceBdd = fopen("coordonnees.dat", "a");
  if (sourceBdd == NULL)
  {
      fprintf(stderr, "\nImpossible ouvrir la base de données!\n");
      exit(1);
  }
  char choix;
  do
  {
    system("clear");
    if (choix == 'n')
    {
      break;
    }

    coordonnees coord_temp;

    printf("Veuillez saisir le prénom : ");
    scanf("%s", coord_temp.prenom);

    printf("Veuillez saisir le nom : ");
    scanf("%s", coord_temp.nom);

    printf("Veuillez saisir l'adresse : ");
    scanf("%s", coord_temp.adresse);

    printf("Veuillez saisir l'importance du client (0 ou 1) : ");
    scanf("%d", &(coord_temp.importance));

    fwrite (&coord_temp, sizeof(coordonnees), 1, sourceBdd);

    do
    {
      printf("\nVoulez-vous ajouter une nouvelle coordonnee? (o/n) ");
      scanf(" %c", &choix);
    } while (choix != 'o' && choix != 'n');

  } while (choix != 'n');
  fclose(sourceBdd);
}

void listerCoordonnees()
{
  system("clear");
  int compteur = 0;
  char key;
  FILE *sourceBdd;
  sourceBdd = fopen("coordonnees.dat", "r");
  if (sourceBdd == NULL)
  {
    fprintf(stderr, "\nImpossible ouvrir la base de données!\n");
    exit(0);
  }

  coordonnees coord_temp;

  printf("\n---------------------\n");
  printf("Coordonnées : ");
  printf("\n---------------------\n");

  while(fread(&coord_temp, sizeof(coordonnees), 1, sourceBdd))
  {
    printf("\nPrénom : %s \nNom : %s \nAdresse mail: %s \nPriorite : %d\n", coord_temp.prenom, coord_temp.nom, coord_temp.adresse, coord_temp.importance);
    printf("\n---------------------\n");
    compteur++;
  }

  printf("Coordonnées trouvées en total : %d.", compteur);
  printf("\n---------------------\n\n");

  fclose(sourceBdd);

  printf("Cliquer sur une touche pour revenir au menu. ");
  scanf(" %c", &key);
}

void rechercherCoordonnees()
{
  system("clear");
  int choix;
  bool exit = false;
  do
  {

    if (exit)
    {
      break;
    }

     printf("1) Rechercher par nom.\n");
     printf("2) Recherche par prenom.\n");
     printf("3) Rechercher par adresse mail.\n\n");
     printf("4) Rechercher par priorité.\n\n");
     printf("5) Returner au menu principal.\n\n");
     printf("Veuillez choisir u parametre de recherche parmis ceux proposés ci-dessus : ");
     scanf(" %d",&choix);

     switch (choix)
     {
         case 1: rechercherParNom();
              break;
         case 2: rechercherParPrenom();
              break;
         case 3: rechercherParAdresse();
             break;
         case 4: rechercherParPriorite();
             break;
         case 5: exit = true;
             break;
         default: system("clear");
             break;
     }
  } while (choix != 5);
}

void rechercherParNom(){}
void rechercherParPrenom(){}
void rechercherParAdresse(){}
void rechercherParPriorite(){}
