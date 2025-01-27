#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <chrono>


using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
// #define KEY_ENTER


const char WALL = '#';
const char PATH = '.';
const char START = 'S';
const char ENDING = 'O';
const int WIDTH = 25;
const int HEIGHT = 10;
string playerName;


void loadMaze(string filename, char maze[HEIGHT][WIDTH], int& startRow, int& startCol);
void printMaze(char maze[HEIGHT][WIDTH]);
void gotoxy( short x, short y);
// void Timer(int argc, char *argv[])
void Timer(chrono::time_point<chrono::high_resolution_clock> start_time);
void saveScore(string playerName, chrono::duration<int> gameTime);
auto start_time = chrono::high_resolution_clock::now(); //Czas startowy
void ShowResults();

int main() {
    char maze[HEIGHT][WIDTH];
    int startRow, startCol;
    loadMaze("maze.txt", maze, startRow, startCol); //Wczytywanie file'a
    printMaze(maze);
    ShowResults();
    bool gameOver = false;
    int x=1, y=1;

    while (!gameOver) {
        // Timer(start_time); //update zegara
        if (!gameOver) {
            Timer(start_time);
        }

        gotoxy(x,y);
        switch (getch()) {
            case KEY_UP:
                if (y>1 && maze[y-1][x] != WALL) y--;
                break;
            case KEY_DOWN:
                if (y<7 && maze[y+1][x] != WALL)y++;
                break;
            case KEY_LEFT:
                if(x>1 && maze[y][x-1] != WALL) x--;
                break;
            case KEY_RIGHT:
                if(x<24 && maze[y][x+1] != WALL)x++;
                break;
        }
        if (x==23 && y==7) {
            // system("CLS");
            gotoxy(0, 9);
            printf("Koniec gry");
            gameOver = true;
        }
    }
    auto gameTime = chrono::high_resolution_clock::now() - start_time;
    chrono::duration<int> seconds = chrono::duration_cast<chrono::seconds>(gameTime);
    gotoxy(0, 11);
    cout << "Podaj nazwe: ";
    cin >> playerName;
    saveScore(playerName, seconds);
    system("pause");
    // return 0;
}


//Funkcja do wczytywania maze'a z pliku .txt (https://www.w3schools.com/cpp/cpp_files.asp)
void loadMaze(string filename, char maze[HEIGHT][WIDTH], int& startRow, int& startCol) {
    ifstream file(filename);

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            file >> maze[i][j];
            if (maze[i][j] == START) {
                startRow = i;
                startCol = j;
            }
        }
    }

    file.close();
}


//Print'owanie maze'a
void printMaze(char maze[HEIGHT][WIDTH]) {
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < HEIGHT-1; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (maze[i][j] == ENDING) {
                SetConsoleTextAttribute(hConsole, 12);
            }
            if (maze[i][j] == WALL) {
                SetConsoleTextAttribute(hConsole, 9);
            }
            if (maze[i][j] == PATH) {
                SetConsoleTextAttribute(hConsole, 2);
            }
            cout << maze[i][j];
        }
        cout << endl;
    }
}

//Kursor (bazowany na sudoku)
void gotoxy(short x, short y) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x, y };
    SetConsoleCursorPosition(hStdout, position);
}

// void Timer(int argc, char *argv[]) {
//     auto start_time = chrono::high_resolution_clock::now();
//     auto current_time = chrono::high_resolution_clock::now();
//     gotoxy(35, 1);
//     cout << "Czas gry: " << chrono::duration_cast<chrono::seconds>(current_time - start_time).count() << " seconds" << endl;
// }

//Funkcja zegara
void Timer(chrono::time_point<chrono::high_resolution_clock> start_time) {
    auto current_time = chrono::high_resolution_clock::now();
    gotoxy(35, 1);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
    cout << "Czas gry: " << chrono::duration_cast<chrono::seconds>(current_time - start_time).count() << " sekund" << endl;
}


void saveScore(string playerName, chrono::duration<int> gameTime) {
    ofstream outFile("scores.txt", ios::app);  //iosapp do zapisywania wynikow w kolejnym wierszu
    if (outFile.is_open()) {
        outFile << playerName << ": " << gameTime.count() << " sekund" << endl;
        outFile.close();
        cout << "Zapisano wynik" << endl;
    }
}

//FUnkcja do wyswietlania tabeli wynikow z pliku scores.txt (wyniki sa zapisywane w saveScore())
void ShowResults() {
    ifstream inFile("scores.txt");
    string line;
    gotoxy(35, 2);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 3);
    cout << "Tablica wynikow: ";
    if (inFile.is_open()) {
        for (int i = 2; i < 40; i++) {
            getline(inFile, line);
            gotoxy(35, i+1);
            cout << line;
        }
        inFile.close();
    }
}