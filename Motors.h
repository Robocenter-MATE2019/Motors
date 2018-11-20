#pragma once

#include <Servo.h>
#include <Arduino.h>

class Motor {
public:
	//Motor();
	virtual void init() = 0;
	virtual void set_power(int8_t power) = 0;
	void set_inverse(bool inverse);
	bool get_inverse();
	int8_t get_power();
protected:
	int8_t m_power;
	bool m_is_inverse;
};

class BrushlessMotor:public Motor {
public:
	BrushlessMotor(uint8_t pin);
	void init();
	void set_power(int8_t power);
private:
	uint8_t m_pin;
	Servo m_driver;
};

class BrushMotor:public Motor { //PWM CONTROL
public:
	BrushMotor(uint8_t pin_left, uint8_t pin_right);
	void init();
	void set_power(int8_t power);
private:
	uint8_t m_driver_left;
	uint8_t m_driver_right;
};

class LevelMotor:public Motor { //LEVEL CONTROL
public:
	LevelMotor(uint8_t pin_left, uint8_t pin_right);
	void init();
	void set_power(int8_t power);
private:
	uint8_t m_driver_left;
	uint8_t m_driver_right;
};
