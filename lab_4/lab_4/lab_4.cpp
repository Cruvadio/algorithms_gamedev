#include <iostream>
#include <vector>
#include <fstream>
#include "Dice.h"

int main() {
    std::default_random_engine randGenerator;
    randGenerator.seed(time(NULL));

    std::ofstream dicesFile("dices.csv");


    int diceNumber = 3;
    int facesNumber = 10;
    int result = 0;
    std::vector<Dice> dices;
    std::vector<int> resultNumbers;

    dices.push_back(Dice(diceNumber, facesNumber));

    for (int i = 0; i < facesNumber * diceNumber; i++)
        resultNumbers.push_back(0);

    for (int i = 0; i < 10000; i++) {
        result = Dice::rollDice(dices, randGenerator);
        resultNumbers[result - 1] += 1;
    }

    for (auto i : resultNumbers)
        dicesFile << i << std::endl;
}