#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

template <class T>
std::string ConvertToString(T v) {
	stringstream ss;
	ss << v;
	return ss.str();
}

class ExportHeaderModel {
public:
	ExportHeaderModel(std::string strDepId, std::string strExportDate)
		: m_strDepId(strDepId), m_strExportDate(strExportDate) {
	}

	std::string getDepID() const {
		return m_strDepId;
	}

	std::string getExportDate() const {
		return m_strExportDate;
	}
private:
	std::string m_strDepId;
	std::string m_strExportDate;
};

class ExportDataModel {
public:
	ExportDataModel(std::string strTransId, double Quantity)
		: m_strTransId(strTransId), m_Quantity(Quantity) {
	}

	std::string getTransId() const {
		return m_strTransId;
	}

	double getQuantity() const {
		return m_Quantity;
	}
private:
	std::string m_strTransId;
	double m_Quantity;
};


class ExportFooterModel {
public:
	ExportFooterModel(std::string exportUser)
		: m_exportUser(exportUser) {
	}

	std::string getExportUser() const {
		return m_exportUser;
	}
private:
	std::string m_exportUser;
};


class ExporttoTxtHelper {
public:
	void doExport(ExportHeaderModel& ehm, vector<ExportDataModel*>& edmCollection, ExportFooterModel& efm);
};

void ExporttoTxtHelper::doExport(ExportHeaderModel& ehm, vector<ExportDataModel*>& edmCollection, ExportFooterModel& efm) {
	std::string strTemp = "";

	strTemp += ehm.getDepID() + "," + ehm.getExportDate() + "\n";
	for (vector<ExportDataModel*>::iterator iter = edmCollection.begin(); iter != edmCollection.end(); ++iter) {
		strTemp += (*iter)->getTransId() + ":" + std::to_string((*iter)->getQuantity()) + "\n";
	}

	strTemp += efm.getExportUser() + "\n";

	std::cout << strTemp << std::endl;
}



class ExportToXmlHelper {
public:
	void doExport(ExportHeaderModel& ehm, vector<ExportDataModel*>& edmCollection, ExportFooterModel& efm);
};

void ExportToXmlHelper::doExport(ExportHeaderModel& ehm, vector<ExportDataModel*>& edmCollection, ExportFooterModel& efm) {
	std::string strTemp = "";
	strTemp.append("<?xml version=\"1.0\" encoding=\"UTF - 8\"?>");
	strTemp.append("<Receipt>\n");
	strTemp.append("    <Header>\n");
	strTemp.append("        <DepID>" + ehm.getDepID() + "</DepID>\n");
	strTemp.append("        <ExportDate>" + ehm.getDepID() + "</ExportDate>\n");
	strTemp.append("    </Header>\n");

	strTemp.append("    <Body>\n");
	for (vector<ExportDataModel*>::iterator iter = edmCollection.begin(); iter != edmCollection.end(); ++iter) {
		strTemp.append("        <ID>" + (*iter)->getTransId() + "</ID>\n");
		strTemp.append("        <amount>" + std::to_string((*iter)->getQuantity()) + "</amount>\n");
	}
	strTemp.append("    </Body>\n");

	strTemp.append("    <Footer>\n");
	strTemp.append("        <ExportUser>" + efm.getExportUser() + "</ExportUser>\n");
	strTemp.append("    </Footer>\n");

	strTemp.append("</Receipt>\n");

	std::cout << strTemp << std::endl;

}

/******如下是使用builder模式实现该项目******/

class Builder {
public:
	virtual void  builderHeader(ExportHeaderModel& ehm) = 0;
	virtual void  builderBody(vector<ExportDataModel*>& edmCollection) = 0;
	virtual void  builderFoot(ExportFooterModel& efm) = 0;
	virtual std::string  getStringResult() const = 0;
protected:
	Builder() {}
};

