/**
 * Simple, non circular, double linked pointer list.
 * Created because the properties of the standard circular list were not
 * very well suited for the interference graph implementation.
 * This list uses an obstack and a free-list to efficiently manage its
 * elements.
 * @author Kimon Hoffmann
 * @date 14.07.2005
 * @note Until now the code is entirely untested so it probably contains
 * 		plenty of errors.
 */
#include <stdlib.h>

#include "plist.h"

/**
 * Helper macro that returns a new uninitialized list element by either
 * fetching one from the free-list or allocating a new one on the lists
 * obstack.
 * @param list the list for which to allocate the element.
 * @return the newly allocated, uninitialized element.
 */
static PListElement* allocate_element(PList* list) {
	PListElement* newElement;
	if (list->firstFreeElement != NULL) {
		newElement = list->firstFreeElement;
		list->firstFreeElement = newElement->next;
		newElement->next = NULL;
	} else {
		newElement = obstack_alloc(&list->obst, sizeof(*newElement));
	}
	return newElement;
}

PList* plist_new(void) {
	PList* list = xmalloc(sizeof(*list));
	obstack_init(&list->obst);
	list->firstElement = NULL;
	list->lastElement = NULL;
	list->firstFreeElement = NULL;
	list->elementCount = 0;
	return list;
}

void plist_free(PList* list) {
	obstack_free(&list->obst, NULL);
	list->firstElement = NULL;
	list->lastElement = NULL;
	list->firstFreeElement = NULL;
	list->elementCount = 0;
	xfree(list);
}

void plist_insert_back(PList* list, void* value) {
	if (list->lastElement != NULL) {
		plist_insert_after(list, list->lastElement, value);
	} else {
		PListElement* newElement = allocate_element(list);
		newElement->data = value;
		newElement->prev = NULL;
		newElement->next = NULL;
		list->firstElement = list->lastElement = newElement;
		list->elementCount = 1;
	}
}

void plist_insert_front(PList* list, void* value) {
	if (list->firstElement != NULL) {
		plist_insert_before(list, list->firstElement, value);
	} else {
		PListElement* newElement = allocate_element(list);
		newElement->data = value;
		newElement->prev = NULL;
		newElement->next = NULL;
		list->firstElement = list->lastElement = newElement;
		list->elementCount = 1;
	}
}

void plist_insert_before(PList* list, PListElement* element, void* value) {
	PListElement* prevElement;
	PListElement* newElement = allocate_element(list);

	newElement->data = value;
	newElement->next = element;
	prevElement = element->prev;
	newElement->prev = prevElement;
	if (prevElement != NULL) {
		prevElement->next = newElement;
	} else {
		list->firstElement = newElement;
	}
	element->prev = newElement;
	++list->elementCount;
}

void plist_insert_after(PList* list, PListElement* element, void* value) {
	PListElement* nextElement;
	PListElement* newElement = allocate_element(list);

	newElement->data = value;
	newElement->prev = element;
	nextElement = element->next;
	newElement->next = nextElement;
	if (nextElement != NULL) {
		nextElement->prev = newElement;
	} else {
		list->lastElement = newElement;
	}
	element->next = newElement;
	++list->elementCount;
}

void plist_erase(PList* list, PListElement* element) {
	PListElement* nextElement = element->next;
	PListElement* prevElement = element->prev;
	if (nextElement != NULL) {
		nextElement->prev = prevElement;
	} else {
		list->lastElement = prevElement;
	}
	if (prevElement != NULL) {
		prevElement->next = nextElement;
	} else {
		list->firstElement = nextElement;
	}
	--list->elementCount;
	/* Clean the element and prepend it to the free list */
	element->prev = NULL; /* The allocation code expects prev to be NULL */
	element->next = list->firstFreeElement;
	list->firstFreeElement = element;
}

void plist_clear(PList* list) {
	PListElement* currentElement = list->firstElement;
	while (currentElement != NULL) {
		currentElement->prev = NULL;
		currentElement = currentElement->next;
	}
	currentElement = list->lastElement;
	if (currentElement != NULL) {
		currentElement->next = list->firstFreeElement;
	}
	list->firstFreeElement = list->firstElement;
	list->firstElement = list->lastElement = 0;
	list->elementCount = 0;
}
