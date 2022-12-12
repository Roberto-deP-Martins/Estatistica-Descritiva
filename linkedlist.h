#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>

typedef struct DoubleNode {
    double value;
    int amount;
    struct DoubleNode *next;
} DoubleNode;

typedef struct StringNode {
    char string[1024];
    int amount;
    struct StringNode *next;
} StringNode;

// Funções para serem usadas com Doubles
DoubleNode* startDoubleList() {
    return NULL;
}

DoubleNode* doubleListInsert (DoubleNode* lst, double val) {
    DoubleNode* node;
    short int foundDouble = 0;
    for (node = lst; node != NULL; node = node->next)
    {
        if (node->value == val) {
            node->amount += 1;
            foundDouble = 1;
            return lst;
        }
    }
    if (!foundDouble) {
        DoubleNode* newNode = (DoubleNode*) malloc(sizeof(DoubleNode));
        newNode->value = val;
        newNode->amount = 1;
        newNode->next = lst;
        return newNode;
    }
}

void freeDoubleList (DoubleNode* lst) {
    DoubleNode* currentNode = lst; DoubleNode* nextNode;
    while (currentNode != NULL) {
        nextNode = currentNode->next; /* guarda referência para prox elemento */
        free(currentNode); /* libera a memória apontada por p */
        currentNode = nextNode; /* faz p apontar para o próximo */
    }
}

DoubleNode* doubleSearch (DoubleNode* lst, double searchedValue) { 
    DoubleNode* node;
    for (node=lst; node!=NULL; node = node->next) {
        if (node->value == searchedValue)
        return node;
    }
    return NULL; /* não achou o elemento */
}

double listBiggestValue (DoubleNode* lst) {
    DoubleNode* node;
    double biggestValue = lst->value;
    for (node=lst->next; node!=NULL; node = node->next) {
        if (node->value > biggestValue)
            biggestValue = node->value;
    }
    return biggestValue;
}

double listMinValue(DoubleNode* lst) {
    DoubleNode *node;
    double minValue = lst->value;
    for (node=lst->next; node!=NULL; node = node->next) {
        if (node->value < minValue)
            minValue = node->value;
    } 
    return minValue;
}

int listTotalValuesAmount (DoubleNode* lst) {  // Obtém total de valores inseridos na lista
    int total = 0;
    DoubleNode* node;
    for (node=lst; node!=NULL; node = node->next) {
        total += node->amount;
    }
    return total;
}

double avg(DoubleNode* lst) {
    DoubleNode *node;
    double sum = 0;
    for (node=lst; node!=NULL; node = node->next) {
        sum += (node->value * node->amount);
    }
    return sum / listTotalValuesAmount(lst);
}

double var(DoubleNode *lst) {
    double average = avg(lst);
    double sum = 0;
    DoubleNode *node;
    for (node = lst; node != NULL; node = node->next) {
        sum = sum + (((node->value - average) * (node->value - average)) * node->amount);
    }
    return sum / listTotalValuesAmount(lst);
}

double stdDeviation(DoubleNode *lst) {
    return pow(var(lst), 0.5);
}

void printDoubleList (DoubleNode* lst) {
    DoubleNode* currentNode;
    for (currentNode = lst; currentNode != NULL; currentNode = currentNode->next) {
        printf("info = %g\n", currentNode->value);
    }
}


// Funções para ser usadas para strings
StringNode* startStringList() {
    return NULL;
}

StringNode* stringListInsert (StringNode* lst, char *string) {
    StringNode* node;
    short int foudString = 0;
    for (node=lst; node!=NULL; node = node->next) {
        if (strcmp(node->string, string) == 0) {
            node->amount += 1;
            foudString = 1;
            return lst;
        }
    }
    if (!foudString) {
        StringNode* newNode = (StringNode*) malloc(sizeof(StringNode));
        strcpy(newNode->string, string);
        newNode->amount = 1;
        newNode->next = lst;
        return newNode;
    }
}

void freeStringList (StringNode* lst) {
    StringNode* currentNode = lst; StringNode* nextNode;
    while (currentNode != NULL) {
        nextNode = currentNode->next; /* guarda referência p/ prox. elemento */
        free(currentNode); /* libera a memória apontada por p */
        currentNode = nextNode; /* faz p apontar para o próximo */
    }
}

StringNode* stringSearch (StringNode* lst, char *searchedString) { 
    StringNode* node;
    for (node=lst; node!=NULL; node = node->next) {
        if (strcmp(node->string, searchedString) == 0)
        return node;
    }
    return NULL; /* não achou o elemento */
}

void printStringList (StringNode* lst) {
    StringNode* currentNode;
    setlocale(LC_ALL, "Portuguese");
    for (currentNode = lst; currentNode != NULL; currentNode = currentNode->next) {
        printf("info = %s qtd = %d\n", currentNode->string, currentNode->amount);
    }
}