#include "medmail.h"


void afficherMenu(char *mdp)
{
  system("clear");
  int choix;
  char *tmp_ptr_mdp = mdp;
  do
  {
     printf("%s███╗   ███╗███████╗██████╗ ███╗   ███╗ █████╗ ██╗██╗\n████╗ ████║██╔════╝██╔══██╗████╗ ████║██╔══██╗██║██║\n██╔████╔██║█████╗  ██║  ██║██╔████╔██║███████║██║██║\n██║╚██╔╝██║██╔══╝  ██║  ██║██║╚██╔╝██║██╔══██║██║██║\n██║ ╚═╝ ██║███████╗██████╔╝██║ ╚═╝ ██║██║  ██║██║███████╗\n╚═╝     ╚═╝╚══════╝╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚══════╝\n                                                         ", VERT);
     printf("%s \nBienvenue dans le repondeur mail!\n\n", BLANC);
     printf("1) Envoyer un mail.\n");
     printf("2) Passer à l'interface administrateur.\n");
     printf("3) Fermer l'application.\n\n");
     printf("Veuillez choisir une option parmis celles proposées dans le menu ci-dessus : ");
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
       printf("%s███╗   ███╗███████╗██████╗ ███╗   ███╗ █████╗ ██╗██╗\n████╗ ████║██╔════╝██╔══██╗████╗ ████║██╔══██╗██║██║\n██╔████╔██║█████╗  ██║  ██║██╔████╔██║███████║██║██║\n██║╚██╔╝██║██╔══╝  ██║  ██║██║╚██╔╝██║██╔══██║██║██║\n██║ ╚═╝ ██║███████╗██████╔╝██║ ╚═╝ ██║██║  ██║██║███████╗\n╚═╝     ╚═╝╚══════╝╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚══════╝\n                                                         ", VERT);
       printf("%s \nBienvenue dans le repondeur mail (Menu Administrateur)!\n\n", BLANC);
       printf("1) Saisir nouvelles coordonnées.\n");
       printf("2) Lister les coordonnées.\n");
       printf("3) Rechercher une coordonnée.\n");
       printf("4) Supprimer une coordonnée.\n");
       printf("5) Saisir un mot clé et sa réponse associée.\n");
       printf("6) Lister les mot clés et leur réponse associée.\n");
       printf("7) Rechercher un mot clé et sa réponse associée.\n");
       printf("8) Supprimer un mot clé et sa réponse associée.\n");
       printf("9) Se deconnecter.\n\n");
       printf("Veuillez choisir une option parmis celles proposées dans le menu ci-dessus : ");
       scanf(" %d",&choix);

       switch (choix)
       {
           case 1: saisirCoordonnes(); afficherMenuAdmin(tmp_ptr_mdp);
                break;
           case 2: listerCoordonnees(); afficherMenuAdmin(tmp_ptr_mdp);
                break;
           case 3: rechercherCoordonnees(); afficherMenuAdmin(tmp_ptr_mdp);
               break;
           case 4: supprimerCoordonnee(); afficherMenuAdmin(tmp_ptr_mdp);
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

int getLastIdCoord()
{
  int lastId = 0;
  FILE *sourceBdd;
  sourceBdd = fopen("coordonnees.dat", "r");
  if (sourceBdd == NULL)
  {
    fprintf(stderr, "\nImpossible ouvrir la base de données!\n");
    exit(0);
  }

  coordonnees coord_temp;

  while(fread(&coord_temp, sizeof(coordonnees), 1, sourceBdd))
  {
    lastId = coord_temp.id;
  }

  return lastId + 1;
}

void saisirCoordonnes()
{
  int last_id = getLastIdCoord();
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
    scanf("%s", coord_temp.prenom);

    printf("\nVeuillez saisir le nom : ");
    scanf("%s", coord_temp.nom);

    printf("\nVeuillez saisir l'adresse : ");
    scanf("%s", coord_temp.adresse);

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
     printf("3) Rechercher par adresse mail.\n");
     printf("4) Rechercher par priorité.\n");
     printf("5) Returner au menu principal.\n\n");
     printf("Veuillez choisir u parametre de recherche parmis ceux proposés ci-dessus : ");
     scanf(" %d",&choix);

     switch (choix)
     {
         case 1: lancerRechercherCoordonnees(1); system("clear");
              break;
         case 2: lancerRechercherCoordonnees(2); system("clear");
              break;
         case 3: lancerRechercherCoordonnees(3); system("clear");
             break;
         case 4: lancerRechercherCoordonnees(4); system("clear");
             break;
         case 5: exit = true;
             break;
         default: system("clear");
             break;
     }
  } while (choix != 5);
}

void lancerRechercherCoordonnees(int type)
{
  system("clear");
  char nom[MAX_CHAR_SIZE];
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
    printf("Veuillez rentrer le nom : ");
    scanf("%s", nom);
  }
  else if (type == 2)
  {
    printf("Veuillez rentrer le prenom : ");
    scanf("%s", nom);
  }
  else if (type == 3)
  {
    printf("Veuillez rentrer l'adresse : ");
    scanf("%s", nom);
  }
  else
  {
    do
    {
      printf("Veuillez rentrer le niveau d'importance (1 ou 0) : ");
      scanf("%s", nom);
    } while (strcmp(nom, "1") != 0 && strcmp(nom, "0") != 0);
  }

  while(fread(&coord_temp, sizeof(coordonnees), 1, sourceBdd))
  {
    if (type == 1)
    {
      if (strcmp(nom, coord_temp.nom) == 0)
      {
        printf("\nPrénom : %s \nNom : %s \nAdresse mail: %s \nPriorite : %d\n", coord_temp.prenom, coord_temp.nom, coord_temp.adresse, coord_temp.importance);
        printf("\n---------------------\n");
        compteur++;
      }
    }
    else if (type == 2)
    {
      if (strcmp(nom, coord_temp.prenom) == 0)
      {
        printf("\nPrénom : %s \nNom : %s \nAdresse mail: %s \nPriorite : %d\n", coord_temp.prenom, coord_temp.nom, coord_temp.adresse, coord_temp.importance);
        printf("\n---------------------\n");
        compteur++;
      }
    }
    else if (type == 3)
    {
      if (strcmp(nom, coord_temp.adresse) == 0)
      {
        printf("\nPrénom : %s \nNom : %s \nAdresse mail: %s \nPriorite : %d\n", coord_temp.prenom, coord_temp.nom, coord_temp.adresse, coord_temp.importance);
        printf("\n---------------------\n");
        compteur++;
      }
    }
    else
    {
      if (atoi(nom) == coord_temp.importance)
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
  int id;
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

      printf("\nVeuillez rentrer l'id de la coordonnée à supprimer : ");
      scanf(" %d", &id);

      while(fread(&coord_temp, sizeof(coordonnees), 1, sourceBdd))
      {
        if(id == coord_temp.id)
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
          if(id != coord_temp.id)
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
        printf("\nL'id que vous avez rentré n'hexiste pas dans la base de donées des coordonnées!");

        do
        {
          printf("\nVoulez-vous réessayer avec un autre id? (o/n) ");
          scanf(" %c", &choix);
        } while (choix != 'o' && choix != 'n');
      }
    } while(choix != 'n');
  }
}
