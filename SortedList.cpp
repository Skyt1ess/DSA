#include <iostream>

using namespace std;

template<typename T>
class ISortedList {// sorted list implemetation
    public:
        void add(T item);   // add a new item to the List
        void remove(int i); // remove i-th least element from the list

        T least();      // return the least element
        T greatest();   // return the greatest element
        T get(int i);   // return the i-th least element
        int indexOf(T item);    // return the index of an element (in a sorted sequence)
        ISortedList<T> searchRange(T from, T to);    // find all items between from and to
        bool isEmpty(); // return whether the list is empty
        int size = 0;   // return the size of the list

        ISortedList() = default;  //default constructor
        ~ISortedList() = default; //default destructor

    private:
        struct Node {        //node struct
            T data;
            Node* next = 0;
        };
        Node* first;    // pointer to the first node
        Node* last;     //pointer to the last node
        Node* current;  //pointer to the current node
};

template <typename T>
void ISortedList<T>::add(T item) {// O(n)
    size++;

    struct Node* newNode = new Node;    //allocate memory for new node
    newNode->data = item;               //assign data to new node

    current = first;

    if (size == 1) {                    //handle edge 4 cases: if size = 1 or 2, if item < first or item > last
        first = last = newNode;
    } else

    if (size == 2) {
        last = newNode;
        if (item < first->data) {
            swap(first, last);
        }
        first->next = last;
    } else

    if (item < first->data) {
        newNode->next = first;
        swap(newNode, first);

    } else

    if (item > last->data) {
        last->next = newNode;
        swap(newNode, last);

    } else {                                //adding item between first and last

        while (item > current->next->data) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

}
template <typename T>
void ISortedList<T>::remove(int i) { // O(n)
        if (isEmpty() || i < 1 || i > size) return; //handle edge 3 cases: if size < i, if i < 1 or  isEmpty

    size--;
    int k = i - 1;

    if (i == 1) {
        first = first ->next;
    } else {

        struct Node* newNode = new Node;
        current = first;

        while (k--) { // find needed node
            newNode = current;
            current = current->next;
        }
        newNode->next = current->next;//delete i pos element
        if (i == size + 1) {
            last = newNode;
        }

        current = NULL;
    }

}
template <typename T>
T ISortedList<T>::least() { //O(1) return least element
    if (isEmpty()) return {};
    return first->data;
}

template <typename T>
T ISortedList<T>::greatest() {//O(1) return greatest element
    if (isEmpty()) return {};
    return &last->data;
}

template <typename T>
bool ISortedList<T>::isEmpty() {//O(1) check empty
    return size == 0;
}

template <typename T>
T ISortedList<T>::get(int i) {//O(n)
    if (i < 1 || i > size) return {};//return nothing if i not in 1..size

    current = first;

    while (--i > 0) { //O(n) find needed node
        current = current->next;
    }

    return current->data;
}

template <typename T>
int ISortedList<T>::indexOf(T item) {//O(n)
    current = first;
    int i = 1;

    while (current->data != item) {//check all items
        if (i == size) return {};// if item not from list then return nothing
        current = current->next;
        i++;
    }

    return i;
}

template <typename T>
ISortedList<T> ISortedList<T>::searchRange(T from, T to) {// O(n)

    ISortedList<T> res;
    if (from > to || to < first->data || from > last->data) return {};//handle edge 3 cases
    current = first;

    while (current->data < from) {//O(n) find first needed element
        current = current->next;
    }
    while (current->data <= to) {//O(n) find last needed element
        res.add(current->data);
        if (current == last) break;
        current = current->next;
    }
    return res;
}





int main() {
    ISortedList<pair<double, string>> item; // crate needed data

    string command, name;
    double price, price_2;
    char c;// fro read $ and #
    int n;


    cin >> n;

    for (int i = 0; i < n; i++) {//O(n^2) , read O(n)*opearions O(n)
        cin >> command; // read command

        if (command == "ADD") { //O(n) if add then read and add
            cin >> c >> price;
            getline(cin, name);
            item.add(make_pair(price, name));
        }

        if (command == "REMOVE") {//O(n) remove
            cin >> c >> price;
            getline(cin, name);
            item.remove(item.indexOf(make_pair(price, name)));
        }

        if (command == "LIST") {// O(n)
            cin >> c >> price >> c >> price_2;
            ISortedList<pair<double, string>> range = item.searchRange(make_pair(price, ""), make_pair(price_2, "z"));//O(n)
            //search from price,"" to price "z" , becasue "" is minimal value of string for this task and "z" max

            for (int j = 1; j <= range.size; j++) {//O(n)
                pair<double, string> _pair = range.get(j);

                if (j == range.size) cout << '$' << fixed << setprecision(2) << _pair.first << _pair.second; else//write data double in fromat xx.xx
                    cout << '$' << fixed << setprecision(2) << _pair.first << _pair.second << ", ";
            }


            cout << endl;
        }

    }



}






