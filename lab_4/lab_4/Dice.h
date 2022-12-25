#pragma once
#include <iostream>
#include <vector>
#include <random>

class Dice {
private:
	int diceAmount;
	int faceAmount;
	//char modifierOperation;
	int modifierNumber;

public:
	Dice(int dice, int face);
	Dice(int dice, int face,/* char modifierOperation,*/ int modifierNumber);

	static int rollDice(std::vector<Dice> dices, std::default_random_engine& randGenerator);

	int getDiceAmount();
	int getFaceAmount();
	//char getModifierOperation();
	int getModifierNumber();
};

