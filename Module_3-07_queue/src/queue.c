#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "queuepriv.h"

Queue *Queue_init(void) {
    Queue *q = calloc(1, sizeof(Queue));
    return q;
}

void enqueue(Queue *queue_pointer, struct student* student_pointer) {
    if (queue_pointer->last != NULL) { // check if the queue is not empty
        queue_pointer->last->next = student_pointer;
    } else { // this is the first item in the queue 
        queue_pointer->first = student_pointer;
    }
    queue_pointer->last = student_pointer; // assigning the last pointer to this item as this was the most recently added one
}

/// Adds a new student element to the queue. 
/// \param q The queue to be extended.
/// \param id The ID of the student. Should not be longer than 6 characters.
/// \param name The name of the student - the space for this should be dynamically allocated. 
/// \return 0 if the ID is longer than 6 characters or the allocation of the dynamic space has failed; 1 if adding the item was successful. 
int Queue_enqueue(Queue *q, const char *id, const char *name) {
    int max_id_length = 6;
    if (strlen(id) > max_id_length) 
        return 0;
    
    struct student* student_pointer = malloc(sizeof(struct student));
    char* name_pointer = malloc(sizeof(char) * (strlen(name) + 2));
    
    if (student_pointer != NULL && name_pointer != NULL) {
        // setting up the new student object
        strcpy(name_pointer, name);
        strcpy(student_pointer->id, id);
        student_pointer->name = name_pointer;
        student_pointer->next = NULL; 
        
        enqueue(q, student_pointer);
        
        return 1;
    }
    
    free(student_pointer);
    free(name_pointer);
    return 0;
}

char *Queue_firstID(Queue *q) {
    if (q && q->first)
        return q->first->id;
    else
        return NULL;
}

char *Queue_firstName(Queue *q) {
    if (q && q->first)
        return q->first->name;
    else
        return NULL;
}

int Queue_dequeue(Queue *q) {
    (void) q;
    return 0;
}

int Queue_drop(Queue *q, const char *id) {
    (void) q;
    (void) id;
    return 0;
}

void Queue_delete(Queue *q) {
    if (q) {
        while(Queue_dequeue(q));
        free(q);
    }
}
