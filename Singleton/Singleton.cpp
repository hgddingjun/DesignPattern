#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <mutex>
#ifdef __WIN_UITIL__
#include <afxwin.h>
#endif
//unsing namespace std;

std::mutex mtx;

class Singleton {
private:
	Singleton() {
		m_single = nullptr;
		std::cout << "Constructing Singleton..." << std::endl;
	}

private:
	static Singleton* m_single;

public:
	static Singleton* getInstance() {
		mtx.lock();
		if (m_single == nullptr) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			m_single = new Singleton;
		}
		mtx.unlock();
		return m_single;
	}
};

Singleton* Singleton::m_single = nullptr;

Singleton* tp1 = nullptr;
Singleton* tp2 = nullptr;
Singleton* tp3 = nullptr;
Singleton* tp4 = nullptr;
Singleton* tp5 = nullptr;

void TestThread1(void)
{
	tp1 = Singleton::getInstance();
	printf("TestThread1 tp1=0x%p\n", tp1);
}

void TestThread2(void)
{
	tp2 = Singleton::getInstance();
	printf("TestThread2 tp2=0x%p\n", tp2);
}

void TestThread3(void)
{
	tp3 = Singleton::getInstance();
	printf("TestThread3 tp3=0x%p\n", tp3);
}

void TestThread4(void)
{
	tp4 = Singleton::getInstance();
	printf("TestThread4 tp4=0x%p\n", tp4);
}

void TestThread5(void)
{
	tp5 = Singleton::getInstance();
	printf("TestThread5 tp5=0x%p\n", tp5);
}

#ifdef __WIN_UITIL__
UINT Func(LPVOID)
{
	printf("Func: print Singleton point: 0x%p\n", Singleton::getInstance());
	return 0;
}
#endif

int main(void)
{
#if 0
	Singleton* p1 = Singleton::getInstance();
	Singleton* p2 = Singleton::getInstance();
	printf("Singleton pointer p1=0x%p, p2=0x%p\n", p1, p2);

#else
	std::thread t1(TestThread1);
	std::thread t2(TestThread2);
	std::thread t3(TestThread3);
	std::thread t4(TestThread4);
	std::thread t5(TestThread5);

	std::cout << "Thread[1...5] now execute concurrently..." << std::endl;

	//sync threads.
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();

	std::cout << "Thread[1...5] execute completed." << std::endl;

#ifdef __WIN_UITIL__
	for (int i = 0; i < 10; i++) {
		AfxBeginThread(Func, nullptr);
	}
#endif/*__WIN_UITIL__*/

#endif
	return 0;
}
