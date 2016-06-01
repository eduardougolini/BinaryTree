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

int readNodeValue() {
    int node;

    printf("Informe o numero do no: ");
    scanf("%d", &node);

    return node;
}

char readUserChoice() {
    char treeValue;
    
    getchar();//Limpa buffer do teclado
    printf("Opcoes: 'i' => inserir | d' => deletar | 'm' => mostrar | 'p' => parar : ");
    scanf("%c", &treeValue);
    getchar();

    return treeValue;
}

int readValueToDelete() {
    int valueToDelete;
    
    printf("Informe o valor a ser excluido: ");
    scanf("%d", &valueToDelete);
    
    return valueToDelete;
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

int getSmallestNodeValueAtRightAndRemoveIt(Tree *mainNode) {
    Tree* selectedNode = mainNode->nextPointerRight;
    
    while (true) {
        
        if(! selectedNode->nextPointerLeft) {
            int smallestValue = selectedNode->nodeValue;
            Tree* backNode = selectedNode->backPointer;
            
            delete(selectedNode);
            
            if (selectedNode->nodeValue != backNode->nodeValue) {
                backNode->nextPointerRight = selectedNode->nextPointerRight;
            } else {
                backNode->nextPointerLeft = selectedNode->nextPointerLeft;
            }
            
            selectedNode->backPointer = backNode->backPointer;
            
            return smallestValue;
        } else {
            selectedNode = selectedNode->nextPointerLeft;
        }
        
    }
}

void deleteNodeWithTwoChilds(Tree *nodeToDelete) {
    int newNodeValue = getSmallestNodeValueAtRightAndRemoveIt(nodeToDelete);
        
    nodeToDelete->nodeValue = newNodeValue;
}

void deleteNodeWithOneChild(Tree *nodeToDelete) {
    Tree* parentNode = nodeToDelete->backPointer;
    
    if(nodeToDelete->nextPointerLeft) {
        Tree* leftChild = nodeToDelete->nextPointerLeft;
        
        leftChild->backPointer = nodeToDelete->backPointer;
        parentNode->nextPointerLeft = nodeToDelete->nextPointerLeft;
    } else if (nodeToDelete->nextPointerRight) {
        Tree* rightChild = nodeToDelete->nextPointerRight;
        
        rightChild->backPointer = nodeToDelete->backPointer;
        parentNode->nextPointerRight = nodeToDelete->nextPointerRight;
    } else {
        Tree* backNode = nodeToDelete->backPointer;
        
        if(backNode->nextPointerRight == nodeToDelete) {
            backNode->nextPointerRight = NULL;
        } else {
            backNode->nextPointerLeft = NULL;
        }
    }
    
    return;
}

void checkNodeToDeleteType(Tree *nodeToDelete) {
    
    if (nodeToDelete->nextPointerLeft && nodeToDelete->nextPointerRight) {
        deleteNodeWithTwoChilds(nodeToDelete);
    } else {
        deleteNodeWithOneChild(nodeToDelete);
    }
    
    return;    
}

void findNodeToDelete(Tree *rootNode, int valueToDelete) {
    Tree* selectedNode = rootNode;
        
    while (true) {
        
        if (selectedNode->nodeValue == valueToDelete) {
            checkNodeToDeleteType(selectedNode);
            break;
        } else if (selectedNode->nodeValue > valueToDelete) {
            selectedNode = selectedNode->nextPointerLeft;
        } else {
            selectedNode = selectedNode->nextPointerRight;
        }
        
    }
    
    return;
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
        char choice = readUserChoice();
        int nodeValue, valueToDelete;
        
        switch (choice) {
            case 'i':
                nodeValue = readNodeValue();
                orderNode(rootNode, nodeValue);
                break;
            case 'm':
                showInsertedValues(rootNode);
                break;
            case 'd':
                valueToDelete = readValueToDelete();
                findNodeToDelete(rootNode, valueToDelete);
                break;
            case 'p':
                return 0;
            default:
                return 0;
        }

    }

    return 0;
}