#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CHAR_SIZE 100
#define MAX_CHAR_BODY 1000

typedef struct{
  int id;
  char prenom[MAX_CHAR_SIZE];
  char nom[MAX_CHAR_SIZE];
  char adresse[MAX_CHAR_SIZE];
  int importance;
} coordonnees;

typedef struct{
  int id;
  char mot[MAX_CHAR_SIZE];
  char reponse[MAX_CHAR_BODY];
} motcles;

typedef struct{
  coordonnees c;
  char obj[MAX_CHAR_SIZE];
  char corps[MAX_CHAR_BODY];
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
void lancerRechercherCoordonnees(int);
void supprimerCoordonnee();
void saisirMotCle();
void listerMotCle();
void rechercherMotsCle();
void supprimerMotCle();


int getLastId(char*);
void removeNl(char*);
bool checkIfDigit(char*);

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
  char choix[MAX_CHAR_SIZE] = "";
  char *tmp_ptr_mdp = mdp;
  do
  {

    if(checkIfDigit(choix) == false)
    {
      system("clear");
      printf("\nVous devez uniquement rentrer des chiffres entre 1 et 3 pour effectuer votre choix.\n");
    }

     printf("\nBienvenu dans le repondeur mail!\n\n");
     printf("1) Envoyer un mail.\n");
     printf("2) Passer à l'interface aministrateur.\n");
     printf("\n0) Fermer l'application.\n\n\n");
     printf("Veuillez choisir une option parmis celles proposées dans le menu ci-dessus : ");
     scanf("%s", choix);

     if(checkIfDigit(choix) == false)
     {
       continue;
     }

     switch (atoi(choix))
     {
         case 1: envoyerMail();
              break;
         case 2: loginAdmin(tmp_ptr_mdp);
              break;
         case 0: printf("Au revoir!\n");
             exit(0);
             break;
         default: system("clear");
             break;
     }
  } while (atoi(choix) != 0);
}

void envoyerMail()
{

}

