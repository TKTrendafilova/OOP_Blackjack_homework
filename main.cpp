#pragma warning(disable:4996)
#include<iostream>
#include<cstring>
#include<ctime>
#include"CardDeck.h"
#include "Player.h"

void testCardClass() {
	//Всички тестове са упешни!

	Card c1(Paint::Clubs, "3", "default1");
	c1.print();
	std::cout << "Get point card: " << c1.getPoint() << std::endl;
	c1.setPaint(Paint::Diamonds);
	std::cout << "After setPaint(Paint::Diamonts) : " << std::endl;
	c1.print();
	c1.setValue("7");
	c1.print();
	Card c2 = c1;;
	std::cout << "Print info for secoind card: " << std::endl;
	c2.print();
	Card c3;
	c3 = c1;
	std::cout << "Print info for 3-th card:" << std::endl;
	c3.print();
	std::cout << c1.getPaint() << ", " << c1.getValue() << ", " << c1.getSerial() << std::endl;
}

//Актуализиране на данните за играча, ако загуби играта.
void updateLose(Player& player, std::ofstream& ofs) {
	
	unsigned number = player.getNumberOfGames();
	unsigned victories= player.getVictories();

	player.setNumberOfGames(number + 1);
	double coef = (double)number / (double)victories;
	player.setCoef(coef);
	player.writeToFile(ofs);
	ofs.close();

}

//Актуализиране на информацията за играча, ако е спечелил.
void updateWin(Player& player, std::ofstream& ofs) {
	
	unsigned number = player.getNumberOfGames();
	unsigned victories = player.getVictories();

	player.setVictories(victories + 1);
	player.setNumberOfGames(number+ 1);
	double coef = (double) number / (double)victories;
	player.setCoef(coef);
	player.writeToFile(ofs);
	ofs.close();

}


 void run(Deck & deck, Player& player , std::ofstream& ofs) {

	const unsigned LEN_COMMAND= 12;
	const unsigned MAX_POINT_PLAYER = 21;
	const unsigned otherPointOfAce = 11;

	std::cout << "Start!" << std::endl;

	unsigned tempPointPlayer = 0;
	unsigned tempPointDealer = 0;

	char command[LEN_COMMAND];
	
	//Пръво теглене на играча.
	tempPointPlayer += deck.returnPoint();
	deck.cardDrawing();
	
	while (true) {
		
		std::cout << "Hit/Stand/Probability" << std::endl;
		std::cin.getline(command, LEN_COMMAND);
		if (strcmp(command, "Hit") == 0) {

			//Проверка колко точки да носи карта със стойност А.
			if (deck.returnPoint() == 1) {
				//Когато искаме да получим 11 точки.
				if (tempPointPlayer < otherPointOfAce) {
					tempPointPlayer += otherPointOfAce;
					deck.cardDrawing();
				}
				else{
					tempPointPlayer += deck.returnPoint();
					deck.cardDrawing();
				}
			}

			tempPointPlayer += deck.returnPoint();
			deck.cardDrawing();
			//Приключване на играта, когато играчът при теглене събете повече от 21 точки.
			if (tempPointPlayer > MAX_POINT_PLAYER) {
				std::cout << "You lose!" << std::endl;
				updateLose(player, ofs);
				break;
				return;
			}
			
		}
		if (strcmp(command, "Stand") == 0) {
			//Генериране тегленето на раздавача.
			std::cout << "The dealer's draw: ";
			while (true) {
				tempPointDealer += deck.returnPoint();;
				deck.cardDrawing();

				if (tempPointDealer > 21) {
					std::cout << "Congratulations! You have won! The dealer lose." << std::endl;
					updateWin(player, ofs);
					break;
					return;
				}
				if (tempPointDealer >= 17 && tempPointDealer <= 21) {
					if (tempPointPlayer >= tempPointDealer) {
						std::cout << "Congratulations! You have won!" << std::endl;
						updateWin(player, ofs);
						break;
						return;
					}
					else {
						std::cout << "The dealer has won!" << std::endl;
						updateLose(player, ofs);
						break;
						return;
					}
				}
			}

		}
		if (strcmp(command, "Probability") == 0) {
			unsigned probability=deck.probabilityOfWinning(tempPointPlayer);
			std::cout << probability << std::endl;
		}
	}
}

