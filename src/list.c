#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodeStruct {
    Info info;
    int index;
    struct nodeStruct* next;
    struct nodeStruct* back;
} NodeStruct;

typedef struct listStruct {
    NodeStruct* head;
    NodeStruct* tail;
    int size;
} ListStruct;

void dRemoveNode(List list, NodeL node);

// Cria e retorna a lista
List createList() {
    ListStruct* new = (ListStruct*)malloc(sizeof(ListStruct));

    new->head = NULL;
    new->tail = NULL;
    new->size = 0;

    return new;
}

// Encerra a lista e todos os nós no while
void endList(List list) {
    ListStruct* listAux = (ListStruct*)list;

    if (listAux->size != 0) {
        NodeStruct* aux;
        while (listAux->head) {
            aux = listAux->head;
            removeListNode(list, aux);
        }
    }

    free(listAux);
}

// Insere um elemento no fim da lista
void insertListElement(List list, Info info) {
    ListStruct* listAux = (ListStruct*)list;

    NodeStruct* new = (NodeStruct*)malloc(sizeof(NodeStruct));

    if (listAux->size == 0) {
        new->info = info;
        new->next = NULL;
        new->back = NULL;
        new->index = 0;
        listAux->head = new;
        listAux->tail = new;
        listAux->size++;
    } else {
        new->info = info;
        new->next = NULL;
        new->back = listAux->tail;
        new->index = new->back->index + 1;
        listAux->tail->next = new;
        listAux->tail = new;
        listAux->size++;
    }
}

void updateIndex(List list){
    ListStruct* listAux = (ListStruct*)list;
    int i = 0;

    for(NodeStruct* aux = listAux->head; aux; aux = aux->next){
        aux->index = i;
        i++;
    }
}

// Remove o nó da lista que voce passou de parametro
void removeListNode(List list, NodeL node) {
    ListStruct* listAux = (ListStruct*)list;
    NodeStruct* nodeAux = (NodeStruct*)node;

    if (listAux->size == 0)
        return;

    if (!nodeAux) {
        return;
    }

    NodeStruct* aux;

    // Se tiver um anterior linka com o próximo/ se não ele se torna a cabeça
    if (nodeAux->back) {
        aux = nodeAux->back;

        aux->next = nodeAux->next;
    } else {
        listAux->head = nodeAux->next;
    }

    // Se tiver próximo linka com o anterior/ se não ele se torna a calda
    if (nodeAux->next) {
        aux = nodeAux->next;

        aux->back = nodeAux->back;
    } else {
        listAux->tail = nodeAux->back;
    }

    free(nodeAux);
    listAux->size--;
    updateIndex(list);
}

// Função que retorna o info do nó
Info getListInfo(NodeL node) {
    NodeStruct* nodeAux = (NodeStruct*)node;

    return nodeAux->info;
}

// Função que retorna o primeiro elemento da lista
NodeL getListFirst(List list) {
    ListStruct* listAux = (ListStruct*)list;

    return listAux->head;
}

NodeL getListLast(List list) {
    ListStruct* listAux = (ListStruct*)list;

    return listAux->tail;
}

// Função que retorna o próximo elemento
NodeL getListNext(NodeL node) {
    NodeStruct* nodeAux = (NodeStruct*)node;

    return nodeAux->next;
}

// Função que retorna o elemento anterior
NodeL getListBack(NodeL node) {
    NodeStruct* nodeAux = (NodeStruct*)node;

    return nodeAux->back;
}

// Função que retorna o tamanho da lista
int getListSize(List list) {
    ListStruct* listAux = (ListStruct*)list;

    return listAux->size;
}

int getListIndexOf(NodeL node){
    NodeStruct* nodeAux = (NodeStruct*)node;

    return nodeAux->index;
}

NodeL getListNodeByIndex(List list, int index){
    ListStruct* listAux = (ListStruct*)list;

    int i = 0;
    for(NodeStruct* aux = listAux->head; aux; aux = aux->next){
        if(i == index){
            return aux;
        }
        i++;
    }

    return NULL;

}

void swapListInfo(NodeL node1, NodeL node2){
    NodeStruct* nodeAux1 = (NodeStruct*) node1;
    NodeStruct* nodeAux2 = (NodeStruct*) node2;

    Info aux = nodeAux1->info;

    nodeAux1->info = nodeAux2->info;
    nodeAux2->info = aux;

}