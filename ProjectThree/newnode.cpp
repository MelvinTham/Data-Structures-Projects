// FILE: node1.cxx
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
// INVARIANT for the node class:
//   The data of a node is stored in data_field, and the link in link_field.

#include "newnode.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
using namespace std;

namespace main_savitch_5
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
	node *insert_ptr;

	insert_ptr = new node(entry, previous_ptr->link( ));
	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
	node *cursor;

	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    if (target == cursor->data( ))
		return cursor;
	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
	const node *cursor;

	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    if (target == cursor->data( ))
		return cursor;
	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
	node *cursor;
	size_t i;

	assert (0 < position);
	cursor = head_ptr;
	for (i = 1; (i < position) && (cursor != NULL); i++)
	    cursor = cursor->link( );
	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
	const node *cursor;
	size_t i;

	assert (0 < position);
	cursor = head_ptr;
	for (i = 1; (i < position) && (cursor != NULL); i++)
	    cursor = cursor->link( );
	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
	node *remove_ptr;

	remove_ptr = head_ptr;
	head_ptr = head_ptr->link( );
	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
	node *remove_ptr;

	remove_ptr = previous_ptr->link( );
	previous_ptr->set_link( remove_ptr->link( ) );
	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
	while (head_ptr != NULL)
	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
	head_ptr = NULL;
	tail_ptr = NULL;

	// Handle the case of the empty list.
	if (source_ptr == NULL)
	    return;
	list_head_insert(head_ptr, source_ptr->data( ));
	tail_ptr = head_ptr;
	source_ptr = source_ptr->link( );
	while (source_ptr != NULL)
	{
	    list_insert(tail_ptr, source_ptr->data( ));
	    tail_ptr = tail_ptr->link( );
	    source_ptr = source_ptr->link( );
	}
    }
    // list_occurrences is an O(n) because it is not just one step.
    //It requires cursor to go through the whole link list, making the big O notation O(n).
    std::size_t list_occurrences(const node* head_ptr, const node::value_type& target)
    {
        const node *cursor;
        size_t count = 0;
        cursor = head_ptr;

        if (cursor ==NULL)
            return 0;
        for (cursor = head_ptr;cursor!=NULL;cursor = cursor->link())
        {
            if (target==cursor->data())
                count++;
        }
            return count;
    }
    //list_attach is also O(n) because it has to go through a loop to find the last
    // tail and attach a new node to it.
    void list_tail_attach(node*& head_ptr, const node::value_type& entry)
    {
        node *new_node = new node(entry,head_ptr);
        node *tail_ptr;
        if(list_length(head_ptr)==0)
        {
            head_ptr = new_node;
            tail_ptr = new_node;
        }
        else
        {
            node *tail_insert = new node;
            tail_insert->set_data(entry);
            tail_insert->set_link(list_locate(head_ptr,list_length(head_ptr))->link());
            list_locate(head_ptr,list_length(head_ptr))->set_link(tail_insert);
        }
    }
    //BIG O NOTATION LIST_TAIL_REMOVE: is also O(n) because it has to go through a loop to find the last node and remove it.
    void list_tail_remove(node*& head_ptr)
    {
        node *remove_tail;

        if (head_ptr==0)
            head_ptr = NULL;

        else if (list_length(head_ptr)==1)
            list_head_remove(head_ptr);

        else
        {
            remove_tail= list_locate(head_ptr,list_length(head_ptr));
            list_locate(head_ptr,list_length(head_ptr)-1)->set_link(NULL);
        }
            delete remove_tail;
    }
    // list_copy_front is also has a O(n) notation because
    // source_ptr and tail_ptr traverses the list. It's much more complex than O(1).
    node* list_copy_front(const node* source_ptr, std::size_t n)
    {
        node *head_ptr;
        node *tail_ptr;
        head_ptr=new node;
        head_ptr= NULL;
        tail_ptr=NULL;
        int count =0;
        if (n == 0)
            return head_ptr;

        list_head_insert(head_ptr, source_ptr->data( ));
        tail_ptr = head_ptr;
        count++;

        source_ptr = source_ptr->link( );
        while (count<n)
	{
	    list_insert(tail_ptr, source_ptr->data( ));
	    count ++;
	    tail_ptr = tail_ptr->link( );
	    source_ptr = source_ptr->link( );
	}
        return head_ptr;
    }
}



