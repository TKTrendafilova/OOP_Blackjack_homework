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
	//������� ����������, ����� �� ���� ����� ���� �� ���������� ����.
	//�� �� ����� �� ���������� �� ����������� �� ��������.
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
	//������
	void setName(char*);
	void setYear(unsigned);
	void setVictories(unsigned);
	void setCoef(double);
	void setPoint(unsigned);
	void setNumberOfGames(unsigned);


	//���������� �������
	void printInfo();

	//������
	char* getName()const;
	unsigned getVictories()const;
	unsigned getNumberOfGames()const;

	//��������� �� ������������ �� �������� � ������� ����.
	void writeToFile (std::ofstream&)const;

	//������ �� ������������ �� �������� �� ������� ����.
	void readFromFile(std::ifstream&);
};

#endif
