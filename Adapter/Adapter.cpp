#include <iostream>

class ThreePhaseOutlet {
public:
	void doThreePhaseOutlet() {
		std::cout << "ThreePhaseOutlet PLUG IN." << std::endl;
	}
};

class TwoPhaseOutlet {
public:
	virtual void doPlug() = 0;
};

class OutletConverter :public TwoPhaseOutlet, public ThreePhaseOutlet {
public:
	void doPlug() {
		doConvertor();
		doThreePhaseOutlet();
	}

	void doConvertor() {
		std::cout << "Converting TwoPhaseOutlet from ThreePhaseOutlet..." << std::endl;
	}
};

//对象适配更加灵活
class OutletObjConvertor :public TwoPhaseOutlet {
public:
	OutletObjConvertor(ThreePhaseOutlet* pOut) :m_pOut(pOut) {

	}
	void doPlug() {
		doConvert();
		m_pOut->doThreePhaseOutlet();
	}
	void doConvert() {
		std::cout << "Converting a two-phase plug itself..." << std::endl;
	}
private:
	ThreePhaseOutlet* m_pOut;
};


int main(void) {
	TwoPhaseOutlet* pOutlet = new OutletConverter();
	pOutlet->doPlug();

	TwoPhaseOutlet* pTwoOutlet = new OutletObjConvertor(new ThreePhaseOutlet);
	pTwoOutlet->doPlug();
	return 0;
}