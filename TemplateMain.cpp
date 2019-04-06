#include "TemplateDoublyLinkedList.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>

using namespace std;

int main () {
  // Construct a linked list with header & trailer
  cout << "Create a new lists" << endl;
  DoublyLinkedList<string> dll;
  cout << "list: " << dll << endl << endl;

  // Insert 10 nodes at back with value 10,20,30,..,100
  cout << "Insert 10 nodes at back with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    stringstream ss;
    ss << i;
    dll.insertLast(ss.str());
  }
  cout << "list: " << dll << endl << endl;

  // Insert 10 nodes at front with value 10,20,30,..,100
  cout << "Insert 10 nodes at front with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    stringstream ss;
    ss << i;
    dll.insertFirst(ss.str());
  }
  cout << "list: " << dll << endl << endl;
  
  // Copy to a new list
  cout << "Copy to a new list" << endl;
  DoublyLinkedList<string> dll2(dll);
  cout << "list2: " << dll2 << endl << endl;
  
  // Assign to another new list
  cout << "Assign to another new list" << endl;
  DoublyLinkedList<string> dll3;
  dll3=dll;
  cout << "list3: " << dll3 << endl << endl;
  
  // Delete the last 10 nodes
  cout << "Delete the last 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    dll.removeLast();
  }
  cout << "list: " << dll << endl << endl;
  
  // Delete the first 10 nodes
  cout << "Delete the first 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    dll.removeFirst();
  }
  cout << "list: " << dll << endl << endl;
  
  // Check the other two lists
  cout << "Make sure the other two lists are not affected." << endl;
  cout << "list2: " << dll2 << endl;
  cout << "list3: " << dll3 << endl;





  // Construct a linked list with header & trailer
  cout << "\nCreate a new int list" << endl;
  DoublyLinkedList<int> dll7;
  cout << "list: " << dll7 << endl << endl;

  // Insert 10 nodes at back with value 10,20,30,..,100
  cout << "Insert 10 int nodes at back with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    dll7.insertLast(i);
  }
  cout << "list: " << dll7 << endl << endl;
  
  //Move to a new list
  cout << "\nMove to a new list" << endl;
  DoublyLinkedList<string> dll4(move(dll2));
  cout << "list4: " << dll4 << endl;
  cout << "list2: " << dll2 << endl;

  //Move assign to a new list
  cout << "\nMove assignment to a new list" << endl;
  DoublyLinkedList<string> dll5 =  move(dll3);
  cout << "list5: " << dll5 << endl;
  cout << "list3: " << dll3 << endl;

  //insert after second one
  cout << "\nInsert 42 after 2nd value and 32 before 5th" << endl;
  dll5.insertAfter(*dll5.getFirst()->next , "42");
  dll5.insertBefore(*dll5.getFirst()->next->next->next->next , "32");
  cout << "list5: " << dll5 << endl;

  //Delete added values
  cout << "\nDelete the added values" << endl;
  dll5.removeAfter(*dll5.getFirst()->next);
  dll5.removeBefore(*dll5.getFirst()->next->next->next->next);
  cout << "list5: " << dll5 << endl;

  //list length
  cout << "\nGet list5 length" << endl;
  cout << "list5 length: " << DoublyLinkedListLength(dll5) << endl;

  

  // more testing...
  // add tests for insertAfter, insertBefore
  // add tests for removeAfter, removeBefore
  // add tests for DoublyLinkedListLength
  
  return 0;
}
