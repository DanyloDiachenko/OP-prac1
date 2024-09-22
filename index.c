#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define MIN_VALID_ARABIC_NUMBER 1
#define MAX_VALID_ARABIC_NUMBER 3999

void validateInputNumber(int number);
int transformArabicToRoman(int numberToTransform, int arabicNumber, char romanNumber);
void clearInputBuffer();
char getch();

int main() {
    printf("\n%s\n", "Welcome to the Arabic and Roman numbers transformer app.");

    while (1) {
        int number = 0;

        printf("Enter Number to transform (from %d to %d): ", MIN_VALID_ARABIC_NUMBER, MAX_VALID_ARABIC_NUMBER);
        scanf("%d", &number);

        validateInputNumber(number);

        number = transformArabicToRoman(number, 1000, 'M');
        number = transformArabicToRoman(number, 500, 'D');
        number = transformArabicToRoman(number, 100, 'C');
        number = transformArabicToRoman(number, 50, 'L');
        number = transformArabicToRoman(number, 10, 'X');
        number = transformArabicToRoman(number, 5, 'V');
        number = transformArabicToRoman(number, 1, 'I');

        clearInputBuffer();

        printf("\nPress any key to continue, or enter 0 to stop...\n");
        char inputChar = getch();
        if (inputChar == '0') {
            printf("\nYou entered 0. Exiting...\n");

            break;
        }
    }

    return 0;
}

void validateInputNumber(const int number) {
    if (number > MAX_VALID_ARABIC_NUMBER || number < MIN_VALID_ARABIC_NUMBER) {
        char validityMessage[100];
        sprintf(validityMessage, "Input number must be greater than or equal to %d and less than or equal to %d.", MIN_VALID_ARABIC_NUMBER, MAX_VALID_ARABIC_NUMBER);
        printf("%s\n", validityMessage);
        exit(EXIT_FAILURE);
    }
}

int transformArabicToRoman(int numberToTransform, const int arabicNumber, const char romanNumber) {
    while (numberToTransform >= arabicNumber) {
        putchar(romanNumber);
        numberToTransform -= arabicNumber;
    }
    return numberToTransform;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

char getch() {
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
