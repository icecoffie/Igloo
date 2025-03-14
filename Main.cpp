#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <termios.h>

using namespace std;

const int width = 20; 
const int height = 10; 
int playerPos = width / 2; 
int snowX = rand() % width; 
int score = 0, missed = 0;

char getKey() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void drawGame() {
    system("clear"); 
    cout << "=== IGLOO CATCH ===\n";
    cout << "Gunakan 'A' dan 'D' untuk bergerak, tangkap kepingan salju! ❄️\n\n";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (y == height - 1 && x == playerPos) cout << "🐧"; 
            else if (y == 0 && x == snowX) cout << "❄️";
            else cout << ".";
        }
        cout << "\n";
    }
    cout << "\nSkor: " << score << " | Terlewat: " << missed << "/5\n";
}

void updateGame() {
    if (playerPos == snowX) {
        score++;
        snowX = rand() % width; 
    } else {
        missed++;
    }
}

void playSnowflakeCatcher() {
    while (missed < 5) {
        drawGame();
        usleep(500000); 
        
        if (system("stty raw") == 0) { 
            char move = getchar();
            if (move == 'a' && playerPos > 0) playerPos--;
            else if (move == 'd' && playerPos < width - 1) playerPos++;
            system("stty cooked"); 
        }
        updateGame();
    }
    
    cout << "\nGame Over! Skor akhir: " << score << "\n";
}

int main() {
    srand(time(0)); // Seed untuk random
    playSnowflakeCatcher();
    return 0;
}
