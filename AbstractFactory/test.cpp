#include <iostream>
#include <string>

class TestString {
public:
	TestString(std::string str):m_string(str) {
		std::cout << "Test String is:" << str << std::endl;
	}
private:
	std::string m_string;
};
int main(void) {
	TestString gString("2560x1440");
	return 0;
}