#include <iostream>

using namespace std;

template<typename K, typename V>
class _map { // map <K,V>
    public:
        K* key;
        V* value;
        int size; // size of K, V. need for doubling
        int count;//count of elements K, V

        _map() { // constructor, start values
            size = 1;
            key = new K[1];
            value = new V[1];
            count = 0;
        }

        ~_map() { //destrcutor
            delete[] key;
            delete[] value;
        }

        int find_key(K _key) { // O(n), find key position, if dont find then return -1
            for (int i = 0; i < count; i++) {
                if (key[i] == _key) return i;
            }
            return -1;
        }

        void put(K _key, V _value) {// (O(n) - because find_key, put <K,V> into map
            if (count >= size) {
                resize(size * 2);
            }

            int key_pos = find_key(_key);
            if (key_pos >= 0) {     //if key exist then add new value for keys value
                value[key_pos].add(_value);
            } else {
                count++;// if key not exist then add new <K,V>
                key[count - 1] = _key;
                value[count - 1] = _value;
            }

        }

        void get_keys(K* &array) {  // O(n)  get array of keys.pass an array to the argument, and change its value in the function
            K* _key;
            _key = new K[count];
            for (int i = 0; i < count; i++) {
                _key[i] = key[i];
            }
            array = _key;

        }

        void get_values(V* &array) {// O(n)  get array of values.pass an array to the argument, and change its value in the function
            V* _value;
            _value = new V[count];
            for (int i = 0; i < count; i++) {
                _value[i] = value[i];
            }
            array = _value;

        }

        private:
            void resize(int new_size) { //O(n) resize array, need for doubling
                K* _key;
                _key = new K[new_size];
                V* _value;
                _value = new V[new_size];

                for (int i = 0; i < size; i++) {
                    _key[i] = key[i];
                    _value[i] = value[i];
                }
                delete[] key;
                delete[] value;

                key = _key;
                value = _value;
                size = new_size;
            }


};

template<typename T>
class hash_table { // hash table with map implementation, <int, T>, where int - result of hash(String)
    public:
        _map<int, T> table;

        void add(string s, T item) {       //O(n) - because put add new item to hash table
            table.put(hash_str(s), item);
        }

    private:
        int hash_str(string S) { //O(length(S)) ~ O(1) - because string is small , hashing a string
            const char* s = S.c_str();
            int A = 13; //main argument
            int N = 50021; // 50000 - max size, 50021 prime number > 50000
            unsigned h = 31;
            unsigned q = A;
            while (*s) {    //algorithm for hashing
                h = h + s[0]*q ;
                s++;
                q *= A;
            }
            if ( h < 0) h *= -1;
            return h % N; //need values 0..50020
        }
};


struct cafe { // struct where stored one date, and array of data(time, ID, item ..) - all operation for this date. and store unic_ID
    string date, *time, *ID, *item, *unic_ID;
    double price, total_cost;
    int count, size, unic_size, unic_count;

    cafe() {// constructor
        count = unic_count = price = total_cost = 0;
        size = unic_size = 2;
        time = ID = item = unic_ID = new string[size];
    }

    void set(string _date, string _time, string _ID, string _item, double _price) {//O(1) // set first element - need if we want to store just 1 element
        date = _date;
        time[0] = _time;
        ID[0] = _ID;
        item[0] = _item;
        unic_ID[0] = _ID;
        price = total_cost = _price;
        count++;
        unic_count++;
    }

    void add (cafe const& right) {// O(n) need if we want to store mor ethan 1 element

        total_cost += right.total_cost; // calculate total cost

        for (int i = 0; i < right.count; i++) {//O(n) // add new elementf for this from right
            if (count + 1 >= size) {
                resize(ID, size, size * 2 + 1);
                resize(time, size, size * 2 + 1);
                resize(item, size, size * 2 + 1);
                size = size * 2 + 1;
            }

            time[count] = right.time[i];
            ID[count] = right.ID[i];
            item[count] = right.item[i];
            count++;
            bool cont = false;
            for (int j = 0; j < unic_count; j++) {//O(n)
                if (unic_ID[j] == right.ID[i]) { // check if this ID is unic, then store him to unic_ID
                    cont = true;
                }
            }
            if (cont) continue; // cont = true if unic else continue to next i

            if (unic_count + 1 >= unic_size) {
                resize(unic_ID, unic_size, unic_size * 2 + 1);//O(n) resize
                unic_size = unic_size * 2 + 1;
            }

            unic_ID[unic_count] = right.ID[i];
            unic_count++;

        }
    }


    private:
            template<typename t>
            void resize(t* &item, int sz, int new_size) {// O(n) slightly different resize implementation
                t *_item;
                _item = new t[new_size];
                for (int i = 0; i < sz; i++) {
                    _item[i] = item[i];
                }
                item = _item;
            }
};


int main() {

    int n; // count of elements
    string date, time, ID, item; // data for read
    double price;// data for read
    char c; // data for read # and $
    cin >> n;

    hash_table<cafe> _cafe;

    for (int i = 0; i < n; i++) {// O(n^2), read O(n) * add(O(n)
        cin >> date >> time >> c >> ID >> c >> price; getline(cin, item);// read data
        cafe x;
        x.set(date, time, ID, item, price); //O(1) create cafe with 1 element
        _cafe.add(date, x);//O(n) add it to hash table
    }
    int count = _cafe.table.count; //O(1) count of unic_days
    cafe* res;
    _cafe.table.get_values(res); //O(n) get all values, keys - different days
    for (int i = 0; i < count; i++) {// O(n)
        cout << res->date << " $" << res->total_cost << ' ' << res->unic_count << endl;// write data
        res++;
    }



}






