#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    char dado;
    struct Node* next;
    struct Node* prev;
    
}Node;

Node* new_item(char dado){
    Node* node = malloc(sizeof(Node));
    node->dado = dado;
    node->next = NULL;
    return node;
}

Node* push_front(Node* head, char dado){
    Node* nova_head = new_item(dado);
    if(head == NULL){
        return nova_head;
    }
    nova_head->next = head;
    head->prev = nova_head;
    return nova_head;
}

Node* pop_front(Node* head){
    if(head == NULL){
        printf("Nenhum node a ser excluido");
    }

    Node* nova_head = head->next;

    //Caso reste apenas um node apos o pop, nosso node restante tera um ponteiro prev = a NULL
    if(nova_head!=NULL){
        nova_head->prev = NULL;
    }

    free(head);
    return nova_head;
}

Node* back_node(Node* head){
    if(head == NULL)
        return NULL;

    Node* back = head;
    if(back->next!=NULL){
        back = back_node(back->next);
    }

    return back;
}


void push_after(Node* node, char dado){
    if(node == NULL)
        return;
    Node* novo_node = new_item(dado);

    novo_node->next = node->next;
    novo_node->prev = node;

    Node* temp = node->next;

    node->next = novo_node;
    temp->prev = novo_node;

}

Node* find(Node* head, char dado_procurado){
    Node* current = head;
    while(current!=NULL){
        if(current->dado == dado_procurado){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void printLinkedList(Node* head){
    for (Node* p = head; p!=NULL; p=p->next)
    {
        printf("%c ", p->dado);
    }
    puts("");
    puts("");

}

Node* remove_node(Node* head, Node* target){
    if(head == NULL || target == NULL)
        return head;
    if(target == head){
        return pop_front(head);
    }
    Node* tempA = target->next;
    Node* tempB = target->prev;

    tempB->next = tempA;
    tempA->prev = tempB;
    free(target);
    return head;


}


int main(int argc, char const *argv[])
{
    Node* head = NULL;
    //Coloca coisas na nossa lista encadeada
    head = push_front(head, 'a');
    head = push_front(head, 'b');
    head = push_front(head, 'c');

    // Eclui o c e coloca denovo na lista
    printLinkedList(head);
    head = pop_front(head);
    printLinkedList(head);
    head = push_front(head, 'c');
    printLinkedList(head);

    //Inserir apos o node contendo o 'b'
    Node* target = find(head, 'b');
    push_after(target, 'x');
    printLinkedList(head);

    //Ecluir o node que contem 'x'
    Node* target2 = find(head, 'x');
    head = remove_node(head, target2);
    printLinkedList(head);

    return 0;
}