void loginAdmin(char *mdp)
{
  char inputMdp[MAX_CHAR_SIZE] = "";
  char choix;
  char *tmp_ptr_mdp = mdp;
  do
  {
      system("clear");
      printf("\nVeuillez entrer le mot de passe pour vous identifier à l'interface d'administration : ");
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
    char choix[MAX_CHAR_SIZE] = "";
    char *tmp_ptr_mdp = mdp;
    do
    {

      if(checkIfDigit(choix) == false)
      {
        system("clear");
        printf("\nVous devez uniquement entrer des chiffres entre 1 et 9 pour effectuer votre choix.\n");
      }

       printf("\nBienvenu dans le repondeur mail (Menu Administrateur)!\n\n");
       printf("1) Saisir nouvelles coordonnées.\n");
       printf("2) Lister les coordonnées.\n");
       printf("3) Rechercher une coordonnée.\n");
       printf("4) Supprimer une coordonnée.\n");
       printf("5) Saisir un mot clé et sa réponse associée.\n");
       printf("6) Lister les mot clés et leur réponse associée.\n");
       printf("7) Rechercher un mot clé et sa réponse associée.\n");
       printf("8) Supprimer un mot clé et sa réponse associée.\n");
       printf("\n0) Se deconnecter.\n\n\n");
       printf("Veuillez choisir une option parmis celles proposées dans le menu ci-dessus : ");
       scanf(" %s",choix);

       if(checkIfDigit(choix) == false)
       {
         continue;
       }

       switch (atoi(choix))
       {
           case 1: saisirCoordonnes(); afficherMenuAdmin(tmp_ptr_mdp);
                break;
           case 2: listerCoordonnees(); afficherMenuAdmin(tmp_ptr_mdp);
                break;
           case 3: rechercherCoordonnees(); afficherMenuAdmin(tmp_ptr_mdp);
               break;
           case 4: supprimerCoordonnee(); afficherMenuAdmin(tmp_ptr_mdp);
               break;
           case 5: saisirMotCle(); afficherMenuAdmin(tmp_ptr_mdp);
                break;
           case 6: listerMotCle(); afficherMenuAdmin(tmp_ptr_mdp);
                break;
           case 7: rechercherMotsCle(); afficherMenuAdmin(tmp_ptr_mdp);
               break;
           case 8: supprimerMotCle(); afficherMenuAdmin(tmp_ptr_mdp);
               break;
           case 0: system("clear"); afficherMenu(tmp_ptr_mdp);
               break;
           default: system("clear");
               break;
       }
    } while (atoi(choix) != 0);
}

int getLastId(char *fichier)
{
  int lastId = 0;
  FILE *sourceBdd;
  char *file_path = fichier;
  sourceBdd = fopen(file_path, "r");
  if (sourceBdd == NULL)
  {
    return lastId + 1;
  }

  if (strcmp("coordonnees.dat", file_path) == 0)
  {
    coordonnees coord_temp;

    while(fread(&coord_temp, sizeof(coordonnees), 1, sourceBdd))
    {
      lastId = coord_temp.id;
    }
  }
  else
  {
    motcles motCle;

    while(fread(&motCle, sizeof(motcles), 1, sourceBdd))
    {
      lastId = motCle.id;
    }
  }

  return lastId + 1;
}

void removeNl(char *text)
{
  size_t len = strlen(text);
  if (len > 0 && text[len - 1] == '\n')
    text[len - 1] = '\0';
}

bool checkIfDigit(char *input)
{
  bool isDigit = true;
  for (int i=0; i <strlen(input); i++) {
    if (!((int)input[i] >= 47 && (int)input[i] <= 57))
    {
      isDigit = false;
    }
  }
  return isDigit;
}

void saisirCoordonnes()
{
  int last_id = getLastId("coordonnees.dat");
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

    coord_temp.id = last_id;

    printf("\nVeuillez saisir le prénom : ");
    getchar();
    fgets(coord_temp.prenom, sizeof(coord_temp.prenom), stdin);
    removeNl(coord_temp.prenom);

    printf("\nVeuillez saisir le nom : ");
    fgets(coord_temp.nom, sizeof(coord_temp.nom), stdin);
    removeNl(coord_temp.nom);

    printf("\nVeuillez saisir l'adresse : ");
    fgets(coord_temp.adresse, sizeof(coord_temp.adresse), stdin);
    removeNl(coord_temp.adresse);

    printf("\nVeuillez saisir l'importance du client (0 ou 1) : ");
    scanf("%d", &(coord_temp.importance));

    fwrite (&coord_temp, sizeof(coordonnees), 1, sourceBdd);

    do
    {
      printf("\nVoulez-vous ajouter une nouvelle coordonnee? (o/n) ");
      scanf(" %c", &choix);
    } while (choix != 'o' && choix != 'n');

    if (choix == 'o')
    {
      last_id++;
    }

  } while (choix != 'n');
  fclose(sourceBdd);
}

void listerCoordonnees()
{
  system("clear");
  int compteur = 0;
  char choix;
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
    printf("\nId : %d \nPrénom : %s \nNom : %s \nAdresse mail: %s \nPriorite : %d\n", coord_temp.id, coord_temp.prenom, coord_temp.nom, coord_temp.adresse, coord_temp.importance);
    printf("\n---------------------\n");
    compteur++;
  }

  printf("Coordonnées trouvées en total : %d.", compteur);
  printf("\n---------------------\n\n");

  fclose(sourceBdd);

  printf("Cliquer sur la touche 'e' pour revenir au menu principal. ");
  do
  {
    scanf(" %c", &choix);
  } while (choix != 'e');
}

