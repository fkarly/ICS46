#ifndef __PROJ2_QUEUE_HPP
#define __PROJ2_QUEUE_HPP

#include "runtimeexcept.hpp"

class QueueEmptyException : public RuntimeException
{
public:
    QueueEmptyException(const std::string & err) : RuntimeException(err) {}
};


template<typename Object>
class LLQueue
{
private:
		int count = 0;
    struct Node{
      Object value;
      Node * next;
    };
    Node * head;
    Node * rear;

public:
    LLQueue()
    {
      head = nullptr;
      rear = nullptr;
    }

    //
    ~LLQueue()
    {
      while(head != nullptr)
        dequeue();
    }

    int size() const noexcept;
    bool isEmpty() const noexcept;

    Object & front();
    const Object & front() const;

    void enqueue(const Object & elem);

    // does not return anything. Just removes.
    void dequeue();
};

// Front Function, that will give the first element
// inside the queue.
template<typename Object>
Object & LLQueue<Object>::front()
{
  try
  {
    if(isEmpty())
        throw QueueEmptyException("Access to empty queue");
  }
  catch(QueueEmptyException& s)
  {
    std::cout << s << std::endl;
  }

  return head->value;
}

template<typename Object>
const Object & LLQueue<Object>::front() const
{
  try
  {
    if(isEmpty())
        throw QueueEmptyException("Access to empty queue");
  }
  catch(QueueEmptyException& s)
  {
    std::cout << s << std::endl;
  }

  return head->value;
}

// Keeping track of the # of queue.
template<typename Object>
int LLQueue<Object>::size() const noexcept
{
    return count;
}

// Function that will tell whether or  not the queue
// is empty.
template<typename Object>
bool LLQueue<Object>::isEmpty() const noexcept
{
    return count == 0;
}

// Queue function
template<typename Object>
void LLQueue<Object>::enqueue(const Object & elem)
{
    // Creating a temporary queue
    Node * tmp = new Node();
    tmp->value = elem;
    tmp->next = nullptr;

    // If the queue is empty, then front and back will
    // point to the new queue
    if(isEmpty())
    {
        head = tmp;
        rear = tmp;
        count++;
    }

    // Else, connect the last queue with the new one.
    // Then change the rear queue to the most recent one.
    else
    {
        rear->next = tmp;
        rear = tmp;
        count++;
    }
}

// Dequeue function
template<typename Object>
void LLQueue<Object>::dequeue()
{
    // Check to see if the que is empty
    try
    {
      if(isEmpty())
        throw QueueEmptyException("Dequeue from empty queue");
      // Get rid of the head Node and set the next head Node
      // to be the new head node.
      else
      {
          Node * tmp = head;
          head = head->next;
          delete tmp;
          count--;
      }
    }
    catch(QueueEmptyException& s)
    {
      std::cout << s << std::endl;
    }


}

#endif
