#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

int GetRand(int min, int max);
class Hammurabi;

int GetRand(int min, int max)
{
    srand(time(nullptr));

    int num = min + rand() % (max - min + 1);

    return num;
}

class Hammurabi {
public:
    Hammurabi() {
        ifstream save("save.txt");

        if (save) {
            cout << endl << "На вашем компьютере обнаружено сохранение" << endl;
            int load = twoOpMenu("Продолжить с последнего сохранениия", "Начать новую игру");

            if (load == 1) {
                save >> people >> wheat >> acreage >> round >> deathPerc
                    >> acresDiff >> wheatForFood >> acresForSowing >> acrPrice;
            }
            else {
                setNewGame();
            }
            save.close();

        }
        else {
            setNewGame();
            saveGame();
        }
    }

    Hammurabi(int people, int wheat, int acreage, int round, int deathPerc,
        int acresDiff, int wheatForFood, int acresForSowing, int acrPrice) {
        setVar(people, wheat, acreage, round, deathPerc, acresDiff, wheatForFood, acresForSowing, acrPrice);
    }

    void start() { startGame(); }

private:
    int people, wheat, acreage, round, deathPerc;
    int acresDiff, wheatForFood, acresForSowing, acrPrice;

    const int wheatForPerson = 20,
        acresForPerson = 10,
        wheatForAcr = 5;

    void setVar(int people, int wheat, int acreage, int round, int deathPerc,
        int acresDiff, int wheatForFood, int acresForSowing, int acrPrice) {
        this->people = people;
        this->wheat = wheat;
        this->acreage = acreage;
        this->round = round;
        this->deathPerc = deathPerc;
        this->acresDiff = acresDiff;
        this->wheatForFood = wheatForFood;
        this->acresForSowing = acresForSowing;
        this->acrPrice = acrPrice;
    }

    void setNewGame() {
        setVar(100, 2800, 1000, 1, 0,
            -1, -1, -1, -1);
    }

    static int twoOpMenu(const string& op1, const string& op2) {
        int key = -1;

        cout << endl;
        cout << "1 -> " + op1 << endl;
        cout << "2 -> " + op2 << endl;
        cout << endl;

        while (key != 1 || key != 2) {
            cin >> key;

            if (key == 1) {
                return 1;
            }
            else if (key == 2) {
                return 2;
            }
            else {
                cout << "Пожалуйста, введите один из пунктов меню" << endl;
            }
        }
    }

    void saveGame() const {
        ifstream oldSave("save.txt");
        if (oldSave) remove("save.txt");

        ofstream newSave("save.txt");
        newSave << people << " " << wheat << " " << acreage << " " << round << " " << deathPerc
            << " " << acresDiff << " " << wheatForFood << " " << acresForSowing << " " << acrPrice;

        newSave.close();
    }

