#pragma once
#include <stdio.h>
#include <math.h>
#include "doubletools.h"
#include "linkedlist.h"

typedef struct QuantitativeClass {
    double min;
    double max;
} QuantitativeClass;

double adjustDelta(double delta,  int amountOfClasses) {
    double adjustedDelta = delta;  // Caso não haja necessidade de ajuste
    double nearestMultiplier = delta / amountOfClasses;
    if (nearestMultiplier != (int)nearestMultiplier) {
        if (delta == (int)delta) {  // Se delta é inteiro
            adjustedDelta = amountOfClasses * ((int)nearestMultiplier + 1);  // Ajusta delta para próximo múltiplo maior que valor original
        }
        else {
            int decimalDigitsAmount = fractionalPartSize(delta);
            delta *= pow(10, decimalDigitsAmount);  // Múltiplica valor por potência de 10 de modo a não haver mais parte fracionária
            adjustedDelta = ((int)(delta / 10)) * 10;  // Faz variável com valor de delta com dígito da casa das unidades definido em 0

            // Repete até que adjustedDelta seja divisível pela qtd de classes e adjustedDelta seja no mínimo igual à delta
            while (((int)adjustedDelta % amountOfClasses != 0) || adjustedDelta < delta) {
                adjustedDelta+= amountOfClasses;
            }
            adjustedDelta /= pow(10, decimalDigitsAmount);  // Retorna adjustedDelta à sua unidade de grandeza apropriada
        }
    }
    return adjustedDelta;
}

void printClassesTable (int justifyParam, int classesAmount, int totalAmount ,QuantitativeClass *classArray, int *frequencyArray) {
    printf("\n%-*s   %*s   %*s   %*s   %*s\n", justifyParam ,"Classes", 15, "Freq Abs.", 15, "Freq. relat.", 15, "Freq. Acum.", 15, "Freq. Acum. Relat.");
    printf("--------------------------------------------------------------------------------------------------\n");
    double relativeFreqTotal = 0;
    double absoluteFreqTotal = 0;
    for (int i = 0; i < classesAmount; i++)
    {
        absoluteFreqTotal += frequencyArray[i];
        relativeFreqTotal = relativeFreqTotal + ((double)frequencyArray[i] / totalAmount);
        char classOutput[50];
        sprintf(classOutput,"%g|-%g", classArray[i].min, classArray[i].max);
        printf("%-*s %*d %*.2g %*g %*.2lf\n", justifyParam ,classOutput, 15, frequencyArray[i], 15, (double)(frequencyArray[i]) / totalAmount, 15, absoluteFreqTotal, 15, relativeFreqTotal);
    }
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("%-*s %*d %*.2f\n", justifyParam, "Total", 15, totalAmount, 15, 1.0);
}

void nonGorupedTable(DoubleNode *currentNode) {
    int justifyParam = digitsAmount(listBiggestValue(currentNode)) * 2;
    printf("\n%-*s   %*s   %*s   %*s   %*s\n", justifyParam ,"Classes", 15, "Freq Abs.", 15, "Freq. relat.", 15, "Freq. Acum.", 15, "Freq. Acum. Relat.");
    printf("--------------------------------------------------------------------------------------------------\n");

    int total = listTotalValuesAmount(currentNode);
    int counter = 0;
    DoubleNode *auxNode;
    for (auxNode = currentNode; auxNode != NULL; auxNode = auxNode->next)
    {
        counter += auxNode->amount;
        printf("%*.2lf   %*d   %*.2lf   %*d   %*.2lf\n", justifyParam, auxNode->value, 15 ,auxNode->amount, 15 ,(double)auxNode->amount / total, 15 ,counter, 15 ,(double)counter / total);
    }

    printf("--------------------------------------------------------------------------------------------------\n");
    printf("%-*s %*d %*.2f\n", justifyParam, "Total", 15, total, 15, 1.0);
}

double groupedSampleAverage(QuantitativeClass *classes, int *frequencies, int amountOfValues, int amountOfClasses) {
    double sum = 0;
    for (int i = 0; i < amountOfClasses; i++)
    {
        double classAvg = (classes[i].min + classes[i].max) / 2.0;
        sum = sum + (classAvg * frequencies[i]);
    }
    return sum / amountOfValues;
}