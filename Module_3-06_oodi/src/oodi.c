#include <stdlib.h>
#include <string.h>
#include "oodi.h"


/* Exercise a: Initialize student record
 * 
 * Parameters:
 * or: Oodi record to be changed (does not need to be allocated)
 * p_student, p_course, p_grade, p_compdate: Values for different structure
 *      fields (must be copied)
 * 
 * Returns: 1 if initialization was succesful, 0 if it failed
 * If student ID is more than 6 characters, initialization fails.
 * 
 * -- Note that structure contains enough space for student ID, but not for
 * course name
 * -- Remember to check that reserved space is not overwritten
 */
int init_record(struct oodi *or, const char *p_student, const char *p_course,
        unsigned char p_grade, struct date p_date) {
    int max_student_id_length = 6;
    if (strlen(p_student) > max_student_id_length) 
        return -1;
    
    char* course_pointer = (char*)malloc((strlen(p_course) + 2) * sizeof(char)); // reserving as much space as many characters the p_course string has + 2 places for '\0'
    
    if (course_pointer != NULL) {
        or->course = course_pointer;
        strcpy(course_pointer, p_course);
        
        strcpy(or->student, p_student);
        or->grade = p_grade;
        or->compdate = p_date;
        
        return 1;
    }
    free(course_pointer);
    return 0;
}

/* Exercise b: Add a new record to a dynamic array.
 * (Resize the array as needed). All content of the new structure is copied.
 * 
 * Parameters:
 * array: start of an dynamic array (may be NULL, if array is empty)
 * length: current length of the array (number of entries)
 * newrec: new record to be added, all fields need to be copied.
 * 
 * Returns: pointer to the array after adding the new item
 */
struct oodi *add_record(struct oodi *array, unsigned int length, struct oodi newrec) {
    struct oodi* new_pointer = realloc(array, length * sizeof(struct oodi) + sizeof(struct oodi));
    
    if (new_pointer != NULL) {
//        if (new_pointer != array) { // all items have to be copied to the new space
//            for(int i = 0; i < length; i++) {
//                init_record(&new_pointer[i], array[i].student, array[i].course, array[i].grade, array[i].compdate);
//            }
//            
//            
//            free(array); // old space can be released
//        } 
        init_record(&new_pointer[length],newrec.student,newrec.course,newrec.grade, newrec.compdate);
        
        return new_pointer;
    }
    free(new_pointer);
    return NULL;
}

/* Exercise c: Change grade and date in existing record.
 * 
 * Parameters:
 * array: beginning of array
 * size: size of array
 * student: student ID to be changed
 * course: course to be changed
 * newgrade: new value for grade
 * newdate: new value for date
 * 
 * Returns: number of entries changed, i.e. either 1 or 0
 */
int change_grade(struct oodi *array, unsigned int size, const char *p_student,
        const char *p_course, unsigned char newgrade, struct date newdate) {
    struct oodi record;
    
    for (int i = 0; i < size; i++) {
        if (strcmp(array[i].student, p_student) == 0 && strcmp(array[i].course, p_course) == 0) {
            array[i].grade = newgrade;
            array[i].compdate = newdate;
            
            return 1;
        }
    }
    
    return 0;
}

/* Exercise d: Delete array (and all memory allocated for it)
 * 
 * Parameters:
 * array: beginning of the array
 * 
 * Returns: 1 when array is deleted
 */
int delete_array(struct oodi *array, unsigned int size)
{
    (void) array;
    (void) size;
    return 0;
}
