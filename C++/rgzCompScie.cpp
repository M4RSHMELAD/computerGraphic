#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Преобразование целого числа в двоичное представление
void convertIntToBinary(int num, char* binStr) {
    for (int i = 0; i < 32; i++) {
        binStr[31 - i] = (num & (1 << i)) ? '1' : '0';
    }
    binStr[32] = '\0'; // Завершаем строку символом конца строки
}

// Преобразование дробной части в двоичное представление
void convertFractionToBinary(float fractionalPart, char* binStr, int maxBits) {
    int count = 0;
    while (fractionalPart != 0.0 && count < maxBits) {
        fractionalPart *= 2;
        if (fractionalPart >= 1.0) {
            binStr[count++] = '1';
            fractionalPart -= 1.0;
        } else {
            binStr[count++] = '0';
        }
    }
    binStr[count] = '\0'; // Завершаем строку символом конца строки
}

// Преобразование числа с плавающей точкой в двоичное представление
void convertFloatToBinary(float num, char* binStr) {
    union {
        float floatVal;
        unsigned int intVal;
    } floatToInt;
    floatToInt.floatVal = num;
    convertIntToBinary(floatToInt.intVal, binStr);
}

// Выделение целой и дробной части
void separateIntegerAndFraction(float num, int* integerPart, float* fractionalPart) {
    *integerPart = (int)num;  // Целая часть
    *fractionalPart = num - *integerPart;  // Дробная часть
}

// Преобразование дробной части в десятичную систему путем умножения на 10
float convertFractionToDecimal(float fractionalPart) {
    float result = 0.0;
    int count = 0;

    // Умножаем дробную часть на 10, несколько раз, чтобы получить десятичный результат
    while (fractionalPart != 0.0 && count < 10) { // Ограничение на количество шагов
        fractionalPart *= 10;
        int digit = (int)fractionalPart;  // Получаем целую часть после умножения
        result = result * 10 + digit;    // Строим десятичную часть
        fractionalPart -= digit;         // Оставляем только дробную часть для следующего шага
        count++;
    }

    return result;
}

// Вывод в формате "sign / characteristic / mantissa"
void correctConclusion(char* binStr) {
    printf("sign / characteristic / mantissa\n");
    printf("%c      ", binStr[0]);
    for (int i = 1; i <= 8; i++) {
        printf("%c", binStr[i]);
    }
    printf("         ");
    for (int i = 9; i < 32; i++) {
        printf("%c", binStr[i]);
    }
    printf("\n");
}

// Основная функция
int main() {
    char binaryRepresentation[33]; // Для IEEE 754 представления числа
    char intBinary[33];            // Для двоичного представления целой части
    char fractionBinary[65];       // Для двоичного представления дробной части (до 64 бит)
    int choiceInput;
    int integerInput;
    float floatInput;

    printf("Select format of the entered number:\n1 - int\n2 - float\nEnter selection:\n");
    scanf("%d", &choiceInput);

    if (choiceInput == 1) {
        printf("Enter an integer: ");
        scanf("%d", &integerInput);
        convertIntToBinary(integerInput, binaryRepresentation);
        printf("Binary representation (int): %s\n", binaryRepresentation);
    }
    else if (choiceInput == 2) {
        printf("Enter a float: ");
        scanf("%f", &floatInput);

        // Выделяем целую и дробную части
        int integerPart;
        float fractionalPart;
        separateIntegerAndFraction(floatInput, &integerPart, &fractionalPart);

        // Преобразуем число в IEEE 754
        convertFloatToBinary(floatInput, binaryRepresentation);
        correctConclusion(binaryRepresentation);

        // Преобразуем целую часть в двоичный формат
        convertIntToBinary(integerPart, intBinary);
        printf("Binary representation of integer part: %s\n", intBinary);

        // Преобразуем дробную часть в двоичный формат
        convertFractionToBinary(fractionalPart, fractionBinary, 20); // Ограничиваем до 20 бит
        printf("Binary representation of fractional part: %s\n", fractionBinary);

        // Преобразуем дробную часть в десятичный формат
        float decimalFraction = convertFractionToDecimal(fractionalPart);
        printf("Decimal representation of fractional part: %.10f\n", decimalFraction);
    }
    else {
        printf("Invalid value entered\n");
    }

    return 0;
}
