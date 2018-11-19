// last changes 16.11.18. 23:44


#include <Servo.h>

class Motor {
public:
	Motor();
	virtual void init() = 0;
	virtual void set_power(int8_t power) = 0;
	void set_inverise(bool inverse)
	{
		m_is_inverse = inverse;
	}
	bool get_inverise()
	{
		return m_is_inverse;
	}
	int8_t get_power()
	{
		return m_power;
	}
protected:
	int8_t m_power;
	bool m_is_inverse;
};

class BrushlessMotor :Motor {
public:
	BrushlessMotor(uint8_t pin)
	{
		m_pin = pin;
	}
	void init() override
	{
		m_driver.attach(m_pin);
		m_driver.writeMicroseconds(2000);
		delay(2000);
		m_driver.writeMicroseconds(1000);
		delay(6000);
	}
	void set_power(int8_t power) override
	{
		power = constrain(power, -100, 100);
		if (m_is_inverse) power *= -1;
		power = map(power, -100, 100, 1000, 2000);
		m_driver.writeMicroseconds(power);
	}
private:
	uint8_t m_pin;
	Servo m_driver;
};

class BrushMotor :Motor { //PWM CONTROL
public:
	BrushMotor(uint8_t pin_left, uint8_t pin_right)
	{
		m_driver_right = pin_right;
		m_driver_left = pin_left;
	}
	void init() override
	{
		pinMode(m_driver_right, OUTPUT);
		pinMode(m_driver_left, OUTPUT);
	}
	void set_power(int8_t power) override
	{
		power = constrain(power, -100, 100);
		if (power > 0 || (m_is_inverse == true && power < 0))
		{
			power = map(abs(power), 0, 100, 0, 1023);
			analogWrite(m_driver_left, power);
			analogWrite(m_driver_right, 0);
		}
		else if (power < 0 || (m_is_inverse == false && power > 0))
		{
			power = map(abs(power), 0, 100, 0, 1023);
			analogWrite(m_driver_left, 0);
			analogWrite(m_driver_right, power);
		}
	}
private:
	uint8_t m_driver_left;
	uint8_t m_driver_right;
};

class LevelMotor :Motor { //LEVEL CONTROL
public:
	LevelMotor(uint8_t pin_left, uint8_t pin_right)
	{
		m_driver_right = pin_right;
		m_driver_left = pin_left;
	}
	void init() override
	{
		pinMode(m_driver_left, OUTPUT);
		pinMode(m_driver_right, OUTPUT);
	}
	void set_power(int8_t power) override
	{
		power = constrain(power, -100, 100);
		if (power > 0 || (m_is_inverse == true && power < 0))
		{
			digitalWrite(m_driver_left, HIGH);
			digitalWrite(m_driver_right, LOW);
		}
		else if (power < 0 || (m_is_inverse == false && power > 0))
		{
			digitalWrite(m_driver_left, LOW);
			digitalWrite(m_driver_right, HIGH);
		}
	}
private:
	uint8_t m_driver_left;
	uint8_t m_driver_right;
};
