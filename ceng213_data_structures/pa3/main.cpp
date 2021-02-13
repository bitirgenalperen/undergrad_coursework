#include "HashTable.h"
#include <iostream>

using namespace std;

int main() {

    HashTable<int, int> intTable;

    for(int i =0 ;i<100;i++){
    	intTable.Insert(i,i);
    }

    for(int i =0 ;i<100;i++){
    	cout<<intTable.Get(i)<<endl;
    }
    
    intTable.Delete(23);
    intTable.Delete(46);
    intTable.Delete(32);
    intTable.Delete(45);
    intTable.Delete(42);
    intTable.Delete(35);    
    intTable.Delete(27);
    intTable.Delete(49);
    intTable.Delete(36);
    for(int i =50 ;i<100;i++){
    	cout<<intTable.Get(i)<<endl;
    }


	cout<<intTable.Get(35)<<endl;




return 0;
}