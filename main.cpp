#include <iostream>
#include <random>
#include <string>

using namespace std;

class crossCanada {
    private:
    const int thirtyone[7] = { 1, 3, 5, 7, 8, 10, 12 };
    int random_count;
    int HP;
    int currentDay;
    int food;
    int currentMonth;
    int kmLeft;

    // since we get random numbers so much in the program why not make a function so we don't have to rewrite
    // the same code a bunch of times
    int getRandomNumBetween(int min, int max) {
        // you can ignore the `static` keyword for now - it would work the same without it
        static random_device rd;
        static mt19937 eng(rd());

        uniform_int_distribution<> distr(min, max);
        return distr(eng); // get a random number between min and max
    }

    void random_decrease_hp() {
        auto chance = getRandomNumBetween(1, 2);

        if (chance == 1) {
            HP--; // `--` means decrease by 1

            cout << "You have lost one health\n";
            random_count++;
        }
    }

    void add_day(int days) {
        eat_food(days);
        currentDay += days;
        add_month();
    }

    void add_month() {	
        bool hasThirtyone = false;
        int extra;

        if (random_count < 2) {
            random_decrease_hp();
        }

        for (int i = 0; i < 6;i++) {
            //checks if the current month has 31 days
            if (thirtyone[i] == currentMonth) {
                hasThirtyone = true;
            }
        }

        if (hasThirtyone == true && currentDay >= 30) {
            currentMonth++;
            random_count = 0;
            hasThirtyone = false;
            extra = currentDay - 31;
            currentDay = 1 + extra;
        }
        else if (currentDay > 29 && hasThirtyone == false) {
            currentMonth++;
            random_count = 0;
            extra = currentDay - 30;
            currentDay = 1 + extra;
        }
    }

    void eat_food(int days) {
        // for everyday player eats 5lb of food

        for (int i = 0; i < days; i++) {
            food -= 5;
        }
    }

    void travel() {
        auto distance = getRandomNumBetween(100, 500);
        kmLeft -= distance;
        //distance travelled

        auto days = getRandomNumBetween(3, 12);
        
        //days that pass
        std::cout << "You have travelled " << distance << "Km in " << days << " days\n";
        add_day(days);

    }
    void hunt() {
        auto days = getRandomNumBetween(5, 12);
        //amount of days that pass

        food += 100;
        add_day(days);

        cout << "You gained " << food << "lbs in " << days << " days\n";
    }

    void rest() {
        auto rDays = getRandomNumBetween(4, 8);
        HP++;
        add_day(rDays);
    }

    bool shouldQuit() {
        string input;
        cout << "Are you sure you would like to quit?\n1.Yes\n2.No\n";
        getline(cin, input);

        if (input == "1") {
            return true; // we want to quit
        }
        return false;
    }

    void status() {
        cout << "You have " << kmLeft << " Km left, " << HP << " HP, " << food << "lbs of food and the date is  " << currentMonth << "/" << currentDay << "/2020 and you have until 12/31/2019\n";
    }

    bool checkGameOver() {
        bool isGameOver = true;

        if (HP <= 0) {
            cout << "You ran out of HP\n";
        }
        else if (food <= 0) {
            cout << "You ran out of food\n";
        }
        else if (currentMonth >= 12) {
            cout << "You ran out of time\n";
        }
        else if (kmLeft <= 0 && HP > 0 && food > 0 && currentMonth < 13) {
            cout << "Congratuations you have won!\n";
        }
        else {
            // we didn't die or win the game so the game isn't over
            isGameOver = false;
        }

        return isGameOver;
    }

    void setVariables() {
        HP = 5;
        currentDay = 1;
        food = 500;
        currentMonth = 3;
        kmLeft = 2000;
    }

    public:
    bool GameLoop() {
        setVariables();
        cout << "Welcome to the Cross Canada Game!\n";
        
        bool runGame = true;

        while (runGame) {

            // display status
            status();

            cout << "What would you like to do?\n1.Travel\n2.Hunt\n3.Rest\n4.Quit\n";
            string action;
            getline(cin, action);

            // conver the action `string` to an `int`
            auto actionNum = std::stoi(action, nullptr, 10); // the 10 in stoi just means use base 10 (the base we use in school)

            // not sure if you've learned what a switch statement is?
            // basically it'll go to whichever case matches the value inside of `actionNum`
            switch (actionNum)
            {
            case 1:
                travel();
                break;
            case 2:
                hunt();
                break;
            case 3:
                if (HP >= 5) {
                    cout << "You have the maximum amount of HP allowed\n";
                } else {
                    rest();
                }
                break;
            case 4:
                if (shouldQuit()) { // they want to quit
                    return false;
                }
                break;
            default:
                cout << "Invalid input please enter a valid number\n";
            }

            runGame = !checkGameOver();
        }

        string retry;
        cout << "Would you like to play again?\n1.Retry\n2.Exit Game\n";
        getline(cin, retry);

        if (retry == "1") {
            return true;
        }
        return false; // end game
    }
};

int main() {
    auto game = crossCanada();

    while(game.GameLoop());
}
