#include <iostream>

#include<algorithm>

#include<queue>

#include<cassert>

using namespace std;

template <typename T>
class QueueADT
{
public:
    virtual bool isEmpty() = 0;
    //Recall: this = 0 syntax will make queueADT abstract
    virtual bool isFull() = 0;

    virtual T front() = 0;
    //returns pointer to first element of queue
    //"peek" is a common synonym for this function name
    virtual T* back() = 0;

    virtual void enqueue(const T& newValue) = 0;

    virtual void dequeue() = 0;

};

template <typename T>
struct Node
{
    T info;
    Node<T>* link; 
};

template <typename T>
class MyQueue : public QueueADT<T>
{

private:
    Node<T>* queueFront;
    Node<T>* queueBack;
    int nodeCount;


public:
    MyQueue()
    {
        queueFront = nullptr;
        queueBack = nullptr;
        nodeCount = 0;
    }

    //MyQueue(T dataToInsert, int numberOfInitialNodes)

    bool isEmpty() override //override is optional but recommended
    {
        return (queueFront == nullptr);
    }

    bool isFull()
    {
        return false; //dynamic memory -> “infinite” queue length
        //add capacity as member var, if desired
        //required if making queue from static array
    }

    T front() //T is also fine here (and omit ampersand)
    {
        return queueFront->info;
    }

    T* back()
    {
        return &(queueBack->info);
    }

    void printQueue()
    {
        Node<T>* current = new Node<T>;
        current = queueFront;
        for (int i = 0; i < nodeCount; i++)
        {
            cout << current->info << endl;
            current = current->link;
        }
    }

    void enqueue(const T& newValue)
    {
        Node<T>* newNode = new Node<T>;
        newNode->info = newValue;
        newNode->link = nullptr;

        if (isEmpty()) //true if inserting first queue element
        {
            queueFront = newNode;
            queueBack = newNode;
        }
        else
        {
            queueBack->link = newNode;//see figure on next slide
            queueBack = queueBack->link;
        }
        nodeCount++;   
    }

    void dequeue()
    {
        assert(!isEmpty());
        Node<T>* temp = queueFront;
        queueFront = queueFront->link;
        delete temp;
        nodeCount--;
    }


};



int main()
{
    //queue<string> q; 
  
    

    MyQueue<string> lane1Customers; 

    lane1Customers.enqueue("Alice");
    lane1Customers.enqueue("Bob"); //the typical names of "crypotgraphic actors" 
    lane1Customers.enqueue("Carol"); 

    lane1Customers.printQueue(); 
    
    lane1Customers.dequeue(); 
    cout << "\n\nAfter dequeueing ONCE: " << endl; 
    lane1Customers.printQueue(); 


    cout << "Back returns: " << *lane1Customers.back() << endl; 
    cout << "Front returns: " << lane1Customers.front() << endl; 
    //QueueADT<string> q; 

    
    //std::merge()
    //cout << "Hello World";

    return 0;
}