void rechercherCoordonnees()
{
  system("clear");
  char choix[MAX_CHAR_SIZE] = "";
  bool exit = false;
  do
  {

    if (exit)
    {
      break;
    }

    if(checkIfDigit(choix) == false)
    {
      system("clear");
      printf("\nVous devez uniquement rentrer des chiffres entre 1 et 5 pour effectuer votre choix.\n");
    }

     printf("\n1) Rechercher par nom.\n");
     printf("2) Recherche par prenom.\n");
     printf("3) Rechercher par adresse mail.\n");
     printf("4) Rechercher par priorité.\n");
     printf("\n0) Returner au menu administrateur.\n\n\n");
     printf("Veuillez choisir un parametre de recherche parmis ceux proposés ci-dessus : ");
     scanf(" %s", choix);

     if(checkIfDigit(choix) == false)
     {
       continue;
     }

     switch (atoi(choix))
     {
         case 1: lancerRechercherCoordonnees(1); system("clear");
              break;
         case 2: lancerRechercherCoordonnees(2); system("clear");
              break;
         case 3: lancerRechercherCoordonnees(3); system("clear");
             break;
         case 4: lancerRechercherCoordonnees(4); system("clear");
             break;
         case 0: exit = true;
             break;
         default: system("clear");
             break;
     }
  } while (atoi(choix) != 0);
}

void lancerRechercherCoordonnees(int type)
{
  system("clear");
  char query[MAX_CHAR_SIZE] = "";
  char choix;
  int compteur = 0;
  FILE *sourceBdd;
  sourceBdd = fopen("coordonnees.dat", "r");
  if (sourceBdd == NULL)
  {
    fprintf(stderr, "\nImpossible ouvrir la base de données!\n");
    exit(0);
  }

  coordonnees coord_temp;

  if (type == 1)
  {
    printf("\nVeuillez entrer le nom : ");
    getchar();
    fgets(query, sizeof(query), stdin);
    removeNl(query);
  }
  else if (type == 2)
  {
    printf("\nVeuillez entrer le prenom : ");
    getchar();
    fgets(query, sizeof(query), stdin);
    removeNl(query);
  }
  else if (type == 3)
  {
    printf("\nVeuillez entrer l'adresse : ");
    getchar();
    fgets(query, sizeof(query), stdin);
    removeNl(query);
  }
  else
  {
    do
    {
      printf("\nVeuillez entrer le niveau d'importance (1 ou 0) : ");
      scanf("%s", query);
    } while (strcmp(query, "1") != 0 && strcmp(query, "0") != 0);
  }

  while(fread(&coord_temp, sizeof(coordonnees), 1, sourceBdd))
  {
    if (type == 1)
    {
      if (strcmp(query, coord_temp.nom) == 0)
      {
        printf("\nPrénom : %s \nNom : %s \nAdresse mail: %s \nPriorite : %d\n", coord_temp.prenom, coord_temp.nom, coord_temp.adresse, coord_temp.importance);
        printf("\n---------------------\n");
        compteur++;
      }
    }
    else if (type == 2)
    {
      if (strcmp(query, coord_temp.prenom) == 0)
      {
        printf("\nPrénom : %s \nNom : %s \nAdresse mail: %s \nPriorite : %d\n", coord_temp.prenom, coord_temp.nom, coord_temp.adresse, coord_temp.importance);
        printf("\n---------------------\n");
        compteur++;
      }
    }
    else if (type == 3)
    {
      if (strcmp(query, coord_temp.adresse) == 0)
      {
        printf("\nPrénom : %s \nNom : %s \nAdresse mail: %s \nPriorite : %d\n", coord_temp.prenom, coord_temp.nom, coord_temp.adresse, coord_temp.importance);
        printf("\n---------------------\n");
        compteur++;
      }
    }
    else
    {
      if (atoi(query) == coord_temp.importance)
      {
        printf("\nPrénom : %s \nNom : %s \nAdresse mail: %s \nPriorite : %d\n", coord_temp.prenom, coord_temp.nom, coord_temp.adresse, coord_temp.importance);
        printf("\n---------------------\n");
        compteur++;
      }
    }

  }

  if(compteur > 0)
  {
    printf("Coordonnées trouvées en total : %d.", compteur);
    printf("\n---------------------\n\n");
  }
  else
  {
    printf("\n---------------------\n");
    printf("Aucune coordonnée trouvée avec ce critere de recherche.");
    printf("\n---------------------\n\n");
  }

  fclose(sourceBdd);

  printf("Cliquer sur la touche 'e' pour revenir au menu de recherche. ");
  do
  {
    scanf(" %c", &choix);
  } while (choix != 'e');
}


