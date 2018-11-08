/*****************************
*                            *
*------------ list.c ------  *
*                            *
******************************/

#include <stdlib.h>
#include <string.h>

#include "list.h"

void list_init(List *list, void (*destroy) (void *data))
{
    /* initialize the list */

    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

void list_destroy(List *list) 
{
    void *data;

    /* remove each element */

    while( list_size(list) > 0 )
    {
        if( list_rem_next(list, NULL, (void **)&data) == 0 && list->destroy != NULL)
        {
            /* call a user defined function to free dynamically allocated data */
            list->destroy(data);
        }
    }

    /* No operations are allowed now, but clear the structure as a precaution */
    memset(list, 0, sizeof(list));
}
