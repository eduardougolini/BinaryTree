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

char readTreeValue() {
    char treeValue;
    
    getchar();//Limpa buffer do teclado
    printf("Informe um valor a ser adicionado a estrutura da arvore: ('d' => deletar | 'm' => mostrar | 'p' => parar)");
    scanf("%c", &treeValue);
    getchar();

    return treeValue;
}

int readValueToDelete() {
    int value;
    
    printf("Informe o valor a ser excluido: ");
    scanf("%d", &value);
    
    return value;
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

void deleteNodeWithTwoChilds(Tree* nodeToDelete) {
    
}

void deleteNodeWithOneChild(Tree* nodeToDelete) {
    Tree* parentNode = nodeToDelete->backPointer;
    
    if(nodeToDelete->nextPointerLeft) {
        Tree* leftChild = nodeToDelete->nextPointerLeft;
        
        leftChild->backPointer = nodeToDelete->backPointer;
        parentNode->nextPointerLeft = nodeToDelete->nextPointerLeft;
    } else {
        Tree* rightChild = nodeToDelete->nextPointerRight;
        
        rightChild->backPointer = nodeToDelete->backPointer;
        parentNode->nextPointerRight = nodeToDelete->nextPointerRight;
    }
    
    return;
}

void checkNodeToDeleteType(Tree* nodeToDelete) {
    
    if (nodeToDelete->nextPointerLeft && nodeToDelete->nextPointerRight) {
        deleteNodeWithTwoChilds(nodeToDelete);
    } else {
        deleteNodeWithOneChild(nodeToDelete);
    }
    
    return;    
}

void findNodeToDelete(Tree* rootNode, int valueToDelete) {
    
    Tree* selectedNode = rootNode;
    
    while (true) {
        
        if (selectedNode->nodeValue == valueToDelete) {
            checkNodeToDeleteType(selectedNode);
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
        int treeValue = readTreeValue();
        int valueToDelete;
        
        switch (treeValue) {
            case 'm':
                showInsertedValues(rootNode);
                break;
            case 'd':
                valueToDelete = readValueToDelete();
                findNodeToDelete(rootNode, valueToDelete);
                break;
            case 'p':
                system("pause");
                return 0;
            default:
                int convertedReadedValue = treeValue - '0'; //Gambiarra do C para fazer parsing
                orderNode(rootNode, convertedReadedValue);
        }

    }

    system("pause");
    return 0;
}