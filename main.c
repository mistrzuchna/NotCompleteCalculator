#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <math.h>
#include <stdbool.h>


//---------------------------------------------------prototypy----------------------------------------------------------

void ONPInput(char onpPhrase[]);

struct stack *push(struct stack *top, char data[]);

void pop(struct stack **top, char *result);

char *peek(struct stack *top);

void ONPCalculations(char *onpPhrase, struct stack *top);

int menu();

void algebraicExpressionInput(char *algebraicExpression);

void algebraicToONP(char *algebraicExpression, struct stack *top);

char ONPFromAlgebraic[50] = "";

//----------------------------------------------------------------------------------------------------------------------

struct stack {
    char *data;
    struct stack *next;
};



int main() {
    struct stack *top = NULL;
    int methodChoice = menu();
    if (methodChoice == 1) {
        char ONP[40] = "";
        ONPInput(ONP);
        ONPCalculations(ONP, top);
    }

    if (methodChoice == 2) {
        char algebraic[50] = "";
        algebraicExpressionInput(algebraic);
        algebraicToONP(algebraic, top);

        ONPCalculations(ONPFromAlgebraic, top);

    }
    return 0;
}


//---------------------------------------------------obsługa ONP--------------------------------------------------------


void ONPInput(char *onpPhrase) {
    printf("Wprowadz wyrazenie w Odwrotnej Notacji Polskiej.\nOddzielaj poczszegolne liczby i operatory spacjami.\nZakoncz zankiem rownosci");
    puts("");
    puts("");
    scanf(" %[^\n]s", onpPhrase);            // razem ze spacjami
    printf("Twoje wyrazenie: %s\n\n", onpPhrase);
}

void ONPCalculations(char *onpPhrase, struct stack *top) {
    char *token;
    char s[] = " ";

    token = strtok(onpPhrase, s);
    char *temp = calloc(40, sizeof(char));
    while (token != NULL) {

        if (atof(token) != 0) {
            // jeśli element jest liczbą
            top = push(top, token);
        } else if (*token == '+') {
            // zdejmij 2 elementy ze stosu i dodaj, potem odloz wynik na stos
            char output[40] = "";
            pop(&top, temp);
            double first = atof(temp);
            pop(&top, temp);
            double second = atof(temp);
            double result = first + second;
            snprintf(output, 50, "%f", result);
            top = push(top, output);
        } else if (*token == '-') {
            // zdejmij 2 elementy ze stosu i dodaj, potem odloz wynik na stos
            char output[40] = "";
            pop(&top, temp);
            double first = atof(temp);
            pop(&top, temp);
            double second = atof(temp);
            double result = second - first;
            snprintf(output, 50, "%f", result);
            top = push(top, output);
        } else if (*token == '*') {
            char output[40] = "";
            pop(&top, temp);
            double first = atof(temp);
            pop(&top, temp);
            double second = atof(temp);
            double result = first * second;
            snprintf(output, 50, "%f", result);
            top = push(top, output);
        } else if (*token == '/') {
            char output[40] = "";
            pop(&top, temp);
            double first = atof(temp);
            pop(&top, temp);
            double second = atof(temp);
            double result = second / first;
            snprintf(output, 50, "%f", result);
            top = push(top, output);
        } else if (*token == '^') {
            char output[40] = "";
            pop(&top, temp);
            double first = atof(temp);
            pop(&top, temp);
            double second = atof(temp);
            double result = pow(second, first);
            snprintf(output, 50, "%f", result);
            top = push(top, output);
        }else if (*token == '%') {
            char output[40] = "";
            pop(&top, temp);
            double first = atof(temp);
            pop(&top, temp);
            double second = atof(temp);
            double result = (int)second % (int)first;
            snprintf(output, 50, "%f", result);
            top = push(top, output);
        } else if (*token == '=') {
            if (top->next == NULL)
                printf("Wynik wprowadzonego wyrazenia wynosi: %.2f\n", atof(peek(top)));
            else
                printf("Niepoprawny element w wyrazeniu! Sprawdz poprawnosc wpisanych danych.");
        } else
            printf("Niepoprawny element w wyrazeniu! Sprawdz poprawnosc wpisanych danych.");
        token = strtok(NULL, s);
    }
    //printf("\nWierzcholek stosu: \t%s", peek(top));
}



//-----------------------------------------------------obsługa stosu----------------------------------------------------



struct stack *push(struct stack *top, char *data) {
    struct stack *new_node = (struct stack *)
            malloc(sizeof(struct stack));

    if (NULL != new_node) {
        new_node->data = data;
        new_node->next = top;
        top = new_node;
    }
    return top;
}

void pop(struct stack **top, char *result) {
    if (NULL != *top) {
        strcpy(result, (*top)->data);
        struct stack *tmp = (*top)->next;
        free(*top);
        *top = tmp;
    }
}

char *peek(struct stack *top) {
    if (NULL != top)
        return top->data;

 //   fprintf(stderr, "Stack is empty.\n");
    return NULL;
}

int menu() {
    puts("\t\tMENU");
    puts("\t-----------------");
    puts("Wybierz sposob zapisu wyrazen do kalkulatora.");
    puts("1. -> Postac w Odwrotnej Notacji Polskiej.");
    puts("2. -> Postac algebraiczna.\n");
    int choice = 0;
    scanf("%d", &choice);
    return choice;
}


//-------------------------------------------------obsługa algebraicznego-----------------------------------------------


void algebraicExpressionInput(char *algebraicExpression) {
    printf("Wprowadz wyrazenie w postaci algebraicznej.\nOddzielaj poczszegolne liczby i operatory spacjami.\nZakoncz zankiem rownosci");
    puts("");
    puts("");
    scanf(" %[^\n]s", algebraicExpression);            // razem ze spacjami
    printf("Twoje wyrazenie: %s\n", algebraicExpression);
}

void algebraicToONP(char *algebraicExpression, struct stack *top) {
    //char ONPFromAlgebraic[50] = "";
    //int currentIndex = -1;
    //char space[2] = " ";

    char *temp = calloc(40, sizeof(char));
    char *token;
    char s[] = " ";

    token = strtok(algebraicExpression, s);
   // char *temp = calloc(40, sizeof(char));
    while (token != NULL) {

        if (atof(token) != 0) {
            // jeśli element jest liczbą odłóż na "wyjście" -- dopisz do ONPFromAlgebraic[]
            strcat(ONPFromAlgebraic, token);
            strcat(ONPFromAlgebraic, s);

        } else if (*token == '+') {
            top = push(top, token);
        } else if (*token == '-') {
            top = push(top, token);
        } else if (*token == '*') {
            top = push(top, token);
        } else if (*token == '/') {
            top = push(top, token);
        } else if (*token == '^') {
            top = push(top, token);
        }else if (*token == '%') {
            top = push(top, token);
        } else if (*token == '='){
            do{
                pop(&top, temp);
                strcat(ONPFromAlgebraic, temp);
                strcat(ONPFromAlgebraic, s);
            }while(top != NULL);
            strcat(ONPFromAlgebraic, token);
        }



            token = strtok(NULL, s);
    }

    printf("\nONPFromAlgebraic: %s", ONPFromAlgebraic);
}

bool priorityCheck(char *operator){ //dalej w programie token po prostu
    //jeżeli na topie jest ważniejszy, zdjąć wszystkie
}

//char strcat (char *s, const char *ct) ---- Dopisuje znaki z tablicy znaków ct na koniec tablicy s, zwracane jest s.
