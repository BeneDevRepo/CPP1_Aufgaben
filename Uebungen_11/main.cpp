#include <stdio.h>
#include <stdlib.h>


/**
 * Datenstruktur für ein Element ("node")
 * der verketteten Liste.
 */
struct node_t;
struct node_t {
    /* Ein Daten-Element vom Typ int */
    int data;
    /* Ein Zeiger auf ein weiteres Element vom Typ node */
    node_t *next;
};


/**
 * Erzeuge einen neuen Knoten
 *
 * @param val ist der Wert des Daten-Elements im neuen Knoten
 * @return Es wird ein Zeiger auf den neuen Knoten zurückgegeben.
 */
node_t *new_node(int val) {
    node_t *node = (node_t*) malloc(sizeof(node_t));
    node->data = val;
    node->next = NULL;
    return node;
}


/**
 * Erzeuge einen neuen Knoten und hänge
 * ihn ans Ende der Liste an
 *
 * @param head ist ein Zeiger auf das erste Element der Liste
 * @param val ist der Wert des Daten-Elements im neuen Knoten
 */
void append_node(node_t *head, int val) {
    node_t *curr = head;    
    if(head==NULL) {
        printf("Error: Leere Liste");
        return;
    }
    /**
     * Laufe bis zum letzten Element der Liste.
     * Dass man beim letzten Element angekommen ist,
     * erkennt man daran, dass der next-Zeiger auf Null zeigt,
     * also das nächste Element nicht vorhanden ist.
     */
    while(curr->next != NULL) {
        curr = curr->next;
    }
    /* Neues Element erzeugen */
    node_t *newnode = new_node(val);
    /**
     * und das vormals letzte Element ("curr")
     * auf das neue Element zeigen lassen
     */
    curr->next = newnode;
}

/**
 * Liste ausgeben
 *
 * @param head ist ein Zeiger auf das erste Element der Liste
 */
void print_list(node_t *head) {
    node_t *curr = head;
    while(curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

/**
 * Funktion zum Testen der Linked List
 */
void linkedlist() {
    node_t *head = new_node(1);
    append_node(head, 2);
    append_node(head, 3);
    append_node(head, 4);
    append_node(head, 5);
    print_list(head);
}

void reverse_list(node_t **head){
	node_t *curr = *head;
	node_t *prev = NULL;
	node_t *next = NULL;
	while(curr != NULL) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}

void delete_node(node_t **head, const int data) {
	// Falls liste leer:
	if(*head == nullptr)
		return;

	// Falls erstes element geloescht werden soll:
	if((*head)->data == data) {
		node_t *trash = *head;
		*head = (*head)->next;
		free(trash);
		return;
	}

	// Alles nach erstem Element:
	for(node_t *cur = *head; cur->next != nullptr; cur = cur->next) {
		node_t *next = cur->next;
		if(next->data == data) {
			node_t *trash = next;
			cur->next = next->next;
			free(trash);
			return;
		}
	}
}



int main() {
	node_t *head = new_node(1);
    append_node(head, 2);
    append_node(head, 3);
    append_node(head, 4);
    append_node(head, 5);
	print_list(head);

	reverse_list(&head);
	print_list(head);

	delete_node(&head, 1);
	print_list(head);

	delete_node(&head, 5);
	print_list(head);

	delete_node(&head, 3);
	print_list(head);
	return 0;
}