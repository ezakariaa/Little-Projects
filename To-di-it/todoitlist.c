#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TACHES 100
#define MAX_TAILLE_TACHE 100

void afficher_taches(char *taches[], int nb_taches) {
    if (nb_taches == 0) {
        printf("Aucune tâche enregistrée.\n");
    } else {
        printf("Liste des tâches:\n");
        for (int i = 0; i < nb_taches; i++) {
            printf("%d. %s\n", i + 1, taches[i]);
        }
    }
}

void ajouter_tache(char *taches[], int *nb_taches, char nouvelle_tache[]) {
    if (*nb_taches < MAX_TACHES) {
        taches[*nb_taches] = strdup(nouvelle_tache);
        (*nb_taches)++;
        printf("Tâche ajoutée : %s\n", nouvelle_tache);
    } else {
        printf("Limite maximale de tâches atteinte.\n");
    }
}

void supprimer_tache(char *taches[], int *nb_taches, int numero_tache) {
    if (numero_tache >= 1 && numero_tache <= *nb_taches) {
        printf("Tâche supprimée : %s\n", taches[numero_tache - 1]);
        free(taches[numero_tache - 1]);
        for (int i = numero_tache - 1; i < *nb_taches - 1; i++) {
            taches[i] = taches[i + 1];
        }
        (*nb_taches)--;
    } else {
        printf("Numéro de tâche invalide.\n");
    }
}

void sauvegarder_taches(char *taches[], int nb_taches) {
    FILE *fichier = fopen("taches.txt", "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nb_taches; i++) {
        fprintf(fichier, "%s\n", taches[i]);
    }

    fclose(fichier);
}

void charger_taches(char *taches[], int *nb_taches) {
    FILE *fichier = fopen("taches.txt", "r");
    if (fichier == NULL) {
        return; // Aucun fichier trouvé, aucune tâche chargée.
    }

    char ligne[MAX_TAILLE_TACHE];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        ligne[strcspn(ligne, "\n")] = '\0'; // Supprime le caractère de nouvelle ligne
        taches[*nb_taches] = strdup(ligne);
        (*nb_taches)++;
    }

    fclose(fichier);
}

int main() {
    char *taches[MAX_TACHES];
    int nb_taches = 0;

    charger_taches(taches, &nb_taches);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Afficher les tâches\n");
        printf("2. Ajouter une tâche\n");
        printf("3. Supprimer une tâche\n");
        printf("4. Quitter\n");

        int choix;
        printf("Entrez le numéro de votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficher_taches(taches, nb_taches);
                break;
            case 2:
                if (nb_taches < MAX_TACHES) {
                    char nouvelle_tache[MAX_TAILLE_TACHE];
                    printf("Entrez la nouvelle tâche : ");
                    getchar(); // Pour absorber le caractère de nouvelle ligne restant dans le buffer
                    fgets(nouvelle_tache, sizeof(nouvelle_tache), stdin);
                    nouvelle_tache[strcspn(nouvelle_tache, "\n")] = '\0'; // Supprime le caractère de nouvelle ligne
                    ajouter_tache(taches, &nb_taches, nouvelle_tache);
                    sauvegarder_taches(taches, nb_taches);
                } else {
                    printf("Limite maximale de tâches atteinte.\n");
                }
                break;
            case 3:
                if (nb_taches > 0) {
                    int numero_tache;
                    printf("Entrez le numéro de la tâche à supprimer : ");
                    scanf("%d", &numero_tache);
                    supprimer_tache(taches, &nb_taches, numero_tache);
                    sauvegarder_taches(taches, nb_taches);
                } else {
                    printf("Aucune tâche à supprimer.\n");
                }
                break;
            case 4:
                printf("Merci d'utiliser le gestionnaire de tâches. Au revoir!\n");
                return 0;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    }

    return 0;
}
