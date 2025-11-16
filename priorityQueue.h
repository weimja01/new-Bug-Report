#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "linkedQueue.h"

template <class Type>
class priorityQueueType : public linkedQueueType<Type>
{
public:
    void enqueue(const Type& newElement);
    // Override enqueue to insert based on priority
    // Higher priority items go towards the front, after other high-priority items
};

template <class Type>
void priorityQueueType<Type>::enqueue(const Type& newElement)
{
    node<Type>* newNode = new node<Type>;
    newNode->data = new Type(newElement);
    newNode->link = nullptr;
    
    // If queue is empty, insert as the only element
    if (this->isEmptyQueue())
    {
        this->queueFront = newNode;
        this->queueRear = newNode;
    }
    // If new element has higher priority than front (front has lowest priority among all)
    // OR equal priority to front, add after all elements with same/higher priority
    else
    {
        node<Type>* current = this->queueFront;
        node<Type>* previous = nullptr;
        
        // Traverse to find the correct position
        // Keep moving while current element has higher or equal priority
        while (current != nullptr && *(current->data) >= newElement)
        {
            previous = current;
            current = current->link;
        }
        
        // Insert at the front
        if (previous == nullptr)
        {
            newNode->link = this->queueFront;
            this->queueFront = newNode;
        }
        // Insert at the end
        else if (current == nullptr)
        {
            previous->link = newNode;
            this->queueRear = newNode;
        }
        // Insert in the middle
        else
        {
            previous->link = newNode;
            newNode->link = current;
        }
    }
}

#endif