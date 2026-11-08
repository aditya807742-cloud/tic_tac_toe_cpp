#include <array>
#include <cctype>
#include <iostream>
#include <limits>
#include <string>

using Board = std::array<std::array<char, 3>, 3>;

void displayBoard(const Board& board) {
    std::cout << "\n";
    for (int row = 0; row < 3; ++row) {
        std::cout << " ";
        for (int col = 0; col < 3; ++col) {
            std::cout << board[row][col];
            if (col < 2) {
                std::cout << " | ";
            }
        }
        std::cout << "\n";
        if (row < 2) {
            std::cout << "-----------\n";
        }
    }
    std::cout << "\n";
}

bool hasWon(const Board& board, char player) {
    // Check all rows and columns.
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    // Check both diagonals.
    return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
           (board[0][2] == player && board[1][1] == player && board[2][0] == player);
}

bool isBoardFull(const Board& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell != 'X' && cell != 'O') {
                return false;
            }
        }
    }
    return true;
}

int getMove(const Board& board, char player) {
    std::string input;

    while (true) {
        std::cout << "Player " << player << ", enter a position (1-9): ";
        if (!std::getline(std::cin, input)) {
            // Treat end-of-input as a clean request to exit.
            return -1;
        }

        if (input.size() != 1 || input[0] < '1' || input[0] > '9') {
            std::cout << "Invalid input. Please enter a number from 1 to 9.\n";
            continue;
        }

        const int position = input[0] - '1';
        const int row = position / 3;
        const int col = position % 3;

        if (board[row][col] == 'X' || board[row][col] == 'O') {
            std::cout << "That position is already occupied. Choose another one.\n";
            continue;
        }

        return position;
    }
}

bool playAgain() {
    std::string input;
    while (true) {
        std::cout << "Would you like to play again? (y/n): ";
        if (!std::getline(std::cin, input)) {
            return false;
        }

        if (input.size() == 1) {
            const char answer = static_cast<char>(std::tolower(static_cast<unsigned char>(input[0])));
            if (answer == 'y') return true;
            if (answer == 'n') return false;
        }

        std::cout << "Please enter y or n.\n";
    }
}

bool playGame() {
    Board board{{{{'1', '2', '3'}}, {{'4', '5', '6'}}, {{'7', '8', '9'}}}};
    char currentPlayer = 'X';

    std::cout << "\n========== TIC TAC TOE ==========\n";
    std::cout << "Player X and Player O take turns.\n";
    std::cout << "Choose a position using the numbers shown on the board.\n";
    displayBoard(board);

    while (true) {
        const int position = getMove(board, currentPlayer);
        if (position == -1) {
            std::cout << "\nInput closed. Exiting the game.\n";
            return false;
        }

        const int row = position / 3;
        const int col = position % 3;
        board[row][col] = currentPlayer;
        displayBoard(board);

        if (hasWon(board, currentPlayer)) {
            std::cout << "Congratulations! Player " << currentPlayer << " wins!\n";
            break;
        }

        if (isBoardFull(board)) {
            std::cout << "It's a draw! Nobody wins this round.\n";
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return true;
}

int main() {
    do {
        if (!playGame()) {
            return 0;
        }
    } while (playAgain());

    std::cout << "\nThanks for playing Tic Tac Toe. Goodbye!\n";
    return 0;
}
