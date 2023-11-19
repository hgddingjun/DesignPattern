#include <iostream>
#include <string>

class FrameApi {
public:
	virtual void draw() = 0;
protected:
	FrameApi() {}
};

class LayoutApi {
public:
	virtual void installFrame() = 0;
protected:
	LayoutApi() {}
};

class ComputerFrame : public FrameApi {
public:
	ComputerFrame(std::string pins) : m_pins(pins) {}
	void draw() {
		std::cout << "AbstractFactory-> Computer frame now, resolution is:" << m_pins << std::endl;
	}
private:
	std::string m_pins;
};


class MobileFrame : public FrameApi {
public:
	MobileFrame(std::string pins) : m_pins(pins) {}
	void draw() {
		std::cout << "AbstractFactory-> Mobile frame now, resolution is:" << m_pins << std::endl;
	}
private:
	std::string m_pins;
};


class ComputerLayout : public LayoutApi {
public:
	ComputerLayout(std::string FrameAdpaterPins) : m_FrameAdpaterPins(FrameAdpaterPins) {}
	void installFrame() {
		std::cout << "AbstractFactory-> Computer environment:" << m_FrameAdpaterPins << std::endl;
	}
private:
	std::string m_FrameAdpaterPins;
};


class MobileLayout : public LayoutApi {
public:
	MobileLayout(std::string FrameAdpaterPins) : m_FrameAdpaterPins(FrameAdpaterPins) {}
	void installFrame() {
		std::cout << "AbstractFactory-> Mobile environment:" << m_FrameAdpaterPins << std::endl;
	}
private:
	std::string m_FrameAdpaterPins;
};


class AbstractFactory {
public:
	virtual FrameApi* createFrameApi() = 0;
	virtual LayoutApi* createLayoutApi() = 0;
protected:
	AbstractFactory(){}
};

class Schemal1 : public AbstractFactory {
public:
	FrameApi* createFrameApi() {
		return new ComputerFrame("2560x1440");
	}
	LayoutApi* createLayoutApi() {
		return new ComputerLayout("2560x1440");
	}
};

class Schemal2 : public AbstractFactory {
public:
	FrameApi* createFrameApi() {
		return new MobileFrame("1024x768");
	}
	LayoutApi* createLayoutApi() {
		return new MobileLayout("1024x768");
	}
};

class AdvanceGuiEngine {
public:
	void prepareMaterials(AbstractFactory* pSchema) {
		this->pFrame = pSchema->createFrameApi();
		this->pLayout = pSchema->createLayoutApi();
		pFrame->draw();
		pLayout->installFrame();
	}
private:
	FrameApi* pFrame;
	LayoutApi* pLayout;
};

int main(void)
{
	AdvanceGuiEngine* pEng = new AdvanceGuiEngine();
	pEng->prepareMaterials(new Schemal1);
	return 0;
}