void supprimerCoordonnee()
{
  system("clear");
  char id[MAX_CHAR_SIZE] = "";
  bool found = false;
  char choix;

  coordonnees coord_temp;

  FILE *tmp_sourceBdd, *sourceBdd;
  tmp_sourceBdd = fopen("temp_coordonnees.dat", "a");
  sourceBdd = fopen("coordonnees.dat", "r");
  if (tmp_sourceBdd == NULL && sourceBdd == NULL)
  {
    fprintf(stderr, "\nImpossible ouvrir la base de données temporaire (suppression coordonnee)!\n");
    exit(0);
  }
  else
  {
    do
    {
      system("clear");
      if (choix == 'n')
      {
        break;
      }

      if(checkIfDigit(id) == false)
      {
        printf("\nL'id que vous avez rentré n'est pas valide! Un id est compose uniquement de chiffres.\n");
      }

      printf("\nVeuillez rentrer l'id de la coordonnée à supprimer : ");
      scanf(" %s", id);

      if(checkIfDigit(id) == false)
      {
        continue;
      }

      while(fread(&coord_temp, sizeof(coordonnees), 1, sourceBdd))
      {
        if(atoi(id) == coord_temp.id)
        {
          found = true;
        }
      }

      fclose(sourceBdd);
      sourceBdd = fopen("coordonnees.dat", "r");

      if(found == true)
      {
        while(fread(&coord_temp, sizeof(coordonnees), 1, sourceBdd))
        {
          if(atoi(id) != coord_temp.id)
          {
            fwrite(&coord_temp, sizeof(coordonnees), 1, tmp_sourceBdd);
          }
        }
        fclose(sourceBdd);
        remove("coordonnees.dat");
        fclose(tmp_sourceBdd);
        rename("temp_coordonnees.dat", "coordonnees.dat");

        do
        {
          printf("\nSupprimée avec succès! Voulez-vous supprimer une autre coordonnee? (o/n) ");
          scanf(" %c", &choix);
        } while (choix != 'o' && choix != 'n');
      }
      else
      {
        printf("\nL'id que vous avez rentré n'existe pas dans la base de donées des coordonnées!");

        do
        {
          printf("\nVoulez-vous réessayer avec un autre id? (o/n) ");
          scanf(" %c", &choix);
        } while (choix != 'o' && choix != 'n');
      }
    } while(choix != 'n');
  }
}

void saisirMotCle()
{
  int last_id = getLastId("motcles.dat");
  FILE *sourceBdd;
  sourceBdd = fopen("motcles.dat", "a");
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

    motcles motCle;

    motCle.id = last_id;

    printf("\nVeuillez saisir le mot clé : ");
    getchar();
    fgets(motCle.mot, sizeof(motCle.mot), stdin);
    removeNl(motCle.mot);

    printf("\nVeuillez saisir la reponse : ");
    fgets(motCle.reponse, sizeof(motCle.reponse), stdin);
    removeNl(motCle.reponse);

    fwrite (&motCle, sizeof(motcles), 1, sourceBdd);

    do
    {
      printf("\nVoulez-vous ajouter un nouveau mot clé? (o/n) ");
      scanf(" %c", &choix);
    } while (choix != 'o' && choix != 'n');

    if (choix == 'o')
    {
      last_id++;
    }

  } while (choix != 'n');
  fclose(sourceBdd);
}

void listerMotCle()
{
  system("clear");
  int compteur = 0;
  char choix;
  FILE *sourceBdd;
  sourceBdd = fopen("motcles.dat", "r");
  if (sourceBdd == NULL)
  {
    fprintf(stderr, "\nImpossible ouvrir la base de données!\n");
    exit(0);
  }

  motcles motCle;

  printf("\n---------------------\n");
  printf("Mots clé : ");
  printf("\n---------------------\n");

  while(fread(&motCle, sizeof(motCle), 1, sourceBdd))
  {
    printf("\nId : %d \nMot clé : %s \nReponse : %s \n", motCle.id, motCle.mot, motCle.reponse);
    printf("\n---------------------\n");
    compteur++;
  }

  printf("Mots clé trouvés en total : %d.", compteur);
  printf("\n---------------------\n\n");

  fclose(sourceBdd);

  printf("Cliquer sur la touche 'e' pour revenir au menu principal. ");
  do
  {
    scanf(" %c", &choix);
  } while (choix != 'e');
}

