#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "queuepriv.h"
#include <stdbool.h>

Queue *Queue_init(void) {
    Queue *q = calloc(1, sizeof(Queue));
    return q;
}

void* free_student(struct student* student) {
    free(student->name);
    free(student);
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
    if (student_pointer != NULL) {
        student_pointer->name = malloc(sizeof(char) * (strlen(name) + 1));
        
        if (student_pointer->name != NULL) {
            // setting up the new student object
            strcpy(student_pointer->name, name);
            strcpy(student_pointer->id, id);
            student_pointer->next = NULL; 

            enqueue(q, student_pointer);
            return 1;
        }
    }
    
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

/// Removes the first member of the queue, and releases all memory allocated for it.
/// \param q
/// \return 1, if something was removed; or 0 if nothing was removed, i.e., because the queue was already empty.
int Queue_dequeue(Queue *q) {
    if (q->first != NULL) {
        if (q->first == q->last) { // only one item in the queue
            free_student(q->first);
            q->first = NULL;
            q->last = NULL;
        } else { // more than one item
            struct student* first_item = q->first;
            q->first = first_item->next;
            free_student(first_item);
        }
        
        return 1;
    }
    
    return 0;
}

int Queue_drop(Queue *q, const char *id) {
    if (q->first != NULL) {
        if (strcmp(q->first->id, id) == 0) {
            Queue_dequeue(q);
            return 1;
        } else {
            struct student* next_student = q->first;
            struct student* last_student;
            do {
                if (strcmp(next_student->id, id) == 0) {
                    struct student* student_to_delete = next_student;
                   
                        last_student->next = student_to_delete->next;
                    
                    if (student_to_delete == q->last) {
                        q->last = last_student;
                        last_student->next = NULL;
                    }
                    free_student(student_to_delete);
                    return 1;
                }
                
                last_student = next_student;
                next_student = next_student->next;
            } while(next_student != NULL);
        }
    }
    
    return 0;
}

void Queue_delete(Queue *q) {
    if (q) {
        while(Queue_dequeue(q));
        free(q);
    }
}
