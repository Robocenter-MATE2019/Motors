#include "Motors.h"
#include <Arduino.h>


bool Motor::get_inverse()
{
	return m_is_inverse;
}

void Motor::set_inverse(bool inverse)
{
	m_is_inverse = inverse;
}

int8_t Motor::get_power()
{
	return m_power;
}



BrushlessMotor::BrushlessMotor(uint8_t pin)
{ 
	m_pin = pin;
}

void BrushlessMotor::init()
{
	m_driver.attach(m_pin);
	m_driver.writeMicroseconds(1500);
}

void BrushlessMotor::set_power(int8_t power)
{
	m_power = constrain(power, -100, 100);
	if (m_is_inverse) m_power *= -1;
	m_power = map(m_power, -100, 100, 1000, 2000);
	m_driver.writeMicroseconds(m_power);
}



BrushMotor::BrushMotor(uint8_t pin_left, uint8_t pin_right)
{
	m_driver_right = pin_right;
	m_driver_left = pin_left;
}

void BrushMotor::init()
{
	pinMode(m_driver_right, OUTPUT);
	pinMode(m_driver_left, OUTPUT);
}
void BrushMotor::set_power(int8_t power)
{
	m_power = constrain(power, -100, 100);
	m_power = m_is_inverse ? m_power * -1 : m_power;
	if (m_power > 0)
	{
		analogWrite(m_driver_left, map(abs(m_power), 0, 100, 0, 255));
		analogWrite(m_driver_right, 0);
	}
	else
	{
		analogWrite(m_driver_right, map(abs(m_power), 0, 100, 0, 255));
		analogWrite(m_driver_left, 0);
	}
}



LevelMotor::LevelMotor(uint8_t pin_left, uint8_t pin_right)
{
	m_driver_right = pin_right;
	m_driver_left = pin_left;
}
void LevelMotor::init()
{
	pinMode(m_driver_left, OUTPUT);
	pinMode(m_driver_right, OUTPUT);
}
void LevelMotor::set_power(int8_t power)
{
	m_power = constrain(power, -100, 100);
	m_power = m_is_inverse ? m_power * -1 : m_power;
	if (m_power < 0)
	{
		digitalWrite(m_driver_left, HIGH);
		digitalWrite(m_driver_right, LOW);
	}
	else
	{
		digitalWrite(m_driver_left, LOW);
		digitalWrite(m_driver_right, HIGH);
	}
}
