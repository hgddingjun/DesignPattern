#include <iostream>

class Camera {
public:
	void turnOn() {
		std::cout << "Open Camera" << std::endl;
	}
	void turnOff() {
		std::cout << "Close Camera" << std::endl;
	}
};

class FlashLight {
public:
	void turnOn() {
		std::cout << "Flashlight Opened" << std::endl;
	}
	void turnOff() {
		std::cout << "Flashlight Closed" << std::endl;
	}
};

class Sensor {
public:
	void active() {
		std::cout << "active Sensor" << std::endl;
	}
	void deactive() {
		std::cout << "deactive Sesnor" << std::endl;
	}
};

class Alarm {
public:
	void active() {
		std::cout << "active Alarm" << std::endl;
	}
	void deactive() {
		std::cout << "deactive Alarm" << std::endl;
	}
};

class SecurityFacade {
public:
	SecurityFacade() {
		Camera* m_pCamera = new Camera;
		FlashLight* m_pFlashLight = new FlashLight;
		Sensor* m_pSensor = new Sensor;
		Alarm* m_pAlarm = new Alarm;
		std::cout << "Construct SecurityFacade(){}" << std::endl;
	}
	void active() {
		m_pCamera->turnOn();
		m_pFlashLight->turnOn();
		m_pSensor->active();
		m_pAlarm->active();
	}
	void deactive() {
		m_pAlarm->deactive();
		m_pSensor->deactive();
		m_pFlashLight->turnOff();
		m_pCamera->turnOff();
	}
	virtual ~SecurityFacade() {
		if (nullptr != m_pAlarm) {
			delete m_pAlarm;
			m_pAlarm = nullptr;
		}
		if (nullptr != m_pSensor) {
			delete m_pSensor;
			m_pSensor = nullptr;
		}
		if (nullptr != m_pFlashLight) {
			delete m_pFlashLight;
			m_pFlashLight = nullptr;
		}
		if (nullptr != m_pCamera) {
			delete m_pCamera;
			m_pCamera = nullptr;
		}
		std::cout << "Destruct ~SecurityFacade(){}" << std::endl;
	}
private:
	Camera* m_pCamera;
	FlashLight* m_pFlashLight;
	Sensor* m_pSensor;
	Alarm* m_pAlarm;
};

int main(void) {

	Camera* pCamera = new Camera;
	FlashLight* pFlashLight = new FlashLight;
	Sensor* pSensor = new Sensor;
	Alarm* pAlarm = new Alarm;
	std::cout << "<<<<<<Launch System>>>>>>" << std::endl;
	pCamera->turnOn();
	pFlashLight->turnOn();
	pSensor->active();
	pAlarm->active();

	std::cout << ">>>>>>Close System<<<<<<" << std::endl;
	pAlarm->deactive();
	pSensor->deactive();
	pFlashLight->turnOff();
	pCamera->turnOff();

	if (nullptr != pAlarm) {
		delete pAlarm;
		pAlarm = nullptr;
	}
	if (nullptr != pSensor) {
		delete pSensor;
		pSensor = nullptr;
	}
	if (nullptr != pFlashLight) {
		delete pFlashLight;
		pFlashLight = nullptr;
	}
	if (nullptr != pCamera) {
		delete pCamera;
		pCamera = nullptr;
	}

/************************ Facade ************************/
	SecurityFacade facade;

	std::cout << "<<<<<< SecurityFacade Launch System >>>>>>" << std::endl;
	facade.active();
	std::cout << ">>>>>> SecurityFacade Close System <<<<<<" << std::endl;
	facade.deactive();

	return 0;
}