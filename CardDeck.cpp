#pragma warning (disable:4996)
#include<iostream>
#include<cstring>
#include<ctime>
#include"CardDeck.h"


unsigned countCardOfOnePaint = 13;
unsigned const defaultCount = 52;
unsigned countNumberValue = 0;
unsigned posTen = 8;


//int Deck::m_ID = 0;
unsigned defaultCountCards = 52;
unsigned startCapacity = 16;

Deck::Deck()
	:m_cards(nullptr), m_series("Default"), m_countCard(defaultCountCards), m_capacity(startCapacity)
{
	initDeck();
	shuffleDeck();
}

Deck::Deck(unsigned size, char* series)
{
	unsigned countPaintNumber = 4;

	if (size == defaultCount) {
		Deck();
		setSeries(series);
	}
	else {
		for (int i = 0; i < size; ++i) {

			char** mat = new(std::nothrow) char*[countCardOfOnePaint];
			if (mat == nullptr) {
				std::cout << "Error1!" << std::endl;
				return;
			}
			for (int i = 0; i < countCardOfOnePaint; ++i) {
				if (i < posTen && i > posTen) {
					mat[i] = new(std::nothrow) char[strlen("1") + 1];
					if (mat[i] == nullptr) {
						//Направи го да работи провилно. УП
						std::cout << "Error2!" << std::endl;
						return;
					}
				}
				else {
					mat[i] = new(std::nothrow) char[strlen("10") + 1];
					if (mat[i] == nullptr) {
						std::cout << "Error2!" << std::endl;
						return;
					}
				}
			}

			strcpy(mat[0], "2");
			strcpy(mat[1], "3");
			strcpy(mat[2], "4");
			strcpy(mat[3], "5");
			strcpy(mat[4], "6");
			strcpy(mat[5], "7");
			strcpy(mat[6], "8");
			strcpy(mat[7], "9");
			strcpy(mat[8], "10");
			strcpy(mat[9], "J");
			strcpy(mat[10], "Q");
			strcpy(mat[11], "K");
			strcpy(mat[12], "A");
			
			m_cards = new(std::nothrow) Card[size];
			if (m_cards == nullptr) {
				std::cout << "Not enought memory for cards! Error!" << std::endl;
				return;
			}
			setSeries(series);
			setCountCards(size);
			srand(time(0));
			

			//Брояч на еднавите карти.
			unsigned countSameCard = 0;

			//Брояч колко карти са сетнати.
			unsigned tempCountCard = 0;

			//Максимален брой на картите от един и същи вид.
			double repetitionRare = (double)(size - 1) / (double)(defaultCount + 1);
			//std::cout << "repetitionRare: " <<size-1<<"/"<<defaultCount+1<<"= "<< repetitionRare << std::endl;

			while (tempCountCard < size) {

				unsigned paintNumber = rand() % countPaintNumber;
				Paint paint = returnPaint(paintNumber);

				unsigned valuePosInMatrix = rand() % (countCardOfOnePaint);
				char* value = new(std::nothrow) char[strlen(mat[valuePosInMatrix] + 1)];
				if (value == nullptr) {
					std::cout << "Not enought memory! Error!" << std::endl;
					return;
				}
				strcpy(value, mat[valuePosInMatrix]);
				Card tempCard(paint, value, series);

				
				for (int i = tempCountCard+1; i > 0; --i) {
					if (m_cards[i] == tempCard) {
						++countSameCard;
					}
				}
				//std::cout << "Count same cards: " << countSameCard << std::endl;
				//Проверка дали броят на повтарящите се карти е повече от позволената.
				if (countSameCard <= (int)repetitionRare) {
					
					m_cards[tempCountCard] = tempCard;
					++tempCountCard;
					countSameCard = 0;
				}
				else {
					countSameCard = 0;
				}
			}

			for (int i = 0; i < countCardOfOnePaint; ++i) {
				delete[] mat[i];
			}
			delete mat;
		}
	}
}

Deck::Deck(const Deck & other)
{
	if (this != &other) {
		copyFrom(other);
	}
}

Deck & Deck::operator=(const Deck & other)
{
	if (this != &other) {
		cleanMemory();
		copyFrom(other);
	}
	return *this;
}

Deck::~Deck()
{
	cleanMemory();
	
}

