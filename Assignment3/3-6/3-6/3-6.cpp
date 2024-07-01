#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Player; // Forward declaration

class TaggerState {
public:
    virtual void toward(Player* player) = 0;
    virtual string getState() = 0;
};

class Back : public TaggerState {
public:
    void toward(Player* player) override;
    string getState() override { return "Back"; }
};

class Front : public TaggerState {
public:
    void toward(Player* player) override;
    string getState() override { return "Front"; }
};

class Player {
private:
    TaggerState* state;
    int progress;

public:
    Player() : state(new Back()), progress(0) {}
    ~Player() { delete state; }

    void SetState(TaggerState* newState) {
        delete state;
        state = newState;
    }

    void toward() {
        state->toward(this);
    }

    int GetProgress() {
        return progress;
    }

    void MoveForward() {
        progress++;
    }

    TaggerState* GetState() {
        return state;
    }
};

void Back::toward(Player* player) {
    cout << "Green Light!" << endl;
    int randNum = rand() % 5 + 2;  // Random number between 2 and 6

    for (int i = 0; i < randNum; i++) {
        if (player->GetProgress() >= 20) {
            return;
        }

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(player->GetProgress()), 0 });
       // cout << "@";
        player->MoveForward();
        Sleep(1000);
    }

    player->SetState(new Front());
}

void Front::toward(Player* player) {
    cout << "Red Light!" << endl;
    int waitTime = rand() % 9 + 2;  // Random time between 2 and 10 seconds
    Sleep(waitTime * 1000);
    player->SetState(new Back());
}

int main() {
    srand((unsigned int)time(0));
    Player player;
    int cursor = 0;

    while (true) {
        player.toward();

        if (player.GetProgress() >= 20) {
            cout << "\nYou Win!" << endl;
            break;
        }

        if (_kbhit()) {
            char input = _getch();
            if (input == 77) {  // Right arrow key
                if (player.GetState()->getState() == "Front") {
                    cout << "\nYou Lose!" << endl;
                    break;
                }
                else {
                    player.MoveForward();
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(player.GetProgress()), 7 });
                    cout << "@";
                    cursor++;
                }
            }
        }

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 3 });
        cout << "Progress: ";
        for (int i = 0; i < player.GetProgress(); i++) {
            cout << "@";
        }
        for (int i = player.GetProgress(); i < 20; i++) {
            cout << "-";
        }
        cout << " (" << player.GetProgress() << "/20)";

        if (player.GetProgress() >= 20) {
            cout << "\nYou Win!" << endl;
            break;
        }
    }

    return 0;
}
