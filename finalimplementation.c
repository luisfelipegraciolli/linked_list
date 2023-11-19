#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
}Node;

// Função para criar um novo nó
Node* new_item(int data) {
    Node* new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

// Função para inserir um novo nó no início da lista
void push_front(Node** head, int data) {
    Node* new_node = new_item(data);
    new_node->next = *head;
    if (*head != NULL) {
        (*head)->prev = new_node;
    }
    *head = new_node;
}

// Função para remover o nó do início da lista
int pop_front(Node** head) {
    if (*head == NULL) {
        return -1; // Lista vazia
    }
    int data = (*head)->data;
    Node* temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
    return data;
}

// Função para inserir um novo nó após um nó específico na lista
void push_after(Node* prev_node, int data) {
    if (prev_node == NULL) {
        printf("O nó anterior não pode ser nulo.\n");
        return;
    }
    Node* new_node = new_item(data);
    new_node->next = prev_node->next;
    new_node->prev = prev_node;
    if (prev_node->next != NULL) {
        prev_node->next->prev = new_node;
    }
    prev_node->next = new_node;
}

// Função para encontrar um nó com um valor específico na lista
struct Node* find(Node* head, int data) {
    while (head != NULL) {
        if (head->data == data) {
            return head;
        }
        head = head->next;
    }
    return NULL; // Nó não encontrado
}

// Função para remover um nó específico da lista
void remove_node(Node** head, Node* node_to_remove) {
    if (*head == NULL || node_to_remove == NULL) {
        printf("A lista ou o nó a ser removido não podem ser nulos.\n");
        return;
    }
    if (node_to_remove->prev != NULL) {
        node_to_remove->prev->next = node_to_remove->next;
    } else {
        *head = node_to_remove->next;
    }
    if (node_to_remove->next != NULL) {
        node_to_remove->next->prev = node_to_remove->prev;
    }
    free(node_to_remove);
}

// Função para imprimir a lista
void print_list(Node* head) {
    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
    puts("");
}

// Função principal
int main() {
    Node* head = NULL;
    push_front(&head, 3);
    push_front(&head, 2);
    push_front(&head, 1);

    printf("- Lista inicial: -\n");
    print_list(head);


    printf("- Realizando pop_front() -\n");
    int popped_value = pop_front(&head);
    printf("Valor removido do início: %d\n", popped_value);

    printf("- Lista após remoção do início -\n");
    print_list(head);

    printf("- Inserindo o valor 4 apos o node contendo o valor 2 -\n");

    push_after(find(head, 2), 4);

    printf("- Lista após inserção -\n");
    print_list(head);

    printf("- Removendo o node que contem o valor 2 -\n");

    remove_node(&head, find(head, 2));

    printf("Lista após remoção: \n");
    print_list(head);
    return 0;
}

