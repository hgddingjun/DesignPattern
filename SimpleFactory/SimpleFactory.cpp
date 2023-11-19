#include <iostream>
#include <string>
using namespace std;

class Api {
public:
	virtual void test(string s) = 0;
protected:
	Api(){}
};

class Impl : public Api {
public:
	void test(string) {
		cout << "test Impl class now,executing..." << endl;
	}
};

int main(void)
{
	Api* pApi = new Impl();
	pApi->test("test running...\n");

	return 0;
}