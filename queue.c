/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (!q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (!q)
        return;

    list_ele_t *curh = q->head;
    while (curh) {
        list_ele_t *nexth = curh->next;
        free(curh->value);
        free(curh);
        curh = nexth;
    }

    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* What should you do if the q is NULL? */
    if (!q || !s)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;

    newh->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (!newh->value) {
        free(newh);
        return false;
    }

    strcpy(newh->value, s);

    if (!q->tail)
        q->tail = newh;

    newh->next = q->head;
    q->head = newh;
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q || !s)
        return false;

    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;

    newh->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (!newh->value) {
        free(newh);
        return false;
    }

    strcpy(newh->value, s);
    if (!q->head)
        q->head = newh;

    newh->next = NULL;
    if (!q->tail)
        q->tail = newh;
    else {
        q->tail->next = newh;
        q->tail = newh;
    }

    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (!q || !q->head || q->size == 0 || !sp)
        return false;

    list_ele_t *popedh = q->head;
    if (strlen(popedh->value) > bufsize - 1) {
        strncpy(sp, popedh->value, bufsize - 1);
        memset(sp + bufsize - 1, '\0', 1);
        // Set \0 to the tail.
    } else
        strncpy(sp, popedh->value, strlen(popedh->value) + 1);

    if (q->head->next) {
        q->head = q->head->next;
    } else
        q->head = NULL;

    free(popedh->value);
    free(popedh);

    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q)
        return 0;
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (!q || q->size == 0)
        return;

    list_ele_t *curh = q->head;
    list_ele_t *curnxt = curh->next;
    list_ele_t *nxtmp;
    if (curnxt)
        nxtmp = curnxt->next;

    while (curh != q->tail) {
        curnxt->next = curh;
        curh = curnxt;

        if (nxtmp) {
            curnxt = nxtmp;
            nxtmp = nxtmp->next;
        }
    }

    q->head->next = NULL;
    list_ele_t *temp = q->head;
    q->head = q->tail;
    q->tail = temp;
}
