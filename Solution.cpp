#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <vector>
#include <iomanip>


#define BOARD_SIZE 8

using namespace std;

//a knight has a maximum of 8 possible moves
const int MOVES_COUNT = 8;

//arrays with all possible moves
const int HORIZONTAL_MOVES[MOVES_COUNT] = { -2, -1, 1, 2, -2, -1, 1, 2 };
const int VERTICAL_MOVES[MOVES_COUNT] = { 1, 2, 2, 1, -1, -2, -2, -1 };

//checks if a move is valid by
//making sure it doesn't go out of board range
bool isMoveValid(int posX, int posY) {
    return (posX >= 0 && posX < BOARD_SIZE) && (posY >= 0 && posY < BOARD_SIZE);
}

//calculates number of possible moves from a certain position
int calculateOnwardMoves(int posX, int posY, int chessBoard[BOARD_SIZE][BOARD_SIZE]) {
    int moveOptions = 0;
    for (int j = 0; j < MOVES_COUNT; j++) {
        int nextX = posX + HORIZONTAL_MOVES[j];
        int nextY = posY + VERTICAL_MOVES[j];
        if (isMoveValid(nextX, nextY) && chessBoard[nextY][nextX] == 0) {
            moveOptions++;
        }
    }
    return moveOptions;
}

//a custom comparator struct defines operator function
//compares two pairs of ints based on their first element
struct MovesComparator {
    bool operator()(pair<int, int> moveA, pair<int, int> moveB) {
        return moveA.first > moveB.first;
    }
};

int main() {
    int chessBoard[BOARD_SIZE][BOARD_SIZE] = {};
    //randomize the knight's initial position
    int knightX = rand() % BOARD_SIZE;
    int knightY = rand() % BOARD_SIZE;
    int minimumMoves = 0;

    //define a prioity queue "movesQueue"
    //pairs are ordered in queue based on
    //previously defined comparator struct "MovesComparator"
    priority_queue<pair<int, int>, vector<pair<int, int>>, MovesComparator> movesQueue;


    for (int move = 0; move < BOARD_SIZE * BOARD_SIZE; move++) {
        chessBoard[knightY][knightX] = move + 1;
        while (!movesQueue.empty()) movesQueue.pop();

        //fills the movesQueue
        //each knight can move a max of 8 moves
        //hence the condition i < 8
        for (int i = 0; i < MOVES_COUNT; i++) {
            int nextX = knightX + HORIZONTAL_MOVES[i];
            int nextY = knightY + VERTICAL_MOVES[i];

            //check that move is valid, and not already visited
            if (isMoveValid(nextX, nextY) && chessBoard[nextY][nextX] == 0) {
                int moveOptions = calculateOnwardMoves(nextX, nextY, chessBoard);
                
                //push to the queue a pair of 
                //number of moves possible and the move index
                //this queue is then ordered descendingly
                //based on number of possible moves
                movesQueue.push(make_pair(moveOptions, i));
            }
        }

        //choose the move with the highest number of possible moves
        if (!movesQueue.empty()) {

            //selected move is represented as 
            //the index of selected x and y
            int selectedMove = movesQueue.top().second;
            movesQueue.pop();
            knightX += HORIZONTAL_MOVES[selectedMove];
            knightY += VERTICAL_MOVES[selectedMove];
            minimumMoves++;
        }
        else {
            break;
        }
    }


    //prints the chessboard
    for (int y = 0; y < BOARD_SIZE; y++) {
        cout << "  +----+----+----+----+----+----+----+----+\n";
        cout << setw(2) <<  "  |";
        for (int x = 0; x < BOARD_SIZE; x++) {
            cout << setw(4) << chessBoard[y][x] << "|";
        }
        cout << "\n";
    }
    cout << "  +----+----+----+----+----+----+----+----+\n";
    cout << "The minimum number of moves = " << minimumMoves;


    return 0;
}
