#pragma once
#include <string.h>
#include <stdlib.h>
#include <math.h>

double stringToDouble(char *string) {
    int floatingPointIndex = -1;
    double result = 0;
    int stringSize = strlen(string);
    for (int i = 0; i < stringSize; i++)
    {
        // Se não for dígito e não for vírgula ou ponto retorna -1
        if ((string[i] != 44 && string[i] != 46) && (string[i] < 48 || string[i] > 57))
        {
            return -1;
        }
        if (string[i] == ',' || string[i] == '.') {  // Se vírgula ou ponto retorna índice do mesmo
            floatingPointIndex = i;
        }
    }
    // Se o valor continua -1, não há vírgula ou ponto no valor, então é um valor inteiro
    if (floatingPointIndex == -1) 
    {
        return atoi(string);
    }

    // Para cada dígito expoente para 10 que deve ser usado na multiplicação desse dígito por potência de 10
    for (int i = 0; i < stringSize; i++)
    {
        if (i != floatingPointIndex) {
            int exponent;
            if (i < floatingPointIndex)
            {
                exponent = floatingPointIndex - i - 1;
            }
            else
            {
                exponent = floatingPointIndex - i;
            }
            int currentDigit = string[i] - 48;  // Conversão do dí­gito atual de string para int

            // Soma ao valor final a multiplicação do dí­gito pela potência de 10 adequada
            result += currentDigit * pow(10, exponent);
        }
    }
    return result;
}

int fractionalPartSize(double number) {  // Calcula tamanho da parte fracionária de um valor de ponto flutuante
    int fractionalDigitsAmount;
    for (fractionalDigitsAmount = 0; number != (int)number; fractionalDigitsAmount++) 
    {
        number *= 10;
    }
    return fractionalDigitsAmount;
}

int digitsAmount(double number) {
    char numberAsString[50];
    sprintf(numberAsString, "%g", number);
    return strlen(numberAsString) - 1;
}