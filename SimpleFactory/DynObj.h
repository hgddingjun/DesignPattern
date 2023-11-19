
#ifndef _DYNOBJ_H_
#define _DYNOBJ_H_

#include <string>
#include <map>

typedef void* (*Constructor)();

class CObjectFactory {
public:
	static void registerClass(std::string className, Constructor constructor) {
		constructors()[className] = constructor;
	}

	static void* createObject(const std::string& className) {
		Constructor constructor = nullptr;
		if (constructors().find(className) != constructors().end()) {
			constructor = constructors().find(className)->second;
		}

		if (constructor == nullptr)
			return nullptr;

		return (*constructor)();
	}
private:
	//string->key:动态创建类名
	inline static std::map<std::string, Constructor>& constructors() {
		static std::map<std::string, Constructor> instance;
		return instance;
	}
};

#define REG_CLASS(_name) \
class _name##Helper{ \
public: \
	_name##Helper() { \
		CObjectFactory::registerClass(#_name, _name##Helper::createObjFunc); \
	} \
	static void* createObjFunc() { \
		return new _name; \
	} \
};\
_name##Helper _name##Helper;

#endif