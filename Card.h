#ifndef __CARD_H
#define __CARD_H



enum  Paint {
	Unknown=-1,
	Clubs=0,
	Diamonds,
	Hearts,
	Spaders

};

//unsigned int const MAX_SIZE_LEN = 16;

class Card {
private:
	Paint m_paint;
	char* m_value;
	char* m_serialNumber;

public:
	//Ще реализирам голямата четворка, но помисли дали ще ти е нужна.
	Card();
	Card(Paint , char*, char*);
	Card(const Card&);
	Card& operator=(const Card&);
	~Card();

	void setPaint(Paint );
	void setValue(char*);
	void setSerialNumber(char*);/*char[MAX_SIZE_LEN]*/

	Paint getPaint()const ; 
	char* getValue() const;
	char* getSerial() const;
	unsigned getPoint() const;

	void print()const;
	
	//Предефиниране на опрератор ==
	bool operator==(const Card&) const;

private:
	void copyFrom(const Card&);
	void cleanMemory();

};

#endif
