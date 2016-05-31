#include <stdio.h>
#include <stdlib.h>

struct Tree {
    struct Tree *backPointer;
    int nodeValue;
    struct Tree *nextPointerLeft;
    struct Tree *nextPointerRight;
};

int readRootValue() {
    int root;

    printf("Informe o numero da raiz: ");
    scanf("%d", &root);

    return root;
}

int readTreeValue() {
    int treeValue;

    printf("Informe um numero a ser adicionado a estrutura da arvore: (0 cancela execucao, 10000 mostra valores inseridos)");
    scanf("%d", &treeValue);

    return treeValue;
}

void addNodeToRight(Tree *parentNode, Tree *childNode) {
    parentNode->nextPointerRight = childNode;
    childNode->backPointer = parentNode;
}

void addNodeToLeft(Tree *parentNode, Tree *childNode) {
    parentNode->nextPointerLeft = childNode;
    childNode->backPointer = parentNode;
}

void orderNode(Tree *rootNode, int treeValue) {
    Tree* selectedNode = rootNode;
    Tree* newNode = new Tree();
    newNode->nodeValue = treeValue;

    while (true) {
        
        if (selectedNode->nodeValue == treeValue) {
            return;
        } else if (selectedNode->nodeValue > treeValue) {
            
            if (selectedNode->nextPointerLeft) {
                selectedNode = selectedNode->nextPointerLeft;
            } else {
                addNodeToLeft(selectedNode, newNode);
                return;
            }
            
        } else if (selectedNode->nodeValue < treeValue) {
            
            if (selectedNode->nextPointerRight) {
                selectedNode = selectedNode->nextPointerRight;
            } else {
                addNodeToRight(selectedNode, newNode);
                return;
            }
            
        }
        
    }

}

void deleteNodeWithDoubleChilds(Tree* selectedNode) {
    Tree* backupNode = selectedNode;
    Tree* backNode = selectedNode->backPointer;

    if (backNode->nextPointerLeft == selectedNode) {
            backNode->nextPointerLeft = selectedNode->nextPointerLeft;
    } else {
            return;
    }
	
}

void deleteNodeWithOneChild(Tree* selectedNode, char type) {
    Tree* backNode = selectedNode->backPointer;

    if (type == 'l') {
            backNode->nextPointerLeft = selectedNode->nextPointerRight;
    } else if (type == 'r') {
            backNode->nextPointerRight = selectedNode->nextPointerRight;
    }
}

void deleteNode(Tree* selectedNode) {
    if (selectedNode->nextPointerLeft && selectedNode->nextPointerRight) {
            deleteNodeWithDoubleChilds(selectedNode);
    } else if (selectedNode->nextPointerLeft) {
            deleteNodeWithOneChild(selectedNode, 'l');
    } else if (selectedNode->nextPointerRight) {
            deleteNodeWithOneChild(selectedNode, 'r');
    }
}

void showInsertedValues(Tree *mainNode) {
    Tree* selectedNode = mainNode;

    while (true) {

        printf("Valor do no atual e %d\n", selectedNode->nodeValue);

        int hasBackPointer = false;
        if (! selectedNode->backPointer) {
            printf("Aperte 4 para ir para o no a esquerda, 6 para ir para a direita ou 0 para sair\n");
        } else {
            hasBackPointer = true;
            printf("Aperte 4 para ir para o no a esquerda, 6 para ir para a direita, 2 para ir ao no anterior ou 0 para sair\n");
        }

        int option;
        scanf("%d", &option);

        if (hasBackPointer && option == 2) {
            selectedNode = selectedNode->backPointer;
        } else if (option == 4) {

            if (!selectedNode->nextPointerLeft) {
                printf("Nao existe valor a esquerda!");
                return;
            }

            selectedNode = selectedNode->nextPointerLeft;
        } else if (option == 6) {

            if (!selectedNode->nextPointerRight) {
                printf("Nao existe valor a direita!");
                return;
            }

            selectedNode = selectedNode->nextPointerRight;
        } else if (option == 0) {
            return;
        }
    }
}

int main() {
	
    Tree* rootNode = new Tree();
    rootNode->nodeValue = readRootValue();

    while (true) {
        int treeValue = readTreeValue();

        if (treeValue == 0) {
                break;
        }

        if (treeValue == 10000) {
                showInsertedValues(rootNode);
        }

        orderNode(rootNode, treeValue);

    }

    system("pause");
    return 0;
}