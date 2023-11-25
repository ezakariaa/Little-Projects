#include <stdio.h>
#include <ctype.h>

// Fonction pour compter le nombre de mots dans le texte
int compterMots(char texte[]) {
    int mots = 0;
    int estDansMot = 0; // 0 si à l'extérieur d'un mot, 1 si à l'intérieur

    for (int i = 0; texte[i] != '\0'; i++) {
        if (texte[i] == ' ' || texte[i] == '\n' || texte[i] == '\t') {
            estDansMot = 0;
        } else if (estDansMot == 0) {
            estDansMot = 1;
            mots++;
        }
    }

    return mots;
}

// Fonction pour compter le nombre de phrases dans le texte
int compterPhrases(char texte[]) {
    int phrases = 0;

    for (int i = 0; texte[i] != '\0'; i++) {
        if (texte[i] == '.' || texte[i] == '!' || texte[i] == '?') {
            phrases++;
        }
    }

    return phrases;
}

// Fonction pour compter le nombre de voyelles et de consonnes dans le texte
void compterVoyellesConsonnes(char texte[], int *voyelles, int *consonnes) {
    for (int i = 0; texte[i] != '\0'; i++) {
        char c = tolower(texte[i]); // Convertir en minuscule pour simplifier la vérification

        if (c >= 'a' && c <= 'z') {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                (*voyelles)++;
            } else {
                (*consonnes)++;
            }
        }
    }
}

int main() {
    char texte[1000];

    printf("Entrez le texte à analyser :\n");
    fgets(texte, sizeof(texte), stdin);

    // Initialiser les compteurs
    int mots = compterMots(texte);
    int phrases = compterPhrases(texte);
    int voyelles = 0, consonnes = 0;
    compterVoyellesConsonnes(texte, &voyelles, &consonnes);

    printf("\nStatistiques du texte :\n");
    printf("Nombre de mots : %d\n", mots);
    printf("Nombre de phrases : %d\n", phrases);
    printf("Nombre de voyelles : %d\n", voyelles);
    printf("Nombre de consonnes : %d\n", consonnes);

    return 0;
}
