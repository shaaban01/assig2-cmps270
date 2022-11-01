#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Stack
{
public:
    // Stack constructor
    Stack();

    // Stack destructor
    ~Stack();

    // a function that check if the stack is empty
    // require:
    //     nothing
    // effect:
    //     return true if the stack is empty
    //     return false if the stack is not empty
    bool empty();

    // push function
    // require:
    //     a key of type T(any type)
    // effect:
    //     push a new element to the top of the stack
    void push(T);

    // pop function
    // require:
    //     nothing
    // effect:
    // if the stack is empty then return empty T with an error message
    // otherwise return the top element of the stack and remove it from the stack
    T pop();

    // require:
    //     nothing
    // effect:
    //     will return the top element of the stack
    //     if the stack is empty then return the top element of the stack which will be 0
    T top();

private:
    vector<T> v;
    int topIndex;
};

template <typename T>
Stack<T>::Stack()
{
    vector<T> st(1);
    v = st;
    topIndex = -1;
}

template <typename T>
Stack<T>::~Stack()
{
    v.clear();
}

template <typename T>
bool Stack<T>::empty()
{
    if (topIndex == -1)
        return true;
    return false;
}

template <typename T>
void Stack<T>::push(T key)
{
    // doubling the stack size to avoid overflow
    if (topIndex + 1 >= v.size())
    {
        v.resize(2 * topIndex);
    }

    // adding the key to the stack
    v[++topIndex] = key;
}

template <typename T>
T Stack<T>::pop()
{
    // checking if the stack is empty
    if (empty())
    {
        cout << "ERROR: Stack is empty!" << endl;
        return T();
    }

    // To remove top
    T key = v[topIndex--];

    // resize the stack if it is more than half empty to save memory
    if (topIndex < (v.size() / 2))
    {
        v.resize(v.size() / 2);
    }

    // return the top
    return key;
}

template <typename T>
T Stack<T>::top()
{
    return v[topIndex];
}

// a test driver for stack
int main(int argc, char const *argv[])
{
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    cout << stack.top() << endl;
    cout << stack.empty() << endl;
    cout << stack.pop() << endl;
    cout << stack.top() << endl;
    cout << stack.pop() << endl;
    cout << stack.pop() << endl;
    cout << stack.empty() << endl;
}
