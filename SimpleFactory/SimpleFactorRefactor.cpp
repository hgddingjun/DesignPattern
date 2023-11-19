#include <iostream>
#include <string>
#include "DynObj.h"
using namespace std;

class Api {
public:
	virtual void test(string s) = 0;
protected:
	Api(){}
};

class ImpleOne : public Api {
public:
	void test(string s) {
		cout << s <<"->One is running now." << endl;

	}
};


class ImpleTwo : public Api {
public:
	void test(string s) {
		cout << s << "->Two is running now." << endl;
	}
};


class Factory {
public:
	static Api* createApi(int type) {
		Api* pApi = nullptr;
		if (type == 1){
			pApi = new ImpleOne();
		}

		if (type == 2) {
			pApi = new ImpleTwo();
		}
		return pApi;
	}
};


#define IMPL_NAME ImpleOne //传入自动工厂类的类名，在REG_CLASS中保持一致

class AutoFactory {
public:
	static Api* createApi() {
		Api* pApi = nullptr;
		pApi = static_cast<Api*>(CObjectFactory::createObject("IMPL_NAME"));
		return pApi;
	}
};

REG_CLASS(IMPL_NAME);
int main()
{

	Api* pApi1 = Factory::createApi(1);
	Api* pApi2 = Factory::createApi(2);
	pApi1->test("using api1");
	pApi2->test("using api2");

	Api* pApi = AutoFactory::createApi();
	pApi->test("Hide all detail complete");
	return 0;
}