    int startGame() {
        while (round <= 10) {
            int wheatPerAcr = GetRand(1, 6);
            int newWheat = acresForSowing * wheatPerAcr;
            int wheatFromSale = acresDiff < 0 ? -(acresDiff * acrPrice) : 0;

            int ratWheat = (GetRand(0, 7) / 100.0) * (wheat + newWheat);
            int wheatDiff = newWheat + wheatFromSale - ratWheat - acresForSowing * wheatForAcr;

            int hungerDeaths = wheatForFood - people * wheatForPerson >= 0 ?
                0 : (people * wheatForPerson - wheatForFood) / wheatForPerson;

            if (100 * hungerDeaths / people > 45 && round != 1) {
                round = 12;
                break;
            }

            int newPeople = hungerDeaths / 2 + (5 - wheatPerAcr) * (wheat + wheatDiff) / 600 + 1;
            if (newPeople > 50) {
                newPeople = 50;
            }
            else if (newPeople < 0) {
                newPeople = 0;
            }

            acrPrice = GetRand(17, 26);

            int plague = GetRand(1, 100) / 85.0 >= 1 ? 1 : 0;
            int plagueDeaths = plague ? (people + newPeople - hungerDeaths) / 2 : 0;

            if (round == 1) {
                cout << "Мой повелитель, позвольте мне поздравить вас с восхождением на престол, "
                    "а также описать ситуацию в царстве\n"
                    "\tНа вашем первом году правления\n"
                    "\tНаселение города сейчас составляет " << people << " человек;\n"
                    "\tВ амбарах хранится " << wheat << " бушелей пшеницы;\n"
                    "\tГород сейчас занимает " << acreage << " акров;\n"
                    "\t1 акр земли стоит сейчас " << acrPrice << " бушель." << endl;
            }
            else {
                wheat = wheat + wheatDiff - wheatForFood;
                people = people + newPeople - hungerDeaths - plagueDeaths;
                acreage += acresDiff;

                cout << "Мой повелитель, соизволь поведать тебе\n";
                cout << "\tв " << round << "-м году твоего высочайшего правления\n";
                if (hungerDeaths) {
                    cout << "\t" << hungerDeaths << " человек умерли с голоду, и "
                        << newPeople << " человек прибыли в наш великий город;\n";
                }
                else {
                    cout << "\t" << newPeople << " человек прибыли в наш великий город;\n";
                }
                if (plague) cout << "\tЧума уничтожила половину населения;\n";
                cout << "\tНаселение города сейчас составляет " << people << " человек;\n";
                cout << "\tМы собрали " << newWheat << " бушелей пшеницы, по "
                    << wheatPerAcr << " бушеля с акра;\n";
                if (ratWheat) {
                    cout << "\tКрысы истребили " << ratWheat << " бушелей пшеницы, оставив "
                        << wheat << " бушеля в амбарах;\n";
                }
                else {
                    cout << "\tВ амбарах хранится " << wheat << " бушеля пшеницы;\n";
                }
                cout << "\tГород сейчас занимает " << acreage << " акров;\n";
                cout << "\t1 акр земли стоит сейчас " << acrPrice << " бушель.\n";
            }

            acresDiff = wheatForFood = acresForSowing = -1;
            cout << "Что пожелаешь, повелитель?\n";

            while (acresDiff < -acreage || acresDiff > wheat / acrPrice
                || wheatForFood < 0 || wheatForFood > wheat - (acresDiff * acrPrice)
                || acresForSowing < 0
                || acresForSowing >(wheat - (acresDiff * acrPrice) - wheatForFood) / wheatForAcr
                || acresForSowing > people * acresForPerson) {

                int acresForSale = 0;

                cout << "Сколько акров земли повелеваешь купить?";
                cin >> acresDiff;
                cout << "Сколько акров земли повелеваешь продать?";
                cin >> acresForSale;
                acresDiff -= acresForSale;
                cout << "Сколько бушелей пшеницы повелеваешь съесть?";
                cin >> wheatForFood;
                cout << "Сколько акров земли повелеваешь засеять?";
                cin >> acresForSowing;

                if (acresDiff < -acreage || acresDiff > wheat / acrPrice
                    || wheatForFood < 0 || wheatForFood > wheat - (acresDiff * acrPrice)
                    || acresForSowing < 0
                    || acresForSowing >(wheat - (acresDiff * acrPrice) - wheatForFood) / wheatForAcr
                    || acresForSowing > people * acresForPerson) {

                    cout << "О, повелитель, пощади нас! У нас только " << people << " человек, "
                        << wheat << " бушелей пшеницы и " << acreage << " акров земли!\n";
                }
            }

            round++;
            saveGame();

            int pause = twoOpMenu("Сохранить и выйти", "Следующий раунд");
            if (pause == 1) break;
        }

        float P = deathPerc / 10.0;
        float L = acreage / people;

        if (round == 12) {
            cout << "В этот год из-за голода умерло слишком много людей, после чего "
                "в вашу спальню был подослан убийца одного из соседних царств. "
                "Воспользовавшись вашей смертью и неразберихой, оно полностью захватило "
                "все земли после вашей смерти..." << endl;
        }
        else if (round == 11 && P > 33 && L < 7) {
            cout << "Из-за вашей некомпетентности в управлении, народ устроил бунт, "
                "и изгнал вас их города. "
                "Теперь вы вынуждены влачить жалкое существование в изгнании..." << endl;
        }
        else if (round == 11 && P > 10 && L < 9) {
            cout << "Вы правили железной рукой, подобно Нерону и Ивану Грозному. "
                "Народ вздохнул с облегчением, "
                "и никто больше не желает видеть вас правителем..." << endl;
        }
        else if (round == 11 && P > 3 && L < 10) {
            cout << "Вы справились вполне неплохо, у вас, "
                "конечно, есть недоброжелатели, но многие хотели бы увидеть вас во "
                "главе города снова" << endl;
        }
        else if (round == 11) {
            cout << "Фантастика! Карл Великий, "
                "Дизраэли и Джефферсон вместе не справились бы лучше" << endl;
        }
        else return 0;

        remove("save.txt");

        setNewGame();
        int restart = twoOpMenu("Начать новую игру", "Выйти");
        if (restart == 1) {
            startGame();
        }
        else return 0;
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru");
    Hammurabi game;
    game.start();
    return 0;
}