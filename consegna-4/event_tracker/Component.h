#ifndef __COMPONENT__
#define __COMPONENT__

/*
La classe astratta component modella il; concetto di componente come entit� fisica collegata all'arduino.
Per questo motivo contiene al suo interno un array di pin ed il tipo del componente. Le interfacce dei
singoli componenti non estendono queta perch� si � voluto separare il concetto di componente fisico
da quello funzionale*/
enum class ComponentTypes {DEBUNCINGBUTTON, LED, SONAR, HC06, SERVO2, PIR, BUZZER};

//TODO deleter componen vector
class Component
{

public:
	int* getPin() {
		return this->pins;
	}
	ComponentTypes getType() {
		return this->type;
	}
private:
	int* pins;
	ComponentTypes type;
protected:
	Component(int pin[], ComponentTypes type) {
		this->type = type;
		this->pins = pin;
	}
};


#endif
