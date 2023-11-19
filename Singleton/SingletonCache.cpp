#include <cstdio>
#include <iostream>
#include <map>
using namespace std;

class Singleton;
std::map<int, Singleton*> myMap = std::map<int, Singleton*>();

class Singleton {
private:
	Singleton() {
		m_single = nullptr;
		std::cout << "Constructing Singleton..." << std::endl;
	}
private:
	static Singleton* m_single;
	static int m_InstanceCount;
public:
	static Singleton* getInstance() {
		m_single = myMap[m_InstanceCount];
		if (m_single == nullptr) {
			m_single = new Singleton;
			myMap[m_InstanceCount] = m_single;
		}
		m_InstanceCount++;
		if (m_InstanceCount > 5) {
			m_InstanceCount = 1;
		}
		return m_single;
	}
};

Singleton* Singleton::m_single = nullptr;
int Singleton::m_InstanceCount = 1;

int main(void)
{
	Singleton* p1 = Singleton::getInstance();
	Singleton* p2 = Singleton::getInstance();
	Singleton* p3 = Singleton::getInstance();
	Singleton* p4 = Singleton::getInstance();
	Singleton* p5 = Singleton::getInstance();

	printf("p1=0x%p,p2=0x%p,p3=0x%p,p4=0x%p,p5=0x%p\n", p1,p2,p3,p4,p5);


	Singleton* p6 = Singleton::getInstance();
	Singleton* p7 = Singleton::getInstance();
	Singleton* p8 = Singleton::getInstance();
	Singleton* p9 = Singleton::getInstance();
	Singleton* p10 = Singleton::getInstance();

	printf("p6=0x%p,p7=0x%p,p8=0x%p,p9=0x%p,p10=0x%p\n", p6, p7, p8, p9, p10);
	return 0;
}