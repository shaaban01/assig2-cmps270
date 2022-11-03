#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Stack
{
public:
    template <typename O>
    friend Stack<O> operator+(Stack<O> &c1, Stack<O> &c2);

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
    void pop();

    // require:
    //     nothing
    // effect:
    //     will return the top element of the stack
    //     if the stack is empty then return the top element of the stack which will be 0
    T top();

private:
    vector<T> v;
};

// ----------------------------------------------------------------
// ----------------------------------------------------------------

template <typename T>
Stack<T>::Stack()
{
    vector<T> st;
    v = st;
}

template <typename T>
Stack<T>::~Stack()
{
    v.clear();
}

// ----------------------------------------------------------------

template <typename T>
bool Stack<T>::empty()
{
    return v.empty();
}

// ----------------------------------------------------------------

template <typename T>
void Stack<T>::push(T key)
{

    v.push_back(key);
}

// ----------------------------------------------------------------

template <typename T>
void Stack<T>::pop()
{
    // checking if the stack is empty
    if (empty())
    {
        cout << "ERROR: Stack is empty!" << endl;
    }
    v.pop_back();
}

// ----------------------------------------------------------------

template <typename T>
T Stack<T>::top()
{
    return v[v.size() - 1];
}

// ----------------------------------------------------------------

template <typename O>
Stack<O> operator+(Stack<O> &c1, Stack<O> &c2)
{

    Stack<O> result;
    for (O o : c1.v)
        result.v.push_back(o);
    for (O o : c2.v)
        result.v.push_back(o);

    // }'
    return result;
}

// ----------------------------------------------------------------
// ----------------------------------------------------------------

// a test driver for stack
int main(int argc, char const *argv[])
{
    Stack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    stack1.push(4);
    stack1.push(5);
    stack1.push(6);

    Stack<int> stack2;
    stack2.push(7);
    stack2.push(8);
    stack2.push(9);
    stack2.push(10);
    stack2.push(11);

    // cout << "stack1: " << stack1.top() << endl;
    // cout << "stack2: " << stack2.top() << endl;

    Stack<int> stack3;
    stack3 = stack1 + stack2;
    while (!stack3.empty())
    {
        cout << stack3.top() << endl;
        stack3.pop();
    }

    // cout << stack1.top() << endl;
    // cout << stack1.empty() << endl;
    // cout << stack1.pop() << endl;
    // cout << stack1.top() << endl;
    // cout << stack1.pop() << endl;
    // cout << stack1.pop() << endl;
    // cout << stack1.empty() << endl;
}
