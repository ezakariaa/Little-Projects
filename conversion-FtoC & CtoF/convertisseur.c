#include <stdio.h>

// Fonction pour convertir de Celsius à Fahrenheit
float celsiusToFahrenheit(float celsius) {
    return (celsius * 9/5) + 32;
}

// Fonction pour convertir de Fahrenheit à Celsius
float fahrenheitToCelsius(float fahrenheit) {
    return (fahrenheit - 32) * 5/9;
}

int main() {
    int choix;
    float valeur;

    printf("Choisissez l'option de conversion :\n");
    printf("1. Celsius vers Fahrenheit\n");
    printf("2. Fahrenheit vers Celsius\n");
    scanf("%d", &choix);

    printf("Entrez la valeur à convertir : ");
    scanf("%f", &valeur);

    switch (choix) {
        case 1:
            printf("%.2f Celsius équivaut à %.2f Fahrenheit\n", valeur, celsiusToFahrenheit(valeur));
            break;
        case 2:
            printf("%.2f Fahrenheit équivaut à %.2f Celsius\n", valeur, fahrenheitToCelsius(valeur));
            break;
        default:
            printf("Option non valide\n");
            break;
    }

    return 0;
}
