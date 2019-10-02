#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <windows.h>
using namespace std;

void getPlayerSymbols(char& aiPlayer, char& huPlayer);
void rematch(char& playAgain);
void printBoard(char currentPlayer[], char aiPlayer, int aiScore, char huPlayer, int huScore);
bool gameWon(char player, char board[]);
int randomIndexGenerator(vector<int> vect);
int randomIndexGenerator(vector<pair<int, int>> vect);
vector<int> emptyIndices(char board[]);
void getMove(char currentPlayer, char board[], int turn, char aiPlayer, char huPlayer);
pair<int, int> miniMax(char currentPlayer, char board[], char aiPlayer, char huPlayer);

int main() {
	char aiPlayer = ' ';													// X or O for AI player
	char huPlayer = ' ';													// X or O for user
	char currentPlayer = ' ';												// X or O for the player whose turn it currently is
	int aiScore = 0;														// Number of matches won by the AI
	int huScore = 0;														// Number of matches won by the human player
	char playAgain = 'Y';													// Holds a value indiciating whether or not the player would like to play another round
	int turn;																// Counter storing the number of turns taken in a given round
	int match = 0;															// Counter storing the number of matches that have been played
	string gameOver;														// Message to be displayed to the player when a round has ended

	getPlayerSymbols(aiPlayer, huPlayer);									// Prompt user to choose a symbol & assign other symbol to AI player

	while (playAgain == 'Y' || playAgain == 'y')
	{
		match++;															// Increment match counter
		turn = 1;															// Reset turn counter
		char board[9] = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };	// Reset the board

		while (!gameWon(currentPlayer, board) && turn <= 9)					// Loop until game is over
		{
			if (match % 2 == 1)
				currentPlayer = (turn % 2 == 1) ? huPlayer : aiPlayer;		// Player gets first turn on odd matches
			else
				currentPlayer = (turn % 2 == 1) ? aiPlayer : huPlayer;		// Computer gets first turn on even matches

			printBoard(board, aiPlayer, aiScore, huPlayer, huScore);		// Update board
			getMove(currentPlayer, board, turn, aiPlayer, huPlayer);		// Get the next move from player/AI
			turn++;															// Increment the turn counter
		}
		printBoard(board, aiPlayer, aiScore, huPlayer, huScore);			// Print terminal board

		if (gameWon(currentPlayer, board))
		{
			// Declare winner & update score
			if (currentPlayer == aiPlayer)
			{
				aiScore++;
				gameOver = "The computer wins!";
			}
			else
			{
				huScore++;
				gameOver = "You win!";
			}

			printBoard(board, aiPlayer, aiScore, huPlayer, huScore);
			cout << gameOver;
		}
		else
			cout << "It's a draw!";

		rematch(playAgain);													// Ask for rematch
	}
}

// Prints symbol passed to function in common output in either red or blue font color depending on the symbol (X/O)
void printInColor(char symbol) {
	if (symbol == 'X')
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);		// Set console text output color to light Red
	else if (symbol == 'O')
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);		// Set console text output color to light Blue

	cout << symbol;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);			// Set console text output color to bright White (Default)
}

// Prints the current board state to the user
void printBoard(char board[], char aiPlayer, int aiScore, char huPlayer, int huScore) {
	system("cls");
	cout << "\n       Tic Tac Toe\n" << "\nPlayer (" << huPlayer << ")  -  Computer (" << aiPlayer << ")\n";
	cout << "Wins: " << huScore << "          Wins: " << aiScore << endl << endl;

	cout << "         |     |     " << endl << "      ";
	printInColor(board[0]);
	cout << "  |  ";
	printInColor(board[1]);
	cout << "  |  ";
	printInColor(board[2]);
	cout << "      " << endl << "    _____|_____|_____" << endl << "         |     |     " << endl << "      ";
	printInColor(board[3]);
	cout << "  |  ";
	printInColor(board[4]);
	cout << "  |  ";
	printInColor(board[5]);
	cout << "      " << endl << "    _____|_____|_____" << endl << "         |     |     " << endl << "      ";
	printInColor(board[6]);
	cout << "  |  ";
	printInColor(board[7]);
	cout << "  |  ";
	printInColor(board[8]);
	cout << "      " << endl << "         |     |     " << endl << endl;
}

// Returns true if the board has reached a terminal state; false otherwise
bool gameWon(char player, char board[]) {
	if (board[0] == player && board[1] == player && board[2] == player ||
		board[3] == player && board[4] == player && board[5] == player ||
		board[6] == player && board[7] == player && board[8] == player ||
		board[0] == player && board[3] == player && board[6] == player ||
		board[1] == player && board[4] == player && board[7] == player ||
		board[2] == player && board[5] == player && board[8] == player ||
		board[0] == player && board[4] == player && board[8] == player ||
		board[2] == player && board[4] == player && board[6] == player)
		return true;
	return false;
}

// Prompts user to input whether they would like to play as Xs or Os and stores their choice
void getPlayerSymbols(char& aiPlayer, char& huPlayer) {
	string input;

	cout << "Enter your choice of symbol X/O: ";
	getline(cin, input);
	huPlayer = input[0];

	if (huPlayer == 'O' || huPlayer == 'o')
	{
		huPlayer = 'O';
		aiPlayer = 'X';
	}
	else if (huPlayer == 'X' || huPlayer == 'x')
	{
		huPlayer = 'X';
		aiPlayer = 'O';
	}
	else
		getPlayerSymbols(aiPlayer, huPlayer);
}

