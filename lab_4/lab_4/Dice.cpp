#include "Dice.h"

Dice::Dice(int dice, int face) :
    diceAmount(dice),
    faceAmount(face),
    //modifierOperation(' '),
    modifierNumber(0)
{}

Dice::Dice(int dice, int face,/* char operation,*/ int number) :
    diceAmount(dice),
    faceAmount(face),
    //modifierOperation(operation),
    modifierNumber(number)
{}

int Dice::rollDice(std::vector<Dice> dices, std::default_random_engine& randGenerator) {
    int result = 0;

    for (Dice dice : dices) {
        std::uniform_int_distribution<int> face(1, dice.getFaceAmount());

        for (int i = 0; i < dice.getDiceAmount(); i++) {
            int randomNumber = face(randGenerator);
            //std::cout << randomNumber << ' ';

            result += randomNumber;
        }
        //std::cout << std::endl;

        if (dice.getModifierNumber() > 0)
            result += dice.getModifierNumber();
    }

    return result;
}

int Dice::getDiceAmount() {
    return this->diceAmount;
}

int Dice::getFaceAmount() {
    return this->faceAmount;
}

//char Dice::getModifierOperation() {
//	return this->modifierOperation;
//}

int Dice::getModifierNumber() {
    return this->modifierNumber;
}