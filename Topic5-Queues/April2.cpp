#include <iostream>
#include <string>

#include<queue>

#include<cassert>



using std::cout; 
using std::cin; 
using std::endl; 
using std::string;

using std::queue;
using std::deque; 

template <typename T>
class QueueADT
{
public:
	virtual bool isEmpty() = 0;
	//Recall: this = 0 syntax will make queueADT abstract  
	virtual bool isFull() = 0;
	//It makes some sense to impose a limit on queue size.

	virtual T* front() = 0;
	//returns pointer to first element of queue 
	//"peek" is a common synonym for this function name 

	virtual T* back() = 0;
	//returns pointer to last element of queue 

	virtual void enqueue(const T& newValue) = 0;
	//adds newValue to the back of the queue
	//I would pronounce this in-KYOO (not “on cue”) 

	virtual void dequeue() = 0;
	//removes value from the front of the queue 
	//pronounced dee-KYOO (as in the fast food place)

	//enqueue and dequeue are similar to push and pop
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

	T* front() //T is also fine here (and omit ampersand)
	{
		return &(queueFront->info);
		//return &(queueFront->info);
	}

	T* back()
	{
		return &(queueBack->info);
	}

	int size() { return nodeCount; }


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

	//MyQueue(const MyQueue<T>& otherQueue) = delete;
	MyQueue(const MyQueue<T>& otherQueue)
	{
		queueFront = nullptr;
		queueBack = nullptr;
		nodeCount = 0; //updated by `enqueue` below 

		Node<T>* current = otherQueue.queueFront;
		while (current != nullptr)
		{
			enqueue(current->info);
			current = current->link;
		}
	}

};

template<typename T> 
queue<T> mergeQueues(queue<T> firstQueue,
	queue<T> secondQueue)
{
	queue<T> mergedQueue;

	while (!(firstQueue.empty() && secondQueue.empty()))
	{
		if (!firstQueue.empty())
		{
			mergedQueue.push(firstQueue.front());
			firstQueue.pop();
		}
		if (!secondQueue.empty())
		{
			mergedQueue.push(secondQueue.front());
			secondQueue.pop();
		}
	} //end while

	return mergedQueue;
}


template<typename T>
std::priority_queue<T> mergePriorityQueues(std::priority_queue<T> firstQueue,
	std::priority_queue<T> secondQueue)
{
	std::priority_queue<T> mergedQueue;

	while (!(firstQueue.empty() && secondQueue.empty()))
	{
		if (!firstQueue.empty())
		{
			mergedQueue.push(firstQueue.top());
			firstQueue.pop();
		}
		if (!secondQueue.empty())
		{
			mergedQueue.push(secondQueue.top());
			secondQueue.pop();
		}
	} //end while

	return mergedQueue;
}

int main()
{
	std::priority_queue<int> pq1;// = { 1, 3, 4 };
	pq1.push(1); 
	pq1.push(3);
	pq1.push(5);

	std::priority_queue<int> pq2;// = { 1, 3, 4 };
	pq2.push(2); 
	pq2.push(4);
	pq2.push(6);

	auto mergedQueue = mergePriorityQueues(pq1, pq2); 

	while (!mergedQueue.empty())
	{
		cout << mergedQueue.top() << endl; 
		mergedQueue.pop(); 
	}
	cout << "\n\n\n";

	//std::merge(pq1.)
	MyQueue <string> q1;
	q1.enqueue("Alice");
	q1.enqueue("Bob");
	q1.enqueue("Carol");

	MyQueue<string> q2{ q1 };

	q1.printQueue(); 
	q2.printQueue(); 

	q2.dequeue(); 

	//q1.printQueue(); 
	cout << "Q2 after dequeuing once (from q2): " << endl; 
	q2.printQueue(); 

	cout << "Q1 after dequeuing once from Q2: " << endl;
	q1.printQueue();


	//MyQueue<string> lane1; 
	//lane1.enqueue("Alice");
	//lane1.enqueue("Bob");

	//cout << *lane1.front() << endl; 

	deque<string> lane1; 
	//lane1.begin() //checking RandomAccessIterator type
	//deque<string> lane2;

	//lane1.push_back("Alice"); 
	//lane1.push_back("Cathy");

	//lane2.push_back("Bob");
	//lane2.push_back("Darth");

	//deque<string> mergedLane; 

	//std::merge(lane1.begin(), lane1.end(), lane2.begin(), lane2.end(), 
	//	std::back_inserter(mergedLane));

	////for (auto& customer : mergedLane)
	////{
	////	cout << customer << endl; 

	////}

	//queue<string> lane1Copy;
	//queue<string> lane2Copy;

	//lane1Copy.push("Alice");
	//lane1Copy.push("Cathy");

	//lane2Copy.push("Bob");
	//lane2Copy.push("Darth");

	//auto mergedLaneCopy = mergeQueues(lane1Copy, lane2Copy);
	//while(!mergedLaneCopy.empty())
	//{
	//	cout << mergedLaneCopy.front() << endl;
	//	mergedLaneCopy.pop(); 
	//}

	//std::queue<int> q; 
	
	//std::sort()


	return 0; 
}