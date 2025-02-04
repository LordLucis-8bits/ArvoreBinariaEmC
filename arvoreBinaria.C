#include <stdio.h>
#include <stdlib.h>

//Estrutura do nó da árvore binária
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

//Função para criar um nó
Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Erro de memoria!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

//Função de inserir um nó na árvore
Node* insertNode(Node *root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    } else {
        printf("Valor ja existe na arvore.\n");
    }
    return root;
}

//Função que encontre um nó mínimo na sub-árvore direita
Node* findMin(Node *root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

//Função para remover um nó da árvore
Node* removeNode(Node *root, int data) {
    if (root == NULL) {
        printf("Valor nao encontrado na arvore.\n");
        return root;
    }
    if (data < root->data) {
        root->left = removeNode(root->left, data);
    } else if (data > root->data) {
        root->right = removeNode(root->right, data);
    } else {
        //Caso 1: Nó folha
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        //Caso 2: Um filho
        else if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        //Caso 3: Dois filhos
        Node *temp = findMin(root->right);
        root->data = temp->data;
        root->right = removeNode(root->right, temp->data);
    }
    return root;
}

//Funções para buscas
void preOrder(Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void postOrder(Node *root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

//Menu principal
int main() {
    Node *root = NULL;
    int choice, value;

    do {
        printf("\nMENU DE OPCOES\n");
        printf("1. Incluir no\n");
        printf("2. Remover no\n");
        printf("3. Buscar pre-ordem\n");
        printf("4. Buscar em ordem\n");
        printf("5. Buscar pos-ordem\n");
        printf("0. Encerrar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite o valor para incluir: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("Digite o valor para remover: ");
                scanf("%d", &value);
                root = removeNode(root, value);
                break;
            case 3:
                printf("Busca pre-ordem: ");
                preOrder(root);
                printf("\n");
                break;
            case 4:
                printf("Busca em ordem: ");
                inOrder(root);
                printf("\n");
                break;
            case 5:
                printf("Busca pos-ordem: ");
                postOrder(root);
                printf("\n");
                break;
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (choice != 0);

    return 0;
}