class TxtBuilder : public Builder {
public:
	TxtBuilder() {
		m_strResult = "";
	}
	void  builderHeader(ExportHeaderModel& ehm) {
		m_strResult.append(ehm.getDepID() + "," + ehm.getExportDate() + "\n");
	}
	void  builderBody(vector<ExportDataModel*>& edmCollection) {
		for (vector<ExportDataModel*>::iterator iter = edmCollection.begin(); iter != edmCollection.end(); ++iter) {
			m_strResult += (*iter)->getTransId() + ":" + std::to_string((*iter)->getQuantity()) + "\n";
		}
	}
	void builderFoot(ExportFooterModel& efm) {
		m_strResult.append(efm.getExportUser() + "\n");
	}

	std::string  getStringResult() const {
		return m_strResult;
	}
private:
	std::string m_strResult;
};



class XMLBuilder : public Builder {
public:
	XMLBuilder() {
		m_strResult = "";
	}
	void  builderHeader(ExportHeaderModel& ehm) {
		m_strResult.append("<?xml version=\"1.0\" encoding=\"UTF - 8\"?>");
		m_strResult.append("<Receipt>\n");
		m_strResult.append("    <Header>\n");
		m_strResult.append("        <DepID>" + ehm.getDepID() + "</DepID>\n");
		m_strResult.append("        <ExportDate>" + ehm.getDepID() + "</ExportDate>\n");
		m_strResult.append("    </Header>\n");
	}
	void  builderBody(vector<ExportDataModel*>& edmCollection) {
		m_strResult.append("    <Body>\n");
		for (vector<ExportDataModel*>::iterator iter = edmCollection.begin(); iter != edmCollection.end(); ++iter) {
			m_strResult.append("        <ID>" + (*iter)->getTransId() + "</ID>\n");
			m_strResult.append("        <amount>" + std::to_string((*iter)->getQuantity()) + "</amount>\n");
		}
		m_strResult.append("    </Body>\n");


	}
	void builderFoot(ExportFooterModel& efm) {
		m_strResult.append("    <Footer>\n");
		m_strResult.append("        <ExportUser>" + efm.getExportUser() + "</ExportUser>\n");
		m_strResult.append("    </Footer>\n");

		m_strResult.append("</Receipt>\n");
	}

	std::string  getStringResult() const {
		return m_strResult;
	}
private:
	std::string m_strResult;
};



class Director {
public:
	Director(Builder* pBuilder) : m_pBuilder(pBuilder) {}
	void Construct(ExportHeaderModel& ehm, vector<ExportDataModel*>& edmCollection, ExportFooterModel& efm) {
		m_pBuilder->builderHeader(ehm);
		m_pBuilder->builderBody(edmCollection);
		m_pBuilder->builderFoot(efm);
	}
private:
	Builder* m_pBuilder;
};




int main(void) {
	std::string disp("建造者模式示例:\n");
	std::cout << disp << std::endl;

	ExportHeaderModel* pEhm = new ExportHeaderModel("北京1支行", "6月1日");
	ExportDataModel* pEdm1 = new ExportDataModel("1", 10000.135);
	ExportDataModel* pEdm2 = new ExportDataModel("2", 20000.246);

	vector<ExportDataModel*> myVec;
	myVec.push_back(pEdm1);
	myVec.push_back(pEdm2);

	ExportFooterModel* pEfm = new ExportFooterModel("李世民");

	std::cout << "文本格式如下:" << std::endl;
	ExporttoTxtHelper helper;
	helper.doExport(*pEhm, myVec, *pEfm);

	std::cout << "XML格式如下:" << std::endl;
	ExportToXmlHelper xmlHelper;
	xmlHelper.doExport(*pEhm, myVec, *pEfm);

	std::cout << "******如下是使用builder模式实现该项目******\n" << std::endl;

	Builder* pBuilder = new TxtBuilder();
	Director* pDirector = new Director(pBuilder);
	pDirector->Construct(*pEhm, myVec, *pEfm);
	std::cout << pBuilder->getStringResult() << std::endl;

	Builder* pBuilder2 = new XMLBuilder();
	Director* pDirector2 = new Director(pBuilder2);
	pDirector2->Construct(*pEhm, myVec, *pEfm);
	std::cout << pBuilder2->getStringResult() << std::endl;
	return 0;
}