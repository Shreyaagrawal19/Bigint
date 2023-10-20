#include<stdio.h>
#include"parth.h"
struct Node {
    int data;
    struct Node* next;
};
typedef struct Node Node;
    Node* initializeBigInt() {
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    return head;
}

// Function to insert a digit at the end of the linked list
void insertDigit(Node* head, int digit) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = digit;
    newNode->next = NULL;
    
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// Function to print a big integer represented as a linked list
void printBigInt(Node* head) {
    Node* current = head->next; // Skip the leading 0
    while (current != NULL) {
        printf("%d", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to free the memory used by a big integer
void freeBigInt(Node* num) {
    Node* current = num;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

// Function to perform addition of two big integers
Node* addBigInt(Node* num1, Node* num2) {
    Node* result = initializeBigInt();
    Node* current1 = num1->next; // Skip the leading 0
    Node* current2 = num2->next; // Skip the leading 0
    int carry = 0;

    while (current1 != NULL || current2 != NULL) {
        int digit1 = (current1 != NULL) ? current1->data : 0;
        int digit2 = (current2 != NULL) ? current2->data : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        insertDigit(result, sum % 10);

        if (current1 != NULL) {
            current1 = current1->next;
        }
        if (current2 != NULL) {
            current2 = current2->next;
        }
    }

    if (carry > 0) {
        insertDigit(result, carry);
    }

    return result;
}

// Function to perform subtraction of two big integers
Node* subtractBigInt(Node* num1, Node* num2) {
    Node* result = initializeBigInt();
    Node* current1 = num1->next; // Skip the leading 0
    Node* current2 = num2->next; // Skip the leading 0
    int borrow = 0;

    while (current1 != NULL || current2 != NULL) {
        int digit1 = (current1 != NULL) ? current1->data : 0;
        int digit2 = (current2 != NULL) ? current2->data : 0;
        int diff = digit1 - digit2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        insertDigit(result, diff);

        if (current1 != NULL) {
            current1 = current1->next;
        }
        if (current2 != NULL) {
            current2 = current2->next;
        }
    }

    // Remove leading 0's in the result
    while (result->next != NULL && result->next->data == 0) {
        Node* temp = result->next;
        result->next = temp->next;
        free(temp);
    }

    return result;
}

// Function to perform multiplication of two big integers
Node* multiplyBigInt(Node* num1, Node* num2) {
    Node* result = initializeBigInt();
    Node* current2 = num2->next; // Skip the leading 0 of num2
    Node* tempResult, * tempResultTail;
    int shift = 0;

    while (current2 != NULL) {
        int digit2 = current2->data;
        tempResult = initializeBigInt();
        tempResultTail = tempResult;

        for (int i = 0; i < shift; i++) {
            insertDigit(tempResult, 0);
        }

        Node* current1 = num1->next; // Skip the leading 0 of num1
        int carry = 0;

        while (current1 != NULL) {
            int digit1 = current1->data;
            int product = digit1 * digit2 + carry;
            carry = product / 10;
            insertDigit(tempResultTail, product % 10);
            current1 = current1->next;
        }

        if (carry > 0) {
            insertDigit(tempResultTail, carry);
        }

        result = addBigInt(result, tempResult);
        shift++;
        current2 = current2->next;
        freeBigInt(tempResult); // Free temporary result
    }

    return result;
}

// Function to compare two big integers (for subtraction)
int compareBigInt(Node* num1, Node* num2) {
    Node* current1 = num1->next;
    Node* current2 = num2->next;

    while (current1 != NULL && current2 != NULL) {
        if (current1->data < current2->data) {
            return -1; // num1 < num2
        } else if (current1->data > current2->data) {
            return 1; // num1 > num2
        }
        current1 = current1->next;
        current2 = current2->next;
    }

    if (current1 != NULL) {
        return 1; // num1 > num2
    } else if (current2 != NULL) {
        return -1; // num1 < num2
    }

    return 0; // num1 == num2
}

// Function to check if a big integer is zero
int isZero(Node* num) {
    Node* current = num->next;
    while (current != NULL) {
        if (current->data != 0) {
            return 0; // Not zero
        }
        current = current->next;
    }
    return 1; // Zero
}

// Function to perform division of two big integers
Node* divideBigInt(Node* num1, Node* num2) {
    Node* result = initializeBigInt();
    Node* dividend = initializeBigInt();
    Node* divisor = initializeBigInt();
    Node* tempResult = initializeBigInt();
    int sign = 1; // Sign of the result

    // Extract the signs
    if (num1->next->data == -1) {
        sign *= -1;
        num1->next->data = 0;
    }

    if (num2->next->data == -1) {
        sign *= -1;
        num2->next->data = 0;
    }

    // Copy num1 and num2 to dividend and divisor
    Node* current1 = num1->next;
    while (current1 != NULL) {
        insertDigit(dividend, current1->data);
        current1 = current1->next;
    }

    Node* current2 = num2->next;
    while (current2 != NULL) {
        insertDigit(divisor, current2->data);
        current2 = current2->next;
    }

    // Check for division by zero
    if (isZero(divisor)) {
        printf("Error: Division by zero\n");
        return result;
    }

    // Initialize variables for the division process
    int comparison = compareBigInt(dividend, divisor);
    int quotientDigit;
    Node* tempDividend = initializeBigInt();

    while (comparison != -1) {
        quotientDigit = 0;
        while (comparison != -1) {
            tempResult = initializeBigInt();
            while (compareBigInt(tempDividend, divisor) != -1) {
                tempDividend = subtractBigInt(tempDividend, divisor);
                quotientDigit++;
            }
            insertDigit(tempResult, quotientDigit);
            insertDigit(result, quotientDigit);
            tempDividend = addBigInt(tempDividend, tempResult);
            comparison = compareBigInt(tempDividend, divisor);
        }
        if (current1 != NULL) {
            insertDigit(tempDividend, current1->data);
            current1 = current1->next;
        }
        comparison = compareBigInt(tempDividend, divisor);
    }

    // Set the sign of the result
    if (sign == -1) {
        result->next->data = -1;
    }

    // Free allocated memory
    freeBigInt(dividend);
    freeBigInt(divisor);
    freeBigInt(tempDividend);
    return result;
}