#include "Entities.h"
#include "HashTable.h"

int main(){
    HashTable<User> ht(10);

    Student s1("101", "Alice", "CS");
    Student s2("102", "Bob", "Math");
    Teacher t1("201", "Dr. Smith", "CS");
    Teacher t2("202", "Dr. Jones", "Math");
    ht.insert(s1);
    ht.insert(s2);
    ht.insert(t1);
    ht.insert(t2);
    ht.print();
    return 0;
}
