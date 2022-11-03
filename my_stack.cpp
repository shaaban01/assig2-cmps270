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

// ----------------------------------------------------------------
// ----------------------------------------------------------------

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

// ----------------------------------------------------------------

template <typename T>
bool Stack<T>::empty()
{
    if (topIndex == -1)
        return true;
    return false;
}

// ----------------------------------------------------------------

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

// ----------------------------------------------------------------

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

// ----------------------------------------------------------------

template <typename T>
T Stack<T>::top()
{
    return v[topIndex];
}

// ----------------------------------------------------------------

template <typename O>
Stack<O> operator+(Stack<O> &c1, Stack<O> &c2)
{
    Stack<O> temp;
    temp.v = c2.v;
    temp.topIndex = c2.topIndex;
    Stack<O> result;
    result.v = c1.v;
    result.topIndex = c1.topIndex;
    for (int i = 0; i < temp.topIndex; i++)
    {
        cout << "result: " << result.top() << endl;
        cout << "temp: " << temp.top() << endl;
        result.push(temp.pop());
        cout << "result: " << result.top() << endl;
        cout << "temp: " << temp.top() << endl;
    }
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

    Stack<int> stack3;
    stack3 = stack1 + stack2;
    cout << stack3.pop() << endl;
    cout << stack3.pop() << endl;
    cout << stack3.pop() << endl;
    cout << stack3.pop() << endl;
    cout << stack3.pop() << endl;
    cout << stack3.pop() << endl;
    cout << stack3.pop() << endl;

    // cout << stack1.top() << endl;
    // cout << stack1.empty() << endl;
    // cout << stack1.pop() << endl;
    // cout << stack1.top() << endl;
    // cout << stack1.pop() << endl;
    // cout << stack1.pop() << endl;
    // cout << stack1.empty() << endl;
}
