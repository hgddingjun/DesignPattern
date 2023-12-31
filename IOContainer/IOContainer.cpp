#include <string>
#include <iostream>
#include <functional>
#include <map>
#include <memory>

template <class T>
class IocContainer {
public:
	IocContainer() {

	}
	~IocContainer()
	{

	}

	//注册需要创建对象的构造函数，通过一个唯一的标识，以便以后查找
	template <class Drived>
	void RegisterType(std::string strKey) {
		std::function<T* ()> function = [] {
			return new Drived();
		};
		RegisterType(strKey, function);
	}
	
	//根据唯一的标识去查找对应的构造函数
	T* Resolve(std::string strKey) {
		if (m_createMap.find(strKey) == m_createMap.end())
			return nullptr;
		std::function<T* ()> function = m_createMap[strKey];
		return function();
	}

	//创建智能指针
	std::shared_ptr<T> ResolveShared(std::string strKey) {
		T* ptr = Resolve(strKey);
		return std::shared_ptr<T>(ptr);
	}

private:
	void RegisterType(std::string strKey, std::function<T* ()> creator) {
		if (m_createMap.find(strKey) != m_createMap.end()) {
			throw std::invalid_argument("Already exsit this Key!");
		}
		m_createMap.emplace(strKey, creator);
	}

private:
	std::map<std::string, std::function<T* ()>> m_createMap;
};

struct ICar {
	virtual ~ICar(){}
	virtual void test() const = 0;
};

struct Bus : ICar {
	Bus(){}
	void test() const {
		std::cout << "Bus::test()" << std::endl;
	}
};


struct Track : ICar {
	Track() {}
	void test() const {
		std::cout << "Track::test()" << std::endl;
	}
};
int main(void)
{
	IocContainer<ICar> carIOC;
	carIOC.RegisterType<Bus>("bus");
	carIOC.RegisterType<Track>("track");

	std::shared_ptr<ICar> bus = carIOC.ResolveShared("bus");
	bus->test();

	std::shared_ptr<ICar> track = carIOC.ResolveShared("track");
	track->test();
	return 0;
}