#include<iostream>
#include <cstdlib>
#include<deque>
#include<vector>
#include<conio.h>
#include<time.h>
using namespace std;

class cplayer {
public:
    int x, y;
    cplayer(int startX, int startY) : x(startX), y(startY) {}
};

class clane {
private:
    deque<bool> cars;
    bool right;
public:
    clane(int width) {
        for (int i = 0; i < width; i++) {
            cars.push_front(true);
            right = rand() % 2;
        }
    }
    void Move() {
        if (right) {
            if (rand() % 10 == 1) {
                cars.push_front(true);
            }
            else {
                cars.push_front(false);
                cars.pop_back();
            }
        }
        else {
            if (rand() % 10 == 1) {
                cars.push_back(true);
            }
            else {
                cars.push_back(false);
                cars.pop_front();
            }
        }
    }
    bool CheckPos(int pos) {
        return cars[pos];
    }
};

class cGame {
private:
    bool quit;
    int numberofLanes;
    int width;
    int score1, score2;
    cplayer* player1;
    cplayer* player2;
    vector<clane*> map;

public:
    cGame(int w = 20, int h = 10) {
        numberofLanes = h;
        width = w;
        quit = false;
        score1 = score2 = 0;

        for (int i = 0; i < numberofLanes; i++) {
            map.push_back(new clane(width));
        }

        player1 = new cplayer(width / 3, numberofLanes - 1);
        player2 = new cplayer(2 * width / 3, numberofLanes - 1);
    }

    ~cGame() {
        delete player1;
        delete player2;
        for (int i = 0; i < map.size(); i++) {
            clane* current = map.back();
            map.pop_back();
            delete current;
        }
    }

    void Draw() {
        // Clear the console by printing newlines
        for (int i = 0; i < 50; i++) {
            cout << endl;
        }

        for (int i = 0; i < numberofLanes; i++) {
            for (int j = 0; j < width; j++) {
                if (i == 0 && (j == 0 || j == width - 1)) {
                    cout << "S";
                }
                if (i == numberofLanes - 1 && (j == 0 || j == width - 1)) {
                    cout << "F";
                }
                if (map[i]->CheckPos(j) && i != 0 && i != numberofLanes - 1) {
                    cout << "#";
                }
                else if (player1->x == j && player1->y == i) {
                    cout << "1";
                }
                else if (player2->x == j && player2->y == i) {
                    cout << "2";
                }
                else {
                    cout << " ";
                }
            }
            cout << endl;
        }
        cout << "Score Player 1: " << score1 << "\tScore Player 2: " << score2 << endl;
    }

    void Input() {
        if (_kbhit()) {
            char current = _getch();
            if (current == 'a') {
                player1->x--;
            }
            if (current == 'd') {
                player1->x++;
            }
            if (current == 'w') {
                player1->y--;
            }
            if (current == 's') {
                player1->y++;
            }

            if (current == 'j') {
                player2->x--;
            }
            if (current == 'l') {
                player2->x++;
            }
            if (current == 'i') {
                player2->y--;
            }
            if (current == 'k') {
                player2->y++;
            }

            if (current == 'q') {
                quit = true;
            }
        }
    }

    void Logic() {
        for (int i = 1; i < numberofLanes - 1; i++) {
            if (rand() % 10 == 1) {
                map[i]->Move();
                if ((map[i]->CheckPos(player1->x) && player1->y == i) ||
                    (map[i]->CheckPos(player2->x) && player2->y == i)) {
                    quit = true;
                }
            }
        }

        if (player1->y == numberofLanes - 1) {
            score1++;
            player1->y = 0;
            cout << "\x07";
        }

        if (player2->y == numberofLanes - 1) {
            score2++;
            player2->y = 0;
            cout << "\x07";
        }
    }

    void Run() {
        while (!quit) {
            Input();
            Draw();
            Logic();
        }
    }
};

int main() {
    srand(time(NULL));
    cGame game(30, 5);
    game.Run();
    cout << " Game over!" << endl;
    getchar();
    return 0;
}

