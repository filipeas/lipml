#include <iostream>

using namespace std;

template<typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& d){
        data = d;
        next = nullptr;
    }
};

template<typename T>
class LinkedList {
    private:
        Node<T>* head;
    
    public:
        LinkedList() {
            head = nullptr;
        }

        void append(const T& data) {
            Node<T>* newNode = new Node<T>(data);
            if (!head) {
                head = newNode;
                return;
            }

            Node<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }

            temp->next = newNode;
        }

        void print() const {
            Node<T>* temp = head;
            while (temp) {
                cout << temp->data << " ";
                temp = temp->next;
            }

            cout << endl;
        }

        ~LinkedList() {
            Node<T>* temp;
            while (head) {
                temp = head->next;
                delete head;
                head = temp;
            }
        }
};