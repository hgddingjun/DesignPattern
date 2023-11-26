#include <iostream>
#include <string>

class OrderApi {
public:
	virtual int getOrderProductNum() const = 0;
	virtual void setOrderProductNum(int num) = 0;
	virtual std::string getOrderContent() = 0;
	virtual OrderApi* cloneOrder() = 0;

protected:
	OrderApi() {}
};

class HomeOrder : public OrderApi {
public:
	int getOrderProductNum() const {
		return m_orderProductNum;
	}
	void setOrderProductNum(int num) {
		m_orderProductNum = num;
	}
	std::string getOrderContent() {
		return "Custom is:" + m_strCustomName + ", Order ID:" + m_strProductId + ", Number:" + std::to_string(m_orderProductNum) + "\n";
	}

	void setCustomName(std::string name) {
		m_strCustomName = name;
	}

	std::string getCustomName() const {
		return m_strCustomName;
	}

	void setProductId(std::string id) {
		m_strProductId = id;
	}

	std::string getProductId() const {
		return m_strProductId;
	}

	OrderApi* cloneOrder() {
		HomeOrder* pOrder = new HomeOrder;
		pOrder->setCustomName(m_strCustomName);
		pOrder->setProductId(m_strProductId);
		pOrder->setOrderProductNum(m_orderProductNum);

		return pOrder;
	}
private:
	std::string m_strCustomName;
	std::string m_strProductId;
	int m_orderProductNum;
};



class AboardOrder : public OrderApi {
public:
	int getOrderProductNum() const {
		return m_orderProductNum;
	}
	void setOrderProductNum(int num) {
		m_orderProductNum = num;
	}
	std::string getOrderContent() {
		return "Custom is:" + m_strCustomName + ", Order ID:" + m_strProductId + ", Number:" + std::to_string(m_orderProductNum) + "\n";
	}

	void setCustomName(std::string name) {
		m_strCustomName = name;
	}

	std::string getCustomName() const {
		return m_strCustomName;
	}

	void setProductId(std::string id) {
		m_strProductId = id;
	}

	std::string getProductId() const {
		return m_strProductId;
	}

	OrderApi* cloneOrder() {
		AboardOrder* pOrder = new AboardOrder;
		pOrder->setCustomName(m_strCustomName);
		pOrder->setProductId(m_strProductId);
		pOrder->setOrderProductNum(m_orderProductNum);

		return pOrder;
	}
private:
	std::string m_strCustomName;
	std::string m_strProductId;
	int m_orderProductNum;
};


class OrderBusiness {
public:
	void saveOrder(OrderApi* pOrder);
};

void OrderBusiness::saveOrder(OrderApi* pOrder) {

	while (pOrder->getOrderProductNum() > 200) {
		OrderApi* pNewOrder = pOrder->cloneOrder();
		pNewOrder->setOrderProductNum(200);

		pOrder->setOrderProductNum(pOrder->getOrderProductNum() - 200);
		std::cout << "New Order->" << pNewOrder->getOrderContent() << std::endl;
	}
	std::cout << "Final Order->" << pOrder->getOrderContent() << std::endl;
}

int main(void)
{
	HomeOrder* pHome = new HomeOrder;
	pHome->setOrderProductNum(512);
	pHome->setCustomName("Alpha-Ting");
	pHome->setProductId("C++designpattern-4-Prototype");
	OrderBusiness* pOb = new OrderBusiness();
	pOb->saveOrder(pHome);
	return 0;
}