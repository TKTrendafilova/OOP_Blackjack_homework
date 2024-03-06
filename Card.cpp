#pragma warning(disable:4996)//За да няма грешки при strcpy()
#include<iostream>
#include<cstring>
#include "Card.h"


Card::Card(Paint paint, char* value, char* serialNumber)
{
	setPaint(paint);
	setValue(value);
	setSerialNumber(serialNumber);
}

Card::Card()
	: m_paint(Paint::Unknown), m_value(nullptr), m_serialNumber(nullptr)
{
}

Card::Card(const Card &other)
{
	if (this != &other) {
		copyFrom(other);
	}
}

Card & Card::operator=(const Card & other)
{
	if (this != &other) {
		cleanMemory();
		copyFrom(other);
	}
	return *this;
}

Card::~Card()
{
	cleanMemory();
}

void Card::setPaint(Paint p)
	
{
	m_paint = p;
}

void Card::setValue(char* value)
{	
	delete[] m_value;
	m_value = new (std::nothrow) char[strlen(value) + 1];
	if (m_value == nullptr) {
		std::cout << "Not enought memory! Error! " << std::endl;
		return;
	}
	strcpy(m_value, value);

}

void Card::setSerialNumber( char* serial)
{

	delete[] m_serialNumber;
	m_serialNumber = new(std::nothrow) char[strlen(serial) + 1];
	if (m_serialNumber == nullptr) {
		std::cout << "Not enought memory for serial number. Error!" << std::endl;
		return;
	}
	strcpy(m_serialNumber, serial);

}

Paint Card::getPaint() const
{
	return m_paint;
}

char * Card::getValue() const
{
	return m_value;
}

char* Card::getSerial() const
{
	return m_serialNumber;
}

unsigned Card::getPoint() const
{
	
	if (atoi(m_value) == 0) {
		if (strcmp(m_value, "J") == 0 || strcmp(m_value, "Q") == 0 || strcmp(m_value, "K") == 0) {
			return 10;
		}
		if (strcmp(m_value, "A") == 0) {
			return 1;
		}
	}
	else {
		return atoi(m_value);
	}
	
}


void Card::print() const
{

	std::cout << this->getValue()/*m_value*/ << " (";
	switch (m_paint) {
	case Paint::Clubs:
		std::cout << "Clubs";
		break;
		

	case Paint::Diamonds:
		std::cout << "Diamonds" ;
		break;

	case Paint::Hearts:
		std::cout << "Hearts" ;
		break;

	case Paint::Spaders:
		std::cout << "Spaders" ;
		break;

	default:
		std::cout << "Unknown paint" ;
	}
	
	//Не използвам фунцията getPoint(), за за изведа двете възможности за точкуване на карта A.
	unsigned point=0;
	if (atoi(m_value) == 0) {
		if (strcmp(m_value, "J") == 0 || strcmp(m_value, "Q") == 0 || strcmp(m_value, "K") == 0) {
			point = 10;
		}
		if (strcmp(m_value, "A") == 0) {
			std::cout << ")" << " (1/11)" << std::endl;
			return;
		}
	}
	else {
		point = atoi(m_value);
	}
	
	std::cout<<")"<< " ("<<point<<")"<< std::endl;

}

bool Card::operator==(const Card & other) const
{
	if (this->getPaint() == other.getPaint()) {
		if (strcmp(this->m_value, other.m_value) == 0) {
			if (strcmp(this->m_serialNumber, other.m_serialNumber) == 0) {
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}


void Card::copyFrom(const Card & other)
{
	setPaint(other.m_paint);
	setValue(other.m_value);
	setSerialNumber(other.m_serialNumber);
}

void Card::cleanMemory()
{
	delete[] m_value;
	m_value = nullptr;
	delete[] m_serialNumber;
	m_serialNumber = nullptr;
}
