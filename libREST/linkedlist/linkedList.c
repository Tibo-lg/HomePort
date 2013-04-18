// linkedList.c

/*  Copyright 2013 Aalborg University. All rights reserved.
 *   
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  
 *  1. Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  
 *  2. Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  
 *  THIS SOFTWARE IS PROVIDED BY Aalborg University ''AS IS'' AND ANY
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Aalborg University OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 *  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *  
 *  The views and conclusions contained in the software and
 *  documentation are those of the authors and should not be interpreted
 *  as representing official policies, either expressed.
 */

#include "linkedList.h"
/// Create linked list
/**
 * Empty LinkedList container is created, initialised with head and tail
 * pointing at NULL.
 *
 * \param
 */
LinkedList *create()
{
   LinkedList *linkedList = malloc(sizeof(*linkedList));
   if(!linkedList)
   {
      fprintf(stderr, "Linked list not allocated\n");
      return NULL;
   }
   linkedList->head = NULL;
   linkedList->tail = NULL;

   return linkedList;
}

/// Insert list element
/**
 * Insert new element into linked list.
 *
 * \param linked list to insert into.
 * \param string key to retrieve value.
 * \param value pointer with any data.
 */
int insert(LinkedList *ll, char *key, void *val)
{
   ListElement *element = malloc(sizeof(*element));
   if(!element)
   {
      fprintf(stderr, "List element not allocated\n" );
      return 1;
   }

   if(ll->head == NULL)
      ll->head = element;
   else
      ll->tail->next = element;
   ll->tail = element;
   element->next = NULL;
   element->val = val;
   element->key = key;

   return 0;
}

/// get linked list element
/**
 * Lookup list element and if found the value is returned
 *
 * \param linked list to get element from.
 * \param key string to perform lookup with.
 */
void* get(LinkedList *ll, char *key)
{
   ListElement *tempElement = ll->head;
   while(tempElement != NULL)
   {
      if(strcmp(tempElement->key, key) == 0)
      {
         return tempElement->val;
      }
      tempElement = tempElement->next;
   }
   return NULL;
}

/// Destroy linked list and elements
/**
 * Destoys the linked list and frees the list elements ans lastly the
 * container
 *
 * \param linked list to be destroyed.
 */
void destroy(LinkedList *ll)
{
   while(ll->head->next != NULL)
   {
      //moving head down the list as elements are freed
      ListElement *target = ll->head;
      ll->head = ll->head->next;
      free(target);
   }
   free(ll->head);
   free(ll);
}

/// remove element for linked list
/**
 * Searches for an element and if found, the element is removed. 
 *
 * /param linked list to remove element from
 * /param key string to compare elements for removal 
 */
void removeElement(LinkedList *ll, char *key)
{  
   ListElement *target = ll->head;
   ListElement *prev = NULL;
   while(target != NULL)
   {
      if(strcmp(target->key, key) == 0)
      {
         if(prev != NULL)
            prev->next = target->next;
         else 
            ll->head = target->next;
         free(target);
      }
      prev = target;
      target = target->next;
   }
}
