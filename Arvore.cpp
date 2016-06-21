#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#define vetor_size  8

struct Tree {
    struct Tree *backPointer;
    int nodeValue;
    int flare;
    struct Tree *nextPointerLeft;
    struct Tree *nextPointerRight;
};

char readUserChoice() {
    char treeValue;
    
    getchar();//Limpa buffer do teclado
    printf("Opcoes: d' => deletar | 'm' => mostrar | 'p' => parar | 'f' parar e salvar em pre ordem: ");
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

void read(int *vetor) {
    std::ifstream file("inputValues.txt");

    for (int i = 0; i < vetor_size; i++) {
        file >> vetor[i];
    }
}

void write(Tree *mainNode) {
    std::ofstream file("outputValues.txt");
    Tree* actualNode = mainNode;
        
    for (int i = 0; i < vetor_size; i++) {
        file << actualNode->nodeValue;
        file << " , ";
        
        actualNode->flare = true;
        
        if (actualNode->nextPointerLeft && actualNode->nextPointerLeft->flare != true) {
           actualNode = actualNode->nextPointerLeft;
        } else if(actualNode->nextPointerRight && actualNode->nextPointerRight->flare != true) {
           actualNode = actualNode->nextPointerRight;
        } else if(actualNode->backPointer->nextPointerRight && actualNode->backPointer->nextPointerRight->flare != true) {
           actualNode = actualNode->backPointer->nextPointerRight;
        }else {
            actualNode = mainNode->nextPointerRight;
        }
    }

    file.close();
}

int main() {
	
    int vetor[vetor_size];
    read(vetor);
    
    Tree* rootNode = new Tree();
    rootNode->nodeValue = vetor[0];
    
    for (int i = 1; i < vetor_size; i++) {
        int nodeValue = vetor[i];
        orderNode(rootNode, nodeValue);
    }

    while (true) {
        char choice = readUserChoice();
        int valueToDelete;
        
        switch (choice) {
            case 'm':
                showInsertedValues(rootNode);
                break;
            case 'd':
                valueToDelete = readValueToDelete();
                findNodeToDelete(rootNode, valueToDelete);
                break;
            case 'p':
                return 0;
            case 'f':
                write(rootNode);
                return 0;
            default:
                return 0;
        }

    }

    return 0;
}