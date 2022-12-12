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
        // Se n�o for d�gito e n�o for v�rgula ou ponto retorna -1
        if ((string[i] != 44 && string[i] != 46) && (string[i] < 48 || string[i] > 57))
        {
            return -1;
        }
        if (string[i] == ',' || string[i] == '.') {  // Se v�rgula ou ponto retorna �ndice do mesmo
            floatingPointIndex = i;
        }
    }
    // Se o valor continua -1, n�o h� v�rgula ou ponto no valor, ent�o � um valor inteiro
    if (floatingPointIndex == -1) 
    {
        return atoi(string);
    }

    // Para cada d�gito expoente para 10 que deve ser usado na multiplica��o desse d�gito por pot�ncia de 10
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
            int currentDigit = string[i] - 48;  // Convers�o do d�gito atual de string para int

            // Soma ao valor final a multiplica��o do d�gito pela pot�ncia de 10 adequada
            result += currentDigit * pow(10, exponent);
        }
    }
    return result;
}

int fractionalPartSize(double number) {  // Calcula tamanho da parte fracion�ria de um valor de ponto flutuante
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