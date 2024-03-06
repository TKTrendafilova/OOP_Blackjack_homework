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

	//Голяма четворка
	Deck();
	Deck(unsigned, char* ="Custom");
	Deck(const Deck&);
	Deck& operator=(const Deck&);
	~Deck();

	//Метатори
	void setCards(Card*);
	void setSeries(char*);
	void setCountCards(unsigned);
	void setCapacity(unsigned);

	//Селектори
	Card* getCards();

private:
	void resize();
	void cleanMemory();
	void copyFrom(const Deck&);

	//Инициялизираща функция.
	void initDeck();

	//Функция, която разбърква тестето с карти.
	void shuffleDeck();

	//Функция, която връща боята на картата по даден номер.
	Paint returnPaint(unsigned);

public:
	//Други функции
	//Функция, която добавя карта
	void addCard(const Card&);

	//Функция за теглене на една карта
	void cardDrawing();

	Card& draw();
	void swap(unsigned, unsigned);
	unsigned suit_count(Paint);
	unsigned rank_count(char*);

	//Функция, която казва каква е вероятността със следващата изтеглена карта играчът да спечели играта.
	double probabilityOfWinning( unsigned);

	unsigned getCount() const { return m_countCard; }
	
	//Функция, която връща точките на картата, която ще бъде изтеглена.
	unsigned returnPoint();

};

#endif