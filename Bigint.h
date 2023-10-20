struct Node {
    int data;
    struct Node* next;
};
typedef struct Node Node;
Node* initializeBigInt();
void insertDigit(Node* head, int digit);
void printBigInt(Node* head);
void freeBigInt(Node* num);
Node* addBigInt(Node* num1, Node* num2);
Node* subtractBigInt(Node* num1, Node* num2);
Node* multiplyBigInt(Node* num1, Node* num2);
int compareBigInt(Node* num1, Node* num2);
int isZero(Node* num);
Node* divideBigInt(Node* num1, Node* num2);