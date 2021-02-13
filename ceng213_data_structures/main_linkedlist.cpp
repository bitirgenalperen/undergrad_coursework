#include <iostream>

#include "LinkedList.h"

int main() {
    LinkedList<int> llist;

    llist.print();

    llist.insertAtTheTail(6);
    llist.print();
    llist.insertAtTheHead(2);
    llist.print();
    llist.insertSorted(4);
    llist.print();
    llist.insertSorted(8);
    llist.print();
    llist.insertSorted(10);
    llist.print();
    llist.removeNode(7);
    llist.print();
    llist.removeNode(4);
    llist.print();
    llist.removeNode(9);
    llist.print();

    return 0;
}
