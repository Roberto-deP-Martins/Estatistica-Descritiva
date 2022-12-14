/* ABRIR EM ISO 8859-1 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>
#include "doubletools.h"
#include "linkedlist.h"
#include "descriptivestatistics.h"

void input(char *string);
void mallocErrorHandler();
char *strsplit(char *string, short int *startIdx);

int main() {
    
    setlocale(LC_ALL, "Portuguese");
    short int isQualitative;
    do
    {
        printf("Digite uma das opções:\n1 - Dados quantitativos.     2 - Dados qualitativos.\n");
        scanf(" %hd", &isQualitative);
        fflush(stdin);
    } while (isQualitative != 1 && isQualitative != 2);
    isQualitative--;

    short int isGrouped = 0;
    if (!isQualitative)
    {
        do
        {
            printf("Os dados são não-agrupados ou agrupados?\n 1 - Dados não agrupados.     2 - Dados agrupados.\n");
            scanf(" %hd", &isGrouped);
            fflush(stdin);
            isGrouped--;
        } while (isGrouped != 0 && isGrouped != 1);
    }
    if (isGrouped)
    {
        double maxValue, minValue;
        printf("Digite valor máximo e mínimo: ");
        scanf("%lf %lf", &maxValue, &minValue);
        
        int classesAmount;
        printf("Digite o número de classes: ");
        scanf(" %d", &classesAmount);
        
        double delta = maxValue - minValue;
        printf("Delta original: %g\n", delta);
        delta = adjustDelta(delta, classesAmount);
        printf("Delta ajustado: %g\n", delta);
        
        double classLength = delta / classesAmount;
        printf("h = %g\n", classLength);

        QuantitativeClass *classes;
        classes = (QuantitativeClass *)malloc(classesAmount * sizeof(QuantitativeClass));
        if (classes == NULL)
            mallocErrorHandler();
        printf("Classes: [");
        for (int i = 0; i < classesAmount; i++)
        {
            printf("[");
            QuantitativeClass classRange;
            classRange.min = minValue;
            minValue += classLength;
            classRange.max = minValue;
            classes[i] = classRange;
            printf("%g, %g] ", classes[i].min, classes[i].max);
        }
        printf("]\n");
        
        printf("Pontos médios: ");
        for (int i = 0; i < classesAmount; i++)
        {
            double averageValue = (classes[i].max + classes[i].min) / 2;
            if (i < classesAmount - 1)
                printf("%g   ", averageValue);
            else
                printf("%g\n", averageValue);
        }

        int *frequencies;
        frequencies = (int *)malloc(classesAmount * sizeof(int));
        if (frequencies == NULL)
            mallocErrorHandler();

        for (int i = 0; i < classesAmount; i++)
            frequencies[i] = 0;

        int valuesTotalAmount = 0;
        char valuesInput[1024];
        do
        {
            input(valuesInput);
            char *token = strtok(valuesInput, " ");  // Pega primeiro item anterior a espaço
            while (token != NULL)
            {
                double floatValue = stringToDouble(token);  // Converte substring pra float
                for (int i = 0; i < classesAmount; i++)
                {
                    // Verifica a qual intervalo (identificado por i) pertence o valor
                    if (floatValue >= classes[i].min && floatValue < classes[i].max)
                    {
                        frequencies[i] += 1;  // Soma à posição i da array de frequências, incrementando quantos valores estão nesse intervalo
                        valuesTotalAmount++;
                    }
                }
                token = strtok(NULL, " ");  // Lê próximo valor separado por espaço na string
            }
        } while (strcmp(valuesInput, "") != 0);
        

        int classJustifyParam = (digitsAmount(classes[classesAmount - 1].min) + digitsAmount(classes[classesAmount - 1].max) + 2) * 2;
        printClassesTable(classJustifyParam, classesAmount, valuesTotalAmount, classes, frequencies);
        printf("\nMédia: %g\n", groupedSampleAverage(classes, frequencies, valuesTotalAmount, classesAmount));
        
        free(frequencies);
        free(classes);
    }
    else  // Não é agrupado
    {
        int totalAmount = 0;
        short int biggestValueSize = 0;
        if (isQualitative)
        {
            char valuesInput[1024];
            StringNode *newestNode;
            newestNode = startStringList();
            do
            {
                input(valuesInput);
                char substring[1024];
                short int startPosition = 0;
                while (startPosition != -1) {  // Função de split torna startPosition -1 quando se alcança fim da string
                    strcpy(substring, strsplit(valuesInput, &startPosition));
                    if (strcmp(substring, "") != 0) {  // Se usuário tiver digitado algo
                        newestNode = stringListInsert(newestNode, substring);
                        totalAmount++;

                        // Atualiza tamanho da maior string que vai à lista encadeada
                        short int substringLen = strlen(substring);
                        if (substringLen > biggestValueSize)
                        {
                            biggestValueSize = substringLen;
                        }
                    }
                }
            } while (strcmp(valuesInput, "") != 0);  // Repete até digitar string vazia
            printStringList(newestNode);
            freeStringList(newestNode);
        }
        else  // Não-agrupado E quantitativo
        {
            DoubleNode *newestNode;
            newestNode = startDoubleList();
            char valuesInput[1024];
            do
            {
                input(valuesInput);
                char substring[1024];
                short int startPosition = 0;
                while (startPosition != -1) {  // Função de split torna startPosition -1 quando se alcança fim da string
                    strcpy(substring, strsplit(valuesInput, &startPosition));
                    if (strcmp(substring, "") != 0) {  // Se usuário tiver digitado algo
                        double stringAsDouble = stringToDouble(substring);
                        newestNode = doubleListInsert(newestNode, stringAsDouble);
                        totalAmount++;

                        // Atualiza qtd de dígitos com o maior que já foi inserido
                        short int valueDigitsAmount = digitsAmount(stringAsDouble);
                        if (valueDigitsAmount > biggestValueSize)
                            biggestValueSize = valueDigitsAmount;
                    }
                }
            } while (strcmp(valuesInput, "") != 0);  // Repete até digitar string vazia
            nonGorupedTable(newestNode);
            double average = avg(newestNode);
            printf("\nMédia: %g\n", average);
            printf("Moda: %g\n", mode(newestNode));
            double max = listBiggestValue(newestNode);
            double min = listMinValue(newestNode);
            printf("Mínimo: %.2lf\n", min);
            printf("Máximo: %.2lf\n", max);
            printf("Amplitude: %.2lf\n", max - min);
            double variance = var(newestNode);
            printf("Variância: %g\n", variance);
            double stdDeviation = pow(variance, 0.5);
            printf("Desvio-padrão: %g\n", stdDeviation);
            printf("Coeficiente de variação: %g\n", stdDeviation / average);
            freeDoubleList(newestNode);
        }
    }
    
    system("pause");
    return 0;
}

void input(char *string) {
    fflush(stdin);
    printf("Digite os valores, separados por espaços caso múltiplos, ou pressione Enter para encerrar inserção de valores: ");
    fgets(string, 1023, stdin);  // Lê string do usuário
    string[strcspn(string, "\n")] = 0;  // Retira \n da string
}

void mallocErrorHandler() {
    printf("Memória insuficiente.\n");
    system("pause");
    exit(1);
}

char *strsplit(char *string, short int *startIdx) {
    static char result[1024];
    short int idx = 0;
    for (; string[*startIdx] != '\0' && string[*startIdx] != ' '; *startIdx += 1)
    {
        result[idx] = string[*startIdx];
        idx++;
    }
    if (string[*startIdx + 1] == '\0') {
        *startIdx = -1;
    }
    else {
        *startIdx += 1;
    }
    result[idx] = '\0';   
    return result;
}