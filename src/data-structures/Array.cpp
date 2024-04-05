#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Array {
    private:
        vector<T> elements;
    
    public:
        bool isEmpty() const {
            return elements.empty();
        }

        void push(const T& item){
            elements.push_back(item);
        }

        T pop() {
            if (isEmpty()) {
                throw runtime_error("A pilha está vazia");
            }

            T topElement = elements.back();
            elements.pop_back();
            return topElement;
        }

        T peek() const {
            if (isEmpty()) {
                throw runtime_error("A pilha está vazia");
            }

            return elements.back();
        }
};