void Deck::setCards(Card * cards)
{ 
	for (int i = 0; i < m_countCard; ++i) {
		m_cards[i] = cards[i];
	}
}

void Deck::setSeries(char * series)
{
	/*if (m_series != nullptr) {
		delete[] m_series;
	}*/

	m_series = new(std::nothrow) char[strlen(series) + 1];
	if (m_series == nullptr) {
		std::cout << "Not enought memory for deck's series. Error!" << std::endl;
		return;
	}
	strcpy(m_series, series);

}

void Deck::setCountCards(unsigned count)
{
	m_countCard = count;
}

void Deck::setCapacity(unsigned capacity)
{
	m_capacity = capacity;
}

void Deck::resize()
{
	int newCapacity = m_capacity * 2;
	Card* newCard = new (std::nothrow) Card[newCapacity];
	if (newCard == nullptr) {
		std::cout << "Not enought memory!" << std::endl;
		return;
	}
	for (int i = 0; i < m_countCard; ++i) {
		newCard[i] = m_cards[i];
	}
	m_capacity = newCapacity;
	delete[]m_cards;
	m_cards = newCard;
}

void Deck::cleanMemory()
{
	delete[] m_cards;
	m_cards = nullptr;
	delete[] m_series;
	m_series = nullptr;
}

void Deck::copyFrom(const Deck & other)
{
	if (m_cards != nullptr) {
		cleanMemory();
	}

	m_cards = new (std::nothrow) Card[other.m_capacity];
	if (m_cards == nullptr) {
		std::cout << "Not enought memory for array of cards. Error!" << std::endl;
		return;
	}
	for (int i = 0; i < other.m_countCard; ++i) {
		m_cards[i] = other.m_cards[i];
	}

	setSeries(other.m_series);
	setCountCards(other.m_countCard);
	setCapacity(other.m_capacity);

}

void Deck::initDeck()
{
	
	unsigned currentCnt = 0;
	unsigned countCardOfOnePaint = 13;
	unsigned countNumberValue = 0;
	unsigned posTen = 8;

	char** mat = new(std::nothrow) char*[countCardOfOnePaint];
	if (mat == nullptr) {
		std::cout << "Error1!" << std::endl;
		return ;
	}
	for (int i = 0; i < countCardOfOnePaint; ++i) {
		if (i < posTen && i > posTen) {
			mat[i] = new(std::nothrow) char[strlen("1") + 1];
			if (mat[i] == nullptr) {
				//Направи го да работи провилно. УП
				std::cout << "Error2!" << std::endl;
				return;
			}
		}
		else {
			mat[i] = new(std::nothrow) char[strlen("10") + 1];
			if (mat[i] == nullptr) {
				std::cout << "Error2!" << std::endl;
				return ;
			}
		}

	}

	strcpy(mat[0], "2");
	strcpy(mat[1], "3");
	strcpy(mat[2], "4");
	strcpy(mat[3], "5");
	strcpy(mat[4], "6");
	strcpy(mat[5], "7");
	strcpy(mat[6], "8");
	strcpy(mat[7], "9");
	strcpy(mat[8], "10");
	strcpy(mat[9], "J");
	strcpy(mat[10], "Q");
	strcpy(mat[11], "K");
	strcpy(mat[12], "A");



	m_cards = new(std::nothrow) Card[defaultCount];
	if (m_cards == nullptr) {
		std::cout << "Not enought memory for m_cards. Error!" << std::endl;
		return;
	}

	unsigned temp = 0;

	for (int i = 0; i < defaultCount; ++i) {
		//unsigned tempPaintNumber = currentCnt / countCardOfOnePaint;
		//Paint paint = returnPaint(/*temp*/tempPaintNumber);

		//Ако все още нямяме всички карти от един цвят
		if (currentCnt < countCardOfOnePaint) {
			unsigned tempPaintNumber = currentCnt / countCardOfOnePaint;
			Paint paint = returnPaint(/*temp*/tempPaintNumber);

			char* newSerial = new(std::nothrow) char[strlen(mat[currentCnt]) + 1];
			if (newSerial == nullptr) {
				return;
			}
			strcpy(newSerial, mat[currentCnt]);

			m_cards[i].setPaint(paint);
			m_cards[i].setSerialNumber("Default1"/*mat[countCardOfOnePaint - currentCnt]*/);
			m_cards[i].setValue(newSerial/*"Default1"*/);
			++currentCnt;
		}
		if (currentCnt%countCardOfOnePaint == 0) {
			++temp;
		}
		unsigned posInMatrix = currentCnt - (temp*countCardOfOnePaint);
	//	std::cout <<"posInMatrix: " <<posInMatrix << std::endl;
		if(currentCnt>=countCardOfOnePaint) {

			unsigned tempPaintNumber = currentCnt / countCardOfOnePaint;
			Paint paint = returnPaint(/*temp*/tempPaintNumber);

			//unsigned posInMatrix = currentCnt - (tempPaintNumber*countCardOfOnePaint);
			char* newSerial = new(std::nothrow) char[strlen(mat[posInMatrix])];
			if (newSerial == nullptr) {
				return;
			}
			strcpy(newSerial, mat[currentCnt - (temp*countCardOfOnePaint)]);

			m_cards[i].setPaint(paint);
			m_cards[i].setSerialNumber("Default1");
			m_cards[i].setValue(newSerial);
			
			++currentCnt;
		}
	}

	
	for (int i = 0; i < countCardOfOnePaint; ++i) {
		delete[] mat[i];
	}
	delete mat;

}

