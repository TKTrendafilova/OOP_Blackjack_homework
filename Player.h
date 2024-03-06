#ifndef __PLAYER_H
#define __PLAYER_H

#include<fstream>


class Player {
private:
	char* m_name;
	unsigned m_year;
	unsigned m_victories;
	double m_coefVictories;
	unsigned m_points;
	//Помощна променлива, която ще пази общия брой на изиграните игри.
	//Тя ще служи за изчисление на коефициента на победите.
	unsigned m_numberOfGames;

public:
	Player();
	Player(char*, unsigned, unsigned, double, unsigned, unsigned=0);
	Player(const Player&);
	Player& operator=(const Player&);
	~Player();

private:
	void copyFrom(const Player&);
	void cleanMemory();

public:
	//Сетъри
	void setName(char*);
	void setYear(unsigned);
	void setVictories(unsigned);
	void setCoef(double);
	void setPoint(unsigned);
	void setNumberOfGames(unsigned);


	//Принтираща функция
	void printInfo();

	//Гетъри
	char* getName()const;
	unsigned getVictories()const;
	unsigned getNumberOfGames()const;

	//Записване на информацията за играчите в двоичен файл.
	void writeToFile (std::ofstream&)const;

	//Четене на информацията за играчите от двойчен файл.
	void readFromFile(std::ifstream&);
};

#endif
