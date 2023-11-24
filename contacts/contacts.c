#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char nom[50];
    char prenom[50];
    char numero[20];
};

void ajouterContact(struct Contact *annuaire, int *taille) {
    printf("Entrez le nom du contact : ");
    scanf("%s", annuaire[*taille].nom);

    printf("Entrez le prénom du contact : ");
    scanf("%s", annuaire[*taille].prenom);

    printf("Entrez le numéro de téléphone du contact : ");
    scanf("%s", annuaire[*taille].numero);

    (*taille)++;
}

void afficherContacts(struct Contact *annuaire, int taille) {
    printf("\nListe des contacts :\n");
    for (int i = 0; i < taille; ++i) {
        printf("Nom : %s\n", annuaire[i].nom);
        printf("Prénom : %s\n", annuaire[i].prenom);
        printf("Numéro de téléphone : %s\n", annuaire[i].numero);
        printf("-------------------------\n");
    }
}

void sauvegarderContacts(struct Contact *annuaire, int taille, const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    for (int i = 0; i < taille; ++i) {
        fprintf(fichier, "%s %s %s\n", annuaire[i].nom, annuaire[i].prenom, annuaire[i].numero);
    }

    fclose(fichier);
}

void chargerContacts(struct Contact *annuaire, int *taille, const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Aucun fichier trouvé. Création d'un nouvel annuaire.\n");
        return;
    }

    while (fscanf(fichier, "%s %s %s", annuaire[*taille].nom, annuaire[*taille].prenom, annuaire[*taille].numero) == 3) {
        (*taille)++;
    }

    fclose(fichier);
}

void supprimerContact(struct Contact *annuaire, int *taille) {
    char nomSupprimer[50];
    int position = -1;

    printf("Entrez le nom du contact à supprimer : ");
    scanf("%s", nomSupprimer);

    // Recherche de la position du contact dans l'annuaire
    for (int i = 0; i < *taille; ++i) {
        if (strcmp(annuaire[i].nom, nomSupprimer) == 0) {
            position = i;
            break;
        }
    }

    // Suppression du contact s'il a été trouvé
    if (position != -1) {
        for (int i = position; i < *taille - 1; ++i) {
            annuaire[i] = annuaire[i + 1];
        }
        (*taille)--;
        printf("Le contact a été supprimé avec succès.\n");
    } else {
        printf("Le contact n'a pas été trouvé.\n");
    }
}

int main() {
    struct Contact annuaire[100];
    int taille = 0;
    int choix;

    chargerContacts(annuaire, &taille, "contacts.txt");

    do {
        printf("\nGestionnaire de contacts\n");
        printf("1. Ajouter un contact\n");
        printf("2. Afficher tous les contacts\n");
        printf("3. Supprimer un contact\n");
        printf("4. Sauvegarder les contacts\n");
        printf("5. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterContact(annuaire, &taille);
                break;
            case 2:
                afficherContacts(annuaire, taille);
                break;
            case 3:
                supprimerContact(annuaire, &taille);
                break;
            case 4:
                sauvegarderContacts(annuaire, taille, "contacts.txt");
                printf("Les contacts ont été sauvegardés dans 'contacts.txt'.\n");
                break;
            case 5:
                printf("Au revoir !\n");
                break;
            default:
                printf("Option invalide. Veuillez réessayer.\n");
        }
    } while (choix != 5);

    return 0;
}
