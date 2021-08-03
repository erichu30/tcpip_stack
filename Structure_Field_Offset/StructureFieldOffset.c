// This is a practice to familiar with how to use offset to get the members of a structure

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "glthread.h"

typedef struct emp_{
    
    char name[30];
    unsigned int salary;
    char designation[30];
    unsigned int emp_id;
    glthread_node glnode;
}emp_t;

// argument: the address of glnode in type of struct glthread_node
// return: print the members of struct emp_t
void print_emp_details(emp_t *emp){
    printf("Employee Name:%s\n", emp->name);

}


int main(){
    // construct a pointer to emp_t object with empty content
    emp_t *emp = malloc(sizeof(emp_t));
    //fill in the content of the pointer
    strcpy(emp->name, "Eric");
    
    print_emp_details(emp);
    
    
    // free the space of the pointer
    free(emp);
}
