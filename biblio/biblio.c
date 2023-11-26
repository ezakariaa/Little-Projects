#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_MEMBERS 50

// Structure pour représenter un livre
struct Book {
    int bookId;
    char title[100];
    char author[50];
    int isAvailable; // 1 si disponible, 0 sinon
};

// Structure pour représenter un membre de la bibliothèque
struct Member {
    int memberId;
    char name[50];
};

// Fonction pour ajouter un livre à la bibliothèque
void addBook(struct Book library[], int *numBooks) {
    if (*numBooks < MAX_BOOKS) {
        struct Book newBook;
        newBook.bookId = *numBooks + 1;

        printf("Titre du livre : ");
        fflush(stdin);
        fgets(newBook.title, sizeof(newBook.title), stdin);
        newBook.title[strcspn(newBook.title, "\n")] = '\0';

        printf("Auteur du livre : ");
        fflush(stdin);
        fgets(newBook.author, sizeof(newBook.author), stdin);
        newBook.author[strcspn(newBook.author, "\n")] = '\0';

        newBook.isAvailable = 1;

        library[*numBooks] = newBook;
        (*numBooks)++;
        printf("Livre ajouté avec succès.\n");
    } else {
        printf("La bibliothèque est pleine, impossible d'ajouter plus de livres.\n");
    }
}

// Fonction pour afficher la liste des livres disponibles
void displayAvailableBooks(struct Book library[], int numBooks) {
    printf("Livres disponibles :\n");
    for (int i = 0; i < numBooks; i++) {
        if (library[i].isAvailable) {
            printf("%d. %s par %s\n", library[i].bookId, library[i].title, library[i].author);
        }
    }
}

// Fonction pour emprunter un livre
void borrowBook(struct Book library[], int numBooks) {
    int bookId;
    displayAvailableBooks(library, numBooks);
    printf("Entrez l'ID du livre que vous souhaitez emprunter : ");
    scanf("%d", &bookId);

    if (bookId > 0 && bookId <= numBooks && library[bookId - 1].isAvailable) {
        library[bookId - 1].isAvailable = 0;
        printf("Vous avez emprunté le livre : %s\n", library[bookId - 1].title);
    } else {
        printf("Livre non disponible ou ID invalide.\n");
    }
}

// Fonction pour retourner un livre
void returnBook(struct Book library[], int numBooks) {
    int bookId;
    printf("Entrez l'ID du livre que vous souhaitez retourner : ");
    scanf("%d", &bookId);

    if (bookId > 0 && bookId <= numBooks && !library[bookId - 1].isAvailable) {
        library[bookId - 1].isAvailable = 1;
        printf("Vous avez retourné le livre : %s\n", library[bookId - 1].title);
    } else {
        printf("Livre non emprunté ou ID invalide.\n");
    }
}

// Fonction pour supprimer un livre de la bibliothèque
void deleteBook(struct Book library[], int *numBooks) {
    int bookId;
    printf("Entrez l'ID du livre que vous souhaitez supprimer : ");
    scanf("%d", &bookId);

    if (bookId > 0 && bookId <= *numBooks) {
        for (int i = bookId - 1; i < *numBooks - 1; i++) {
            library[i] = library[i + 1];
        }
        (*numBooks)--;
        printf("Livre supprimé avec succès.\n");
    } else {
        printf("ID invalide.\n");
    }
}

// Fonction pour enregistrer les livres dans un fichier texte
void saveToTextFile(struct Book library[], int numBooks) {
    FILE *file = fopen("bibliotheque.txt", "w");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fprintf(file, "ID\tTitre\tAuteur\n");

    for (int i = 0; i < numBooks; i++) {
        fprintf(file, "%d\t%s\t%s\n", library[i].bookId, library[i].title, library[i].author);
    }

    fclose(file);
    printf("Livres enregistrés dans bibliotheque.txt\n");
}

int main() {
    struct Book library[MAX_BOOKS];
    int numBooks = 0;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Ajouter un livre\n");
        printf("2. Afficher les livres disponibles\n");
        printf("3. Emprunter un livre\n");
        printf("4. Retourner un livre\n");
        printf("5. Supprimer un livre\n");
        printf("6. Enregistrer dans un fichier texte\n");
        printf("7. Quitter\n");

        int choice;
        printf("Votre choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(library, &numBooks);
                break;
            case 2:
                displayAvailableBooks(library, numBooks);
                break;
            case 3:
                borrowBook(library, numBooks);
                break;
            case 4:
                returnBook(library, numBooks);
                break;
            case 5:
                deleteBook(library, &numBooks);
                break;
            case 6:
                saveToTextFile(library, numBooks);
                break;
            case 7:
                printf("Au revoir !\n");
                return 0;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    }

    return 0;
}
