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
	LayoutApi(){}
};

class ComputerFrame : public FrameApi {
public:
	ComputerFrame(std::string pins) : m_pins(pins) {}
	void draw() {
		std::cout << "Using Computer frame now, resolution is:" << m_pins << std::endl;
	}
private:
	std::string m_pins;
};


class MobileFrame : public FrameApi {
public:
	MobileFrame(std::string pins) : m_pins(pins) {}
	void draw() {
		std::cout << "Using Mobile frame now, resolution is:" << m_pins << std::endl;
	}
private:
	std::string m_pins;
};


class ComputerLayout : public LayoutApi {
public:
	ComputerLayout(std::string FrameAdpaterPins) : m_FrameAdpaterPins( FrameAdpaterPins ) {}
	void installFrame() {
		std::cout << "Computer environment:" << m_FrameAdpaterPins << std::endl;
	}
private:
	std::string m_FrameAdpaterPins;
};


class MobileLayout : public LayoutApi {
public:
	MobileLayout(std::string FrameAdpaterPins) : m_FrameAdpaterPins( FrameAdpaterPins ) {}
	void installFrame() {
		std::cout << "Mobile environment:" << m_FrameAdpaterPins << std::endl;
	}
private:
	std::string m_FrameAdpaterPins;
};


class FrameFactory {
public:
	static FrameApi* createFrame(int type)
	{
		if (type == 1) {
			return new ComputerFrame("2560x1440");
		} 
		if (type == 2) {
			return new MobileFrame("1024x768");
		}
		return nullptr;
	}
};


class LayoutFactory {
public:
	static LayoutApi* createLayout(int type) {
		if (type == 1) {
			return new ComputerLayout("2560x1440");
		}
		if (type == 2) {
			return new MobileLayout("1024x768");
		}
		return nullptr;
	}
};

class GUIEngine {
public:
	void prepareDraw(int FrameType, int LayoutType) {
		this->pFrame = FrameFactory::createFrame(FrameType);
		this->pLayout = LayoutFactory::createLayout(LayoutType);
		pFrame->draw();
		pLayout->installFrame();
	}
private:
	FrameApi* pFrame;
	LayoutApi* pLayout;
};

int main()
{
	GUIEngine* pEng = new GUIEngine;
	pEng->prepareDraw(1, 1);
	if (nullptr != pEng) {
		delete pEng;
		pEng = nullptr;
	}
	return 0;
}
