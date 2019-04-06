#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;

template <class T>
class DoublyLinkedList; // class declaration

// list node
template <class T>
struct DListNode {
  T obj;
  DListNode<T> *prev, *next;


  DListNode<T>(T e=T(), DListNode<T> *p = NULL, DListNode<T> *n = NULL)
    : obj(e), prev(p), next(n) {}
};


// doubly linked list
template <class T>
class DoublyLinkedList {
private:
  DListNode<T> header, trailer;
public:
  DoublyLinkedList()// constructor
  { 

    header.next = &trailer; trailer.prev = &header; 
  }

  DoublyLinkedList(const DoublyLinkedList& dll); // copy constructor
  DoublyLinkedList(DoublyLinkedList&& dll); // move constructor
  ~DoublyLinkedList(); // destructor
  DoublyLinkedList& operator=(const DoublyLinkedList& dll); // assignment operator
  DoublyLinkedList& operator=(DoublyLinkedList&& dll); // move assignment operator
  // return the pointer to the first node
  DListNode<T> *getFirst() const { return header.next; } 
  // return the pointer to the trailer
  const DListNode<T> *getAfterLast() const { return &trailer; }
  // return if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insertFirst(T newobj); // insert to the first of the list
  T removeFirst(); // remove the first node
  void insertLast(T newobj); // insert to the last of the list
  T removeLast(); // remove the last node
  void insertAfter(DListNode<T> &p, T newobj);
  void insertBefore(DListNode<T> &p, T newobj);
  T removeAfter(DListNode<T> &p);
  T removeBefore(DListNode<T> &p);
};




// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

// copy constructor
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& dll)
{
  // Initialize the list
  header.next = &trailer;
  trailer.prev = &header;
  
  
  //add more
  DListNode<T> * node = dll.getFirst();
  if(!dll.isEmpty()){
    while (node->next != NULL) {
      insertLast(node->obj);
      node = node->next;
    }
  }
}

// move constructor
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& dll)
{
  *this = dll;
  dll.~DoublyLinkedList();
}


// assignment operator
template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& dll)
{
  // use if (this != &dll)
  // Initialize the list
  header.next = &trailer;
  trailer.prev = &header;
  
  
  //add more
  DListNode<T> * node = dll.getFirst();
  if(!dll.isEmpty()){
    while (node->next != NULL) {
      insertLast(node->obj);
      node = node->next;
    }
  }
  return *this;
}


// move assignment operator
template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList&& dll)
{
  // use if (this != &dll)
  *this = dll;
  dll.~DoublyLinkedList();
  return *this;
}


// insert the new object as the first one
template <class T>
void DoublyLinkedList<T>::insertFirst(T newobj)
{ 
    DListNode<T> * node = new DListNode<T>(newobj, &header, header.next);
    header.next->prev = node;
    header.next = node;
}

// insert the new object as the last one
template <class T>
void DoublyLinkedList<T>::insertLast(T newobj)
{
    DListNode<T> * node = new DListNode<T>(newobj, trailer.prev, &trailer);
    trailer.prev->next = node;
    trailer.prev = node;
}

// remove the first object from the list
template <class T>
T DoublyLinkedList<T>::removeFirst()
{ 
    if(isEmpty())
      throw EmptyDLinkedListException("Empty");
    DListNode<T> *temp = header.next;
    header.next->next->prev = &header;
    header.next = header.next->next;
    T obj = temp->obj;
    delete temp;
    return obj;
}

// remove the last object from the list
template <class T>
T DoublyLinkedList<T>::removeLast()
{
    if(isEmpty())
      throw EmptyDLinkedListException("Empty");
    DListNode<T> *temp = trailer.prev;
    trailer.prev->prev->next = &trailer;
    trailer.prev = trailer.prev->prev;
    T obj = temp->obj;
    delete temp;
    return obj;
}


// destructor
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    while(header.next != &trailer){
      removeFirst();
    }
}


// return the first object
template <class T>
T DoublyLinkedList<T>::first() const
{ 
    return header.next->obj;
}

// return the last object
template <class T>
T DoublyLinkedList<T>::last() const
{
    return trailer.prev->obj;
}

// insert the new object after the node p
template <class T>
void DoublyLinkedList<T>::insertAfter(DListNode<T> &p, T newobj)
{
    DListNode<T> * node = new DListNode<T>(newobj, &p, p.next);
    p.next->prev = node;
    p.next = node;
}



// insert the new object before the node p
template <class T>
void DoublyLinkedList<T>::insertBefore(DListNode<T> &p, T newobj)
{
    DListNode<T> * node = new DListNode<T>(newobj, p.prev, &p);
    p.prev->next = node;
    p.prev = node;

}

// remove the node after the node p
template <class T>
T DoublyLinkedList<T>::removeAfter(DListNode<T> &p)
{
    if(p.next == &trailer)
      throw EmptyDLinkedListException("Out of Bounds");
    DListNode<T> *temp = p.next;
    p.next->next->prev = &p;
    p.next = p.next->next;
    T obj = temp->obj;
    delete temp;
    return obj;
}

// remove the node before the node p
template <class T>
T DoublyLinkedList<T>::removeBefore(DListNode<T> &p)
{
    if(p.prev == &header)
      throw EmptyDLinkedListException("Out of Bounds");
    DListNode<T> *temp = p.prev;
    p.prev->prev->next = &p;
    p.prev = p.prev->prev;
    T obj = temp->obj;
    delete temp;
    return obj;
}

// return the list length
template <class T>
int DoublyLinkedListLength(DoublyLinkedList<T>& dll)
{
    int sum = 0;
    DListNode<T> *node = dll.getFirst();
    if(!dll.isEmpty()){
      while (node->next != NULL) {
        sum++;
        node = node->next;
      }
    }
    return sum;
}


// output operator
template <class T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll)
{
  
  DListNode<T> *node = dll.getFirst();
  if(!dll.isEmpty()){
    while (node->next != dll.getAfterLast()) {
      out << node->obj <<",";
      node = node->next;
    }
  out << node->obj;
  }
  return out;
}






