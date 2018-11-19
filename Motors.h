#pragma once

#include <Servo.h>

class Motor {
public:
	Motor();
	virtual void init() = 0;
	virtual void set_power() = 0;
	void set_inverise(bool inverse);
	bool get_inverise();
	int8_t get_power();
protected:
	int8_t m_power;
	bool m_is_inverse;
};

class BrushlessMotor:Motor {
public:
	BrushlessMotor(uint8_t pin);
private:
	Servo m_driver;
};

class BrushMotor:Motor { //PWM CONTROL
public:
	BrushMotor(uint8_t pin_left, uint8_t pin_right);
private:
	uint8_t m_driver_left;
	uint8_t m_driver_right;
};

class LevelMotor:Motor { //LEVEL CONTROL
public:
	LevelMotor(uint8_t pin_left, uint8_t pin_right);
private:
	uint8_t m_driver_left;
	uint8_t m_driver_right;
};