void testOverloadingOperator() {
	Card c1(Paint::Clubs, "2", "def");
	Card c2(Paint::Diamonds, "2", "def");
	if (c1 == c2) {
		std::cout << "card operetor== work successffully!" << std::endl;
	}
	else {
		std::cout << "cards operator== don't work!" << std::endl;
	}
}

int main() {

	Player newPlayer;
	
	//частта с фойловете работи успешно.
	std::ofstream ofs("player.bin", std::ios::out | std::ios::binary | std::ios::trunc);

	const unsigned  countPlayer = 3;
	const unsigned defaultCountCards = 52;

	//Записваме броя на играчите в началота на файла.
	//ofs.write((const char*)& countPlayer, sizeof(countPlayer));

	Player p1("Patar Petrov", 23, 3, 0.3, 0,10);
	Player p2("Ivan Ivanov", 51, 157, 7, 0,1450);
	Player p3("Svetla Ivanova", 31, 23, 1.3, 0,9);

	p1.writeToFile(ofs);
	p2.writeToFile(ofs);
	p3.writeToFile(ofs);

	ofs.close();

	

	std::ifstream ifs("player.bin", std::ios::in | std::ios::binary);
	
	Player playerList[countPlayer];

	for (int i = 0; i < countPlayer; ++i) {
		playerList[i].readFromFile(ifs);
	}

	for (int i = 0; i < countPlayer; ++i) {
		playerList[i].printInfo();
	}

	ifs.close();



	const unsigned LEN_NAME=51;

	//Deck deck;
	//deck.cardDrawing();
	char enterCode;
	std::cout << "Do you want to log in as an already registered user [y/n]." << std::endl;
	std::cin >> enterCode;
	char nameNewPlayer[LEN_NAME];
	
	//Преминало е тест.
	if (enterCode == 'y' || enterCode == 'Y') {
		std::cout << "Enter a name: ";

		//За да работи правилно cin.getline(...).
		char c;
		std::cin.get(c);

		std::cin.getline(nameNewPlayer, LEN_NAME);

		unsigned age;
		std::cout << "Enter your age: ";
		std::cin >> age;
		if (age < 18 || age>90) {
			std::cout << "You can not play the game. It's a gamble. " << std::endl;
			return 1;

		}
		newPlayer = Player(nameNewPlayer, age, 0, 0, 0);
		std::cout << "You will play as " << nameNewPlayer << std::endl;
	}

	if (enterCode == 'n' || enterCode == 'N') {

		std::cout << "You have chosen to play as a registered user. Enter you user name: ";
		//За да работи правилно cin.getline(...).
		char c;
		std::cin.get(c);

		std::cin.getline(nameNewPlayer, LEN_NAME);
		bool isUser = false;
		for (int i = 0; i < countPlayer; ++i) {
			if (strcmp(nameNewPlayer, playerList[i].getName()) == 0) {
				newPlayer = playerList[i];
				isUser = true;
				break;
			}
		}
		if (isUser == false) {
			std::cout << "Invalid user name." << std::endl;
			return 1;
		}

		std::cout << "You will play as " << nameNewPlayer << " ." << std::endl;
		
	}


	 ofs.open("player.bin", std::ios::out | std::ios::binary | std::ios::app);

	unsigned countCards;
	std::cout << "Chose the size of deck." << std::endl;
	std::cin >> countCards;

	if (countCards == defaultCountCards) {
		Deck deck;
		run(deck, newPlayer, ofs);
		
	}
	else {
		std::cout << "Do you want to enter the series of the deck of cards? [y/n]" << std::endl;
		char enterSeriesOfDeck;
		std::cin>> enterSeriesOfDeck;
		
		// Ако потребителя няма да въведе серията не тестето от карти.
		if (enterSeriesOfDeck == 'n' || enterSeriesOfDeck == 'N') {
			Deck deck(countCards);
			run(deck,newPlayer, ofs);
		}

		//Ако потребителя желае да въведте серията на тестето от карти. 
		if (enterSeriesOfDeck == 'y' || enterSeriesOfDeck == 'Y') {
		
			const unsigned LEN_SERIES = 11;
			char series[LEN_SERIES];
			std::cout << "Enter a deck's series: ";
			//За да работи правилно cin.getline().
			char c;
			std::cin.get(c);

			std::cin.getline(series, LEN_SERIES);

			Deck deck(countCards, series);
			run(deck,newPlayer, ofs);
		}
		//Няма да проверявам дали enterSeriesOfDeck е различно от 'n' и 'y', защото на потребителя ясно е указано, какво трабда да въведе.
		
	}

	return 0;
}



