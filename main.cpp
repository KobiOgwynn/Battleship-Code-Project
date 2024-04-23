// Coder/Developer: Stance Ogwynn and Adam Wolf
// Class COP 2006-13969, Spring 2024
// Date: April 8, 2024
// Description C++ Program to Play Battleship against computer

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

const int BOARD_SIZE = 8; // Define size of the game board
const int NUM_SHIPS = 5; // Define number of ships for each player

class BattleshipGame
{ // Define the BattleshipGame class
private: // Declare member variables to store player and computer boards & ship counts
    std::vector<std::vector<char>> playerBoard; // 2D vector of player's board
    std::vector<std::vector<char>> computerBoard; // 2D vector of computer's board
    int playerShips; // Number of ships player has
    int computerShips; // Number of ships computer has

public: // Constructor for initializing the game
    BattleshipGame() : playerShips(NUM_SHIPS), computerShips(NUM_SHIPS)
    { // Initialize player and computer boards with . representing empty spaces
        playerBoard = std::vector<std::vector<char>>(BOARD_SIZE, std::vector<char>(BOARD_SIZE, '.'));
        computerBoard = std::vector<std::vector<char>>(BOARD_SIZE, std::vector<char>(BOARD_SIZE, '.'));

        placeShips(playerBoard); // Place ships for player
        placeShipsRandomly(computerBoard); // Place ships for computer
    }

    void displayBoard(const std::vector<std::vector<char>>& board, bool showShips)
    { // Display game board
        std::cout << "  "; // Display column headers
        for (int intBoard = 0; intBoard < BOARD_SIZE; ++intBoard)
        {
            std::cout << " " << intBoard;
        }
        std::cout << std::endl << " +";
        for (int intColumBoarder = 0; intColumBoarder < BOARD_SIZE; ++intColumBoarder)
        { // Display column border
            std::cout << "--";
        }
        std::cout << "+" << std::endl;
        for (int intRowBoarder = 0; intRowBoarder < BOARD_SIZE; ++intRowBoarder)
        { // Display row boarder
            std::cout << intRowBoarder << " |"; // Display row number
            for (int intRowNested = 0; intRowNested < BOARD_SIZE; ++intRowNested)
            {  // Display board content for each row
                if (!showShips && board[intRowBoarder][intRowNested] == 'S')
                { // Check if ships should be hidden or if cell contains a ship S
                    std::cout << " ."; // Display a dot to represent a hidden ship
                } else
                { // Display content of cell
                    std::cout << " " << board[intRowBoarder][intRowNested];
                }
            }
            std::cout << " |" << std::endl; // Display right border for the row
        }
        std::cout << " +";
        for (int intFinishBoard = 0; intFinishBoard < BOARD_SIZE; ++intFinishBoard)
        { // Display bottom border
            std::cout << "--";
        }
        std::cout << "+" << std::endl;
    }

    void placeShips(std::vector<std::vector<char>>& board)
    { // Function to place ships on board
        std::cout << "Enter positions of your ships:" << std::endl; // Ask user to input coordinates of ships
        for (int intPosition = 0; intPosition < NUM_SHIPS; ++intPosition)
        { // Loop to place each ship
            int rowInput, columnInput;
            std::cout << "Ship " << intPosition+1 << "(row(0-7) column(0-7)): "; // Have user input coordinates of  ship
            std::cin >> rowInput >> columnInput;
            if (!isValidMove(rowInput, columnInput) || board[rowInput][columnInput] == 'S')
            { // Check if entered coordinates are valid and if cell is empty
                std::cout << "Invalid position. Try again." << std::endl;
                --intPosition; // Decrement intPosition to retry placing ship
                continue; // Skip to next iteration of loop
            }
            board[rowInput][columnInput] = 'S'; // Place ship on board at the entered coordinates
        }
    }

    bool isValidMove(int rowInput, int columnInput)
    { // Check if user input given row and column coordinates are in the valid range
        return rowInput >= 0 && rowInput < BOARD_SIZE && columnInput >= 0 && columnInput < BOARD_SIZE;
    }

    void placeShipsRandomly(std::vector<std::vector<char>>& board)
    { // To place computer's ships
        srand(time(NULL)); // Seed random number generator with the current time
        for (int intPlaceCPU = 0; intPlaceCPU < NUM_SHIPS; ++intPlaceCPU)
        { // for loop to place ships randomly on board for computer
            int rowInput, columnInput;
            do
            { // Generate random row and column coordinates until finding empty spot
                rowInput = rand() % BOARD_SIZE; // Generate random row index within board size
                columnInput = rand() % BOARD_SIZE; // Generate random column index within board size
            } while (board[rowInput][columnInput] == 'S'); // Repeat if randomly chosen spot already has ship
            board[rowInput][columnInput] = 'S'; // Place the ship
        }
    }

    void play()
    { // Continue game until either player or computer runs out of ships
        while (playerShips > 0 && computerShips > 0)
        { // Display user's board with their ships visible
            std::cout << "Your board:" << std::endl;
            displayBoard(playerBoard, true);
            // Display computer's board with only hit and miss markers visible
            std::cout << "Computer board:" << std::endl;
            displayBoard(computerBoard, false);

            int rowInput, columnInput; // Ask player to enter coordinates to attack
            std::cout << "Enter coordinates to attack (row(0-7) column((0-7)): "; // Display question
            std::cin >> rowInput >> columnInput;

            if (!isValidMove(rowInput, columnInput))
            { // Check if entered move is valid
                std::cout << "Invalid move. Try again." << std::endl; // Display Invalid move
                continue;
            }

            if (computerBoard[rowInput][columnInput] == 'S')
            { // If computer's board at entered coordinates contains a ship it is a hit
                std::cout << "Hit!" << std::endl; // Display Hit
                computerBoard[rowInput][columnInput] = 'X'; // Mark the hit on computer's board
                computerShips--; // Decrement computer ship count
            } else
            { // If computer's board at entered coordinates does not contain a ship it is a miss
                std::cout << "Miss!" << std::endl; // Display Miss
                computerBoard[rowInput][columnInput] = 'O'; // Mark the miss on the computer's board
            }

            // Computer's turn
            rowInput = rand() % BOARD_SIZE; // Computer chooses random row to attack
            columnInput = rand() % BOARD_SIZE; // Computer chooses random column to attack

            if (playerBoard[rowInput][columnInput] == 'S')
            { // If player's board at randomly chosen coordinates contains a ship it is a hit
                std::cout << "Computer hit your ship!" << std::endl; // Display computer hit user's ship
                playerBoard[rowInput][columnInput] = 'X'; // Mark hit on player's board
                playerShips--; // Decrement player ships count
            } else
            { // If player's board at randomly chosen coordinates does not contain a ship it is a miss
                std::cout << "Computer missed!" << std::endl; // Display computer missed user's ship
                playerBoard[rowInput][columnInput] = 'O'; // Mark miss on player's board
            }
        }

        if (playerShips == 0)
        { // Determine winner based on remaining ships
            std::cout << "Computer wins! All your ships are sunk." << std::endl; // Computer won
        } else
        {
            std::cout << "Congratulations! You sunk all the computer's ships!" << std::endl; // User won
        }
    }
};

int main()
{
    BattleshipGame game; // Create instance of BattleshipGame class
    game.play(); // Start game by calling the play() method of the BattleshipGame instance
    return 0;
}

