#pragma warning (disable:4996)
#include "Player.h"
#include<iostream>
#include<cstring>

Player::Player()
	:m_name(nullptr), m_year(18),m_victories(0),m_coefVictories(0),m_points(0)
{
}

Player::Player(char * name, unsigned year, unsigned victories, double coef, unsigned points, unsigned numberOfGames)
	:m_name(nullptr)/*, m_year(year)*/, m_victories(victories), m_coefVictories(coef), m_points(points), m_numberOfGames(numberOfGames)
{
	/*if (year < 18 || year>90) {
		std::cout << "You are not allowed to play." << std::endl;
		return;
	}*/
	setYear(year);
	setName(name);
}

Player::Player(const Player & other)
{
	if (this != &other) {
		copyFrom(other);
	}
}

Player & Player::operator=(const Player & other)
{
	if (this != &other) {
		cleanMemory();
		copyFrom(other);
	}
	return *this;
}

Player::~Player()
{
	cleanMemory();
}

void Player::copyFrom(const Player & other)
{
	setName(other.m_name);
	setYear(other.m_year);
	setVictories(other.m_victories);
	setCoef(other.m_coefVictories);
	setPoint(other.m_points);
	setNumberOfGames(other.m_numberOfGames);
}

void Player::cleanMemory()
{
	delete[] m_name;
	m_name = nullptr;
}

void Player::setName(char * name)
{
	if (m_name != nullptr) {
		cleanMemory();
	}

	bool isCorrectName;

	//Валидация на името. Не работи правилно. Прегледай я!!!!!!!
	unsigned len = strlen(name);
	for (int i = 0; i < len; ++i) {
		if (name[0] >= 'A' && name[0] <= 'Z')
		{
			if (name[i] == ' ' && name[i + 1] >= 'A' && name[i + 1] <= 'Z') {
				isCorrectName = true;
				break;
			}
			else {
				isCorrectName = false;
				break;
			}
		}
		isCorrectName = false;
	}

	
	if (isCorrectName==false){
		m_name = new (std::nothrow) char[len + 1];
		if (m_name == nullptr) {
			std::cout << "Not enought mempry for player's name. Error!" << std::endl;
			return;
		}
		strcpy(m_name, name);
	}
	else {
		std::cout << "Uncorrect name." << std::endl;
	}
	
}

void Player::setYear(unsigned year)
{
	if (year < 18 || year>90) {
		std::cout << "You are not allowed to play." << std::endl;
		return;
	}
	m_year = year;
}

void Player::setVictories(unsigned victories)
{
	m_victories = victories;
}

void Player::setCoef(double coef)
{
	m_coefVictories = coef;
}

void Player::setPoint(unsigned point)
{
	m_points = point;
}

void Player::setNumberOfGames(unsigned num)
{
	m_numberOfGames = num;
}

void Player::printInfo()
{
	std::cout << m_name << " " << m_victories << " " << m_coefVictories << std::endl;
}

char * Player::getName() const
{
	return m_name;
}

unsigned Player::getVictories()const 
{
	return m_victories;
}

unsigned Player::getNumberOfGames() const
{
	return m_numberOfGames;
}

void Player::writeToFile(std::ofstream & ofs) const
{
	//Пpоверка дали фaйлът е отворен успешно.
	if (!ofs.is_open()) {
		std::cout << "File is not open!" << std::endl;
		return;
	}

	unsigned lenName = strlen(m_name);
	ofs.write((const char*)& lenName, sizeof(lenName));
	ofs.write(m_name, lenName);

	ofs.write((const char*)& m_year, sizeof(m_year));
	ofs.write((const char*)& m_victories, sizeof(m_victories));
	ofs.write((const char*)& m_coefVictories, sizeof(m_coefVictories));
	ofs.write((const char*)& m_points, sizeof(m_points));
	ofs.write((const char*)& m_numberOfGames, sizeof(m_numberOfGames));

	//Проверка за състоянието на потока. 
	/*if (ofs.good()) {
		std::cout << "Successfully write. " << std::endl;
	}
	else{
		std::cout << "Failed." << std::endl;
	}*/


}

void Player::readFromFile(std::ifstream & ifs)
{
	//Проверка дали файлът е отворен.
	if (!ifs.is_open()) {
		std::cout << "File is not open." << std::endl;
		return;
	}

	unsigned lenName = 0;

	ifs.read((char*)& lenName, sizeof(lenName));
	m_name = new(std::nothrow) char[lenName + 1];
	if (m_name == nullptr) {
		std::cout << "Not enought memory for name in readFromFile(). Error!" << std::endl;
		return;
	}
	ifs.read(m_name, lenName);
	m_name[lenName] = '\0';

	ifs.read((char*)& m_year, sizeof(m_year));
	ifs.read((char*)& m_victories, sizeof(m_victories));
	ifs.read((char*)& m_coefVictories, sizeof(m_coefVictories));
	ifs.read((char*)& m_points, sizeof(m_points));
	ifs.read((char*)& m_numberOfGames, sizeof(m_numberOfGames));

	//За проверка дали правилно е записано във файла. След тест го закоментирай.
	/*if (ifs.good()) {
		std::cout << "Successfully read." << std::endl;
	}
	else {
		std::cout << "File was not successfully read." << std::endl;
	}*/

}
