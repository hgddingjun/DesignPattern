#include <iostream>
#include <deque>
#include <stack>
using namespace std;

//用STL默认适配器完成将一个deque转化成stack

int main() {
	deque<int> myDeq(3, 100);
	stack<int> myStack;
	stack<int> myStack2(myDeq);
	std::cout << "myStack Size: " << (int)myStack.size() << std::endl;
	std::cout << "myStack2 Size: " << (int)myStack2.size() << std::endl;

	myStack2.pop();
	std::cout << "myStack2 Size: " << (int)myStack2.size() << std::endl;
	std::cout << "myStack2 top: " << (int)myStack2.top() << std::endl;
	return 0;
}