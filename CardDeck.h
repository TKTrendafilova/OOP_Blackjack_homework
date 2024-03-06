#ifndef __CARD_DECK_H
#define __CARD_DECK_H

#include "Card.h"

class Deck {
private:
	Card * m_cards;
	char* m_series;
	unsigned m_countCard;
	unsigned m_capacity;
	

public:
//	static int m_ID;

	//������ ��������
	Deck();
	Deck(unsigned, char* ="Custom");
	Deck(const Deck&);
	Deck& operator=(const Deck&);
	~Deck();

	//��������
	void setCards(Card*);
	void setSeries(char*);
	void setCountCards(unsigned);
	void setCapacity(unsigned);

	//���������
	Card* getCards();

private:
	void resize();
	void cleanMemory();
	void copyFrom(const Deck&);

	//�������������� �������.
	void initDeck();

	//�������, ����� ��������� ������� � �����.
	void shuffleDeck();

	//�������, ����� ����� ����� �� ������� �� ����� �����.
	Paint returnPaint(unsigned);

public:
	//����� �������
	//�������, ����� ������ �����
	void addCard(const Card&);

	//������� �� ������� �� ���� �����
	void cardDrawing();

	Card& draw();
	void swap(unsigned, unsigned);
	unsigned suit_count(Paint);
	unsigned rank_count(char*);

	//�������, ����� ����� ����� � ������������ ��� ���������� ��������� ����� ������� �� ������� ������.
	double probabilityOfWinning( unsigned);

	unsigned getCount() const { return m_countCard; }
	
	//�������, ����� ����� ������� �� �������, ����� �� ���� ���������.
	unsigned returnPoint();

};

#endif