// Prompts for, and stores, player input as to whether they would like to play another round or end the game
void rematch(char& playAgain) {
	string input;

	cout << "\nRematch? (Y/N): ";
	getline(cin, input);
	playAgain = input[0];

	if (playAgain != 'Y' && playAgain != 'y' && playAgain != 'N' && playAgain != 'n')
		rematch(playAgain);
}

// Randomly generates an integer within the range of indices of the passed vector
int randomIndexGenerator(vector<int> vect) {
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<int> distribution(0, vect.size() - 1);

	return distribution(generator);
}

// Randomly generates an integer within the range of indices of the passed vector
int randomIndexGeneratorP(vector<pair<int, int>> vect) {
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<int> distribution(0, vect.size() - 1);

	return distribution(generator);
}

// Returns a vector of indices of the array representing the game board which have not yet been played
vector<int> emptyIndices(char board[]) {
	vector<int> indices;

	for (int i = 0; i < 9; i++)
		if (board[i] != 'O' && board[i] != 'X')
			indices.push_back(board[i] - '0');

	return indices;
}

// Determines and plays the next move (automatically for the AI; prompts human player for input)
void getMove(char currentPlayer, char board[], int turn, char aiPlayer, char huPlayer) {
	string input = "yeet";														// Stores user input for human move choice
	int c = -1;																	// Stores human player move choice
	pair<int, int> choice;														// Stores AI move choice

	if (currentPlayer == aiPlayer)
	{
		if (turn == 1)															// Choose a corner space on first move
		{
			vector<int> vect = { 0, 2, 6, 8 };
			board[vect[randomIndexGenerator(vect)]] = currentPlayer;			// Update board with corner space move
		}
		else if (turn == 2 && board[0] == huPlayer ||							// Choose the middle space on second move if human player chose a corner
			turn == 2 && board[2] == huPlayer ||
			turn == 2 && board[6] == huPlayer ||
			turn == 2 && board[8] == huPlayer)
			board[4] = currentPlayer;											// Update board with middle space move
		else
		{
			choice = miniMax(currentPlayer, board, aiPlayer, huPlayer);			// Determine best move choice using the miniMax algorithm
			board[choice.second] = currentPlayer;								// Update board with best move determined by miniMax algorithm
		}
	}
	else
	{
		while (c < 0 || c > 8 || input.length() != 1)							// Loop until received valid input from human player
		{
			cout << "Please enter a number: ";									// Prompt for move choice
			getline(cin, input);												// Store entered line of input

			if (input.length() == 1)
				c = input[0] - '0';												// Convert input to an integer value

			if (c >= 0 && c <= 8)												// Verify that inputted integer is within the range of the board array indices
			{
				vector<int> available = emptyIndices(board);					// Vector of valid move choices for the player
				bool valid = false;

				for (int i = 0; i < available.size(); i++)
				{
					if (c == available[i])										// Verify that the index choice made by the human player hasn't already been played in the current round
						valid = true;
				}

				if (valid == false)
					c = -1;
				else
					board[c] = currentPlayer;									// Update board with move if the move is valid
			}
		}
	}
}

// Given the current state of the board, calculates and returns the best move for the AI to make
pair<int, int> miniMax(char currentPlayer, char newBoard[], char aiPlayer, char huPlayer) {
	vector<int> availableSpaces = emptyIndices(newBoard);						// Create vector of playable board spaces

	pair<int, int> r;															// Index, score
	if (gameWon(huPlayer, newBoard))											// Return score of -10 if hu wins
	{
		r.first = -10;
		return r;
	}
	else if (gameWon(aiPlayer, newBoard))										// Return score of 10 if AI wins
	{
		r.first = 10;
		return r;
	}
	else if (availableSpaces.size() == 0)										// Return score of 0 in the instance of a draw
	{
		r.first = 0;
		return r;
	}

	pair<int, int> result;														// Used to store the respective score & index of a move returned by a recursive call of the miniMax function
	vector<pair<int, int>> moves;												// Used to store list of potential move scores & board indices

	for (int i = 0; i < availableSpaces.size(); i++)							// Loop through all possible moves
	{
		pair<int, int> move;													// Used to store a potential move's score & index
		move.second = availableSpaces[i];										// Store the index of the current available move being evaluated

		newBoard[availableSpaces[i]] = currentPlayer;							// Update the simulated board with the current move choice

		if (currentPlayer == aiPlayer)											// Call miniMax function to evaluate the remaining branches of the decision tree
			result = miniMax(huPlayer, newBoard, aiPlayer, huPlayer);
		else
			result = miniMax(aiPlayer, newBoard, aiPlayer, huPlayer);

		move.first = result.first;												// Store the returned score of the move being evaluated during this iteration of the loop

		newBoard[availableSpaces[i]] = '0' + static_cast<char>(move.second);	// Reset the simulated board to its previous state prior to playing the move we evaluated

		moves.push_back(move);													// Add this move (score/index) to our running list of evaluated potential moves for the AI
	}

	if (currentPlayer == aiPlayer)
		sort(moves.begin(), moves.end(), greater<>());							// Sort list of evaluated potential moves in descending order of score
	else
		sort(moves.begin(), moves.end());										// Sort list of evaluated potential moves in ascending order of score

	for (int i = 1; i < moves.size(); i++)
		if (moves[i].first != moves[i - 1].first)
			moves.erase(moves.begin() + i, moves.end());						// Remove any moves from the list whose scores are not tied for the best score

	return moves[randomIndexGeneratorP(moves)];									// Randomly choose a move from the list
}