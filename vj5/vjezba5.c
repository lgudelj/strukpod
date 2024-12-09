#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


typedef struct Node {
    double value;
    struct Node* next;
} Node;

Node* push(Node* top, double value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Greška: Nedovoljno memorije.\n");
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->next = top;
    return newNode;
}

Node* pop(Node* top, double* value) {
    if (!top) {
        fprintf(stderr, "Greška: Prazan stog.\n");
        exit(EXIT_FAILURE);
    }
    Node* temp = top;
    *value = temp->value;
    top = top->next;
    free(temp);
    return top;
}


int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

double calculate(double a, double b, char operator) {
    switch (operator) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                fprintf(stderr, "Greška: Dijeljenje s nulom.\n");
                exit(EXIT_FAILURE);
            }
            return a / b;
        default:
            fprintf(stderr, "Greška: Nepoznat operator '%c'.\n", operator);
            exit(EXIT_FAILURE);
    }
}

int main() {
    FILE* file = fopen("postfix.txt", "r");
    if (!file) {
        fprintf(stderr, "Greška: Ne mogu otvoriti datoteku.\n");
        return 1;
    }

    char buffer[256];
    Node* stack = NULL;

    while (fscanf(file, "%s", buffer) != EOF) {
        if (isdigit(buffer[0]) || (buffer[0] == '-' && isdigit(buffer[1]))) {
            stack = push(stack, atof(buffer));
        } else if (isOperator(buffer[0]) && strlen(buffer) == 1) {
            double b, a;
            stack = pop(stack, &b);
            stack = pop(stack, &a);
            double result = calculate(a, b, buffer[0]);
            stack = push(stack, result);
        } else {
            fprintf(stderr, "Greška: Nepoznat element '%s'.\n", buffer);
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    double result;
    stack = pop(stack, &result);

    if (stack) {
        fprintf(stderr, "Greška: Višak elemenata na stogu.\n");
        return 1;
    }

    printf("Rezultat: %.2f\n", result);
    return 0;
}