void Deck::shuffleDeck()
{
	srand(time(0));
	for (int i = 0; i < m_countCard; ++i) {
		unsigned tempPos = rand() % (m_countCard + 1);
		Card tempCard = m_cards[i];
		m_cards[i] = m_cards[tempPos];
		m_cards[tempPos] = tempCard;
	}
}

Paint Deck::returnPaint(unsigned paintNumber)
{
	switch (paintNumber) {
	case 1:
		return Paint::Clubs;

	case 2:
		return Paint::Diamonds;

	case 3:
		return Paint::Hearts;

	case 4:
		return Paint::Spaders;
	}
}

void Deck::addCard(const Card & card)
{
	if (m_countCard > m_capacity) {
		resize();
	}
	m_cards[m_countCard] = card;
	m_countCard++;
}

void Deck::cardDrawing()
{
//	if (m_countCard >= 0) {
		m_cards[m_countCard-1].print();
		m_countCard--;
//	}
	/*else {
		std::cout << "No more cards." << std::endl;
		return;
	}*/
	return;
	
}

Card & Deck::draw()
{
	Card c = m_cards[m_countCard];
	for (int i = m_countCard; i > 0; --i) {
		m_cards[i] = m_cards[i - 1];
	}
	m_cards[0] = c;
	return m_cards[0];
}

void Deck::swap(unsigned position1, unsigned position2)
{
	if (position1 >= 0 && position1 < m_countCard && position2 >= 0 && position2 < m_countCard) {
		Card temp = m_cards[position1];
		m_cards[position1] = m_cards[position2];
		m_cards[position2] = temp;
	}
	else {
		std::cout << "Invalid position/positions!" << std::endl;
		return;
	}
}

unsigned Deck::suit_count(Paint paint)
{
	unsigned count = 0;
	for (int i = 0; i< m_countCard; ++i) {
		if (m_cards[i].getPaint() ==(int) paint) {//Каствам го до int, защото getPaint() ми върща стойността.
			++count;
		}
	}
	return count;
}

unsigned Deck::rank_count(char* value)
{
	std::cout << "in for cicle in ranc_count()... count of cards is:" << m_countCard << std::endl;
	unsigned count = 0;
	for (int i = 0; i <this->getCount(); ++i) {
		
		if (strcmp(m_cards[i].getValue(), value) == 0) {
			++count;
		}
	}
	return count;
}

double Deck::probabilityOfWinning(unsigned currentPoint)
{
	const unsigned maxPoint = 21;
	unsigned needPointsForWin = maxPoint - currentPoint;
	unsigned numberOfCardsWithTheRequiredValue = 0;
	for (int i = 0; i < m_countCard; ++i) {
		if (m_cards[i].getPoint() == needPointsForWin) {
			++numberOfCardsWithTheRequiredValue;
		}
	}
	double prob = numberOfCardsWithTheRequiredValue / (double)m_countCard;
	return prob;
}


unsigned Deck::returnPoint()
{
	//Връща точките на картата, която ще бъде изтеглена.
	return m_cards[m_countCard-1].getPoint();
}