void rechercherMotsCle()
{
  system("clear");
  char query[MAX_CHAR_SIZE] = "";
  char choix;
  int compteur = 0;
  FILE *sourceBdd;
  sourceBdd = fopen("motcles.dat", "r");
  if (sourceBdd == NULL)
  {
    fprintf(stderr, "\nImpossible ouvrir la base de données!\n");
    exit(0);
  }

  motcles motCle;

  printf("\nVeuillez rentrer le mot clé ou reponse à rechercher : ");
  getchar();
  fgets(query, sizeof(query), stdin);
  removeNl(query);

  while(fread(&motCle, sizeof(motcles), 1, sourceBdd))
  {
      if (strcmp(query, motCle.mot) == 0 || strcmp(query, motCle.reponse) == 0)
      {
        printf("\nId : %d \nMot clé : %s \nReponse : %s \n", motCle.id, motCle.mot, motCle.reponse);
        printf("\n---------------------\n");
        compteur++;
      }
    }

  if(compteur > 0)
  {
    printf("Mots clé trouvés en total : %d.", compteur);
    printf("\n---------------------\n\n");
  }
  else
  {
    printf("\n---------------------\n");
    printf("Aucun mot clé trouvé avec ce critere de recherche.");
    printf("\n---------------------\n\n");
  }

  fclose(sourceBdd);

  printf("Cliquer sur la touche 'e' pour revenir au menu de recherche. ");
  do
  {
    scanf(" %c", &choix);
  } while (choix != 'e');
}

void supprimerMotCle()
{
  system("clear");
  char id[MAX_CHAR_SIZE] = "";
  bool found = false;
  char choix;

  motcles motCle;

  FILE *tmp_sourceBdd, *sourceBdd;
  tmp_sourceBdd = fopen("temp_motcles.dat", "a");
  sourceBdd = fopen("motcles.dat", "r");
  if (tmp_sourceBdd == NULL && sourceBdd == NULL)
  {
    fprintf(stderr, "\nImpossible d'ouvrir la base de données temporaire (suppression coordonnee)!\n");
    exit(0);
  }
  else
  {
    do
    {
      system("clear");
      if (choix == 'n')
      {
        break;
      }

      if(checkIfDigit(id) == false)
      {
        printf("\nL'id que vous avez rentré n'est pas valide! Un id est compose uniquement de chiffres.\n");
      }

      printf("\nVeuillez rentrer l'id du mot clé à supprimer : ");
      scanf(" %s", id);

      if(checkIfDigit(id) == false)
      {
        continue;
      }

      while(fread(&motCle, sizeof(motcles), 1, sourceBdd))
      {
        if(atoi(id) == motCle.id)
        {
          found = true;
        }
      }

      fclose(sourceBdd);
      sourceBdd = fopen("motcles.dat", "r");

      if(found == true)
      {
        while(fread(&motCle, sizeof(motcles), 1, sourceBdd))
        {
          if(atoi(id) != motCle.id)
          {
            fwrite(&motCle, sizeof(motcles), 1, tmp_sourceBdd);
          }
        }
        fclose(sourceBdd);
        remove("motcles.dat");
        fclose(tmp_sourceBdd);
        rename("temp_motcles.dat", "motcles.dat");

        do
        {
          printf("\nSupprimé avec succès! Voulez-vous supprimer un autre mot clé? (o/n) ");
          scanf(" %c", &choix);
        } while (choix != 'o' && choix != 'n');
      }
      else
      {
        printf("\nL'id que vous avez rentré n'existe pas dans la base de donées des coordonnées!");

        do
        {
          printf("\nVoulez-vous réessayer avec un autre id? (o/n) ");
          scanf(" %c", &choix);
        } while (choix != 'o' && choix != 'n');
      }
    } while(choix != 'n');
  }
}
