#include <iostream>
#include <cstdio>
#include <string>


class ExportFileApi {
public:
	virtual bool exportData(std::string data)=0;
protected:
	ExportFileApi(){}
};

class ExportTxtFile : public ExportFileApi {
public:
	bool exportData(std::string data) {
		std::cout << "Exporting data: " << data << " to csv file" << std::endl;
		return true;
	}
};

class ExportDB : public ExportFileApi {
public:
	bool exportData(std::string data) {
		std::cout << "Exporting data to " << data << " Database." << std::endl;
		return true;
	}
};

class ExportOperate {
public:
	bool exportData(std::string data) {
		ExportFileApi* pApi = factoryMethod();
		return pApi->exportData(data);
	}
protected:
	virtual ExportFileApi* factoryMethod() = 0;
};


class ExportTxtFileOperate : public ExportOperate {
protected:
	ExportFileApi* factoryMethod() {
		return new ExportTxtFile();
	}
};

class ExportDBOperate : public ExportOperate {
protected:
	ExportFileApi* factoryMethod() {
		return new ExportDB();
	}
};

int main(void)
{
	ExportOperate* pOperate = new ExportTxtFileOperate();
	pOperate->exportData("Haha");
	return 0;
}