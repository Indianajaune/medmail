#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CHAR_SIZE 500

#define NOIR  "\x1B[0m"
#define ROUGE  "\x1B[31m"
#define VERT  "\x1B[32m"
#define JAUNE  "\x1B[33m"
#define BLEU  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define BLANC  "\x1B[37m"

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
  char reponse[MAX_CHAR_SIZE];
} motcles;

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
void lancerRechercherCoordonnees(int);
void supprimerCoordonnee();
void saisirMotCle();
void listerMotCle();
void rechercherMotsCle();
void supprimerMotCle();


int getLastId(char*);
void removeNl(char*);
bool checkIfDigit(char*);
