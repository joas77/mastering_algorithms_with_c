#include <stdlib.h>
#include <string.h>

#include "dlist.h"

void dlist_init(DList *list, void (*destroy)(void *data)) 
{
    /* Initialize the list */
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

void dlist_destroy(DList *list)
{
    void *data;

    /* Remove each element */
    if (dlist_remove(list, dlist_tail(list), (void **)&data) == 0 &&
        list->destroy != NULL)
    {
        /* Call a user defined function to free dynamically allocated data */
        list->destroy(data);
    }

    /* No operations are allowed now, but clear the structure as a precaution */
    memset(list, 0, sizeof(DList));
}

int dlist_ins_next(DList *list, DListElmt *element, const void *data)
{
    DListElmt *new_element;

    /* Do not allow a NULL element unless the list is empty */
    if (element == NULL && dlist_size(list) != 0)
    {
        return  -1;
    }

    /* Allocate storage for the element */
    new_element = (DListElmt *) malloc(sizeof(DListElmt));
    if (new_element == NULL)
    {
        return  -1;
    }

    /* Insert the new element into the list */
    new_element->data = (void *)data;

    if (dlist_size(list) == 0)
    {
        /* Handle insertion when the list is empty */
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_element;
    }
    else
    {
        /* Handle insertion when the list is not empty */
        new_element->next = element->next;
        new_element->prev = element;

        if (element->next == NULL)
        {
            list->tail = new_element;
        }
    }
     
    return 0;
}