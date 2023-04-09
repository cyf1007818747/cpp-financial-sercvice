#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   public: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache: public Cache {
public: 
    LRUCache(int capacity) {
        cp = capacity;
    }
    
    void set(int key, int value) override {
        // the case that the key is in the cache
        if (mp.count(key)) {
            // make c curr pointer and makes it point to the node of this key
            Node* curr = mp[key];
            // update the value of the node
            // cout << "curr->value before: " << curr->value << endl;
            curr->value = value;
            // cout << "curr->value after: " << curr->value << endl;
            // move the curr node to the head of the list
            if (curr != tail && curr != head) {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                curr->prev = nullptr;
                curr->next = head;
                head->prev = curr;
                head = curr;
            } else if (curr == tail && curr != head) {
                curr->prev->next = nullptr;
                tail = curr->prev; // move it to later pos
                curr->next = head;
                curr->prev = nullptr;
                head->prev = curr;
                head = curr;
            }
        } else {
            // update the linked list
            // Node node(nullptr, head, key, value);
            Node* new_node = new Node(nullptr, head, key, value);
            // add to map
            mp[key] = new_node;
            // cout << "new_node->value: " << new_node->value << endl;
            // cout << "mp[key]->value: " << mp[key]->value << endl;
            if (head != nullptr) {
                head->prev = new_node;
                head = new_node;
            } else {
                head = new_node;
            }
            if (tail == nullptr) {
                tail = new_node;
            }
            // check capacity
            if (mp.size() >= cp) {
                int temp_key = tail->key;
                tail = tail->prev;
                tail->next = nullptr;
                delete mp[temp_key];
                mp.erase(temp_key);
            }
        }
    }
    
    int get(int key) override {
        // the case that the key is in the cache
        if (mp.count(key)) {
            // make c curr pointer and makes it point to the node of this key
            Node* curr = mp[key];
            // move the curr node to the head of the list
            if (curr != tail && curr != head) {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                curr->prev = nullptr;
                curr->next = head;
                head->prev = curr;
                head = curr;
            } else if (curr == tail && curr != head) {
                curr->prev->next = nullptr;
                tail = curr->prev; // move it to later pos
                curr->next = head;
                curr->prev = nullptr;
                head->prev = curr;
                head = curr;
            }
            return mp[key]->value;
        } else {
            return -1;
        }
    }

    map<int,Node*>* get_map() {
        return &mp;
    }
};

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
        string command;
        cin >> command;
        if(command == "get") {
            int key;
            cin >> key;
            cout << l.get(key) << endl;
        } 
        else if(command == "set") {
            int key, value;
            cin >> key >> value;
            l.set(key,value);
        }
        auto map = l.get_map();
        for (const auto& pair : *map) {
            cout << "Key: " << pair.first << ", Value: " << pair.second->value << endl;
        }
        cout << "head: " << l.head->value << ", tail: " << l.tail->value << endl;
   }
   return 0;
}

/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 hrank_practice/lcu_cache.cpp -o .bin/hrank_practice@@lcu_cache.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/hrank_practice@@lcu_cache.bin
*/