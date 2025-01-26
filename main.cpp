#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <ctime>


using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER


const char WALL = '#';
const char PATH = '.';
const char START = 'S';
const char ENDING = 'O';
const int WIDTH = 25;
const int HEIGHT = 10;


void loadMaze(const string& filename, char maze[HEIGHT][WIDTH], int& startRow, int& startCol);
void printMaze(char maze[HEIGHT][WIDTH]);
void gotoxy( short x, short y);
// void Timer(clock_t startTime);
// void saveScore();
// void Leaderboard(const string& scores);



int main() {
    char maze[HEIGHT][WIDTH];
    int startRow, startCol;
    loadMaze("E:\\CLionProjects1\\CLion_Projekt_Labirynt\\maze.txt", maze, startRow, startCol); //Trzeba podac full path (czemu?)
    printMaze(maze);
    bool gameOver = false;
    int x=1, y=1;

    while (!gameOver) {
        // system("CLS");
        // Timer(startTime);

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
            system("CLS");
            gotoxy(1, 30);
            printf("Koniec gry");
            // gameOver = true;
        }
    }
    // return 0;
}


//Funkcja do wczytywania maze'a z pliku .txt (https://www.w3schools.com/cpp/cpp_files.asp)
void loadMaze(const string& filename, char maze[HEIGHT][WIDTH], int& startRow, int& startCol) {
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
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
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

//Timer do dokończenia (https://www.w3schools.com/cpp/cpp_date.asp)
// void Timer(clock_t startTime) {
//     clock_t currentTime = clock();
//     double elapsed = double(currentTime - startTime) / CLOCKS_PER_SEC;
//
//     int minutes = elapsed / 60;
//     int seconds = int(elapsed) % 60;
//
//     gotoxy(1, HEIGHT + 1);
//     printf("Czas gry: %02d:%02d", minutes, seconds);
// }