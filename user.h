/**
* User Interface file that deals with the inputs from the user
*
* Asks the user for the coordinates of the piece they want to move
* and where they want to move it to.Takes this coordinateand
* converts in to matrix form.
*
* @author Eamon McGill <mcgill - e@ulster.ac.uk>
* @License http ://www.gnu.org/copyleft/gpl.html
* @copyright Eamon McGill 2020
*/

#include <string>
#include "computer.h"


using namespace std;

class Interface
{
private:
	// column Input conversion
	int letterToColumn(std::string letter);

	// rown Input conversion 
	int NumberToRow(int Row);

	// 
	int startx, starty, endx, endy;
	char myColour;
	Rules check;
	Piece piece7;


public:

	// Initial startup 
	int* userInput();

	int playergo;

	//Function to allow movelegal() to check if the user has selected the correct colour
	void movePiece(Piece board[8][8]);


	// Inputs collected from user in coordinate format
	string startPos, endPos;

	// Final Array to be returned from user Input
	int* c = new int[4];

	void printLogo(void); 
};


/**
* Gets the input from the user and converts in to array form
*
* Gets the coordinates from the user and using the conversion functions,
* changes the input into an array that can work with the rest of the program
*
*
* @return returns an array of the 4 input values. 'From' x and y location as well as the 'To' x and y location
* @see Interface::letterToColumn
* @see Interface::NumberToRow
*/
int* Interface::userInput()
{

	playergo = 1;
	// Creating ASCII for input validation between A and H (a and h)
	char A = 'A';
	char H = 'H';
	char a = 'a';
	char h = 'h';
	int ascii_A = int(A);
	int ascii_H = int(H);
	int ascii_a = int(a);
	int ascii_h = int(h);

	cout << "________________________________________" << endl;
	cout << endl << "user's go... " << endl;
	cout << endl;

	cout << "Enter the coordinates of the piece you want to move. (eg A1): ";
	cin >> startPos;
	cout << endl;
	cout << "Enter the coordinates of the location you want to move to. (eg A2): ";
	cin >> endPos;

	
	while(1)
	{
		
		char startChar = startPos[0];
		int SCascii = startChar;
		int startInt = stoi(startPos.substr(1, 1));
			
		char destChar = endPos[0];
		int DCascii = destChar;
		int destInt = stoi(endPos.substr(1, 1));

		// Input validation to make sure x value falls between A and H
		if (!(SCascii >= ascii_A && SCascii <= ascii_H) && !(SCascii >= ascii_a && SCascii <= ascii_h))
		{
			cout << "Your inputted start column, " << startChar << ", is invalid." << endl;
			cout << "Enter the coordinates of the piece you want to move. (eg A1) : ";
			cin >> startPos;
			cout << endl;
		}

		// Input validation to make sure starting row value falls between 1-8
		else if (!((startInt >= 1 && startInt <= 8)))
		{
			cout << "Your inputted start row, " << startInt << ", is invalid." << endl;
			cout << "Enter the coordinates of the piece you want to move. (eg A1) : ";
			cin >> startPos;
			cout << endl;
		}

		// Input validation to make sure destination column value falls between A and H
		else if (!(DCascii >= ascii_A && DCascii <= ascii_H) && !(SCascii >= ascii_a && SCascii <= ascii_h))
		{
			cout << "Your destination column, " << destChar << ", is invalid." << endl;
			cout << "Enter the coordinates of the detination you want to move to. (eg A1) : ";
			cin >> endPos;
			cout << endl;
		}

		// Input validation to make sure destination row value falls between 1-8
		else if (!((destInt >= 1 && destInt <= 8)))
		{
			cout << "Your destination row, " << destInt << ", is invalid." << endl;
			cout << "Enter the coordinates of the destination you want to move to. (eg A3) : ";
			cin >> endPos;
			cout << endl;

		}
		else
			break;
	}
	

		cout << endl;
		cout << "You have selected the piece at " << startPos << " and want to move it to " << endPos << endl;

		//Convert input to matrix coordinates that can be used by program
		startx = letterToColumn(startPos.substr(0, 1));  // takes a sub string of the column (char) of the input 
		starty = NumberToRow(stoi(startPos.substr(1, 1)));  // takes a sub string of the row (converted to int) of the input

		endx = letterToColumn(endPos.substr(0, 1));  // takes a sub string of the column (char) of the input 
		endy = NumberToRow(stoi(endPos.substr(1, 1)));    // takes a sub string of the row (converted to int) of the input

		// Stores all input coordinates together as an array
		c[0] = startx;
		c[1] = starty;
		c[2] = endx;
		c[3] = endy;

		// for testing 
		// std::cout << "DEBUG: Starting coordinate array: " << c[0] << c[1] << " Destination coordinate array: " << c[2] << c[3];
		return c;

}



/**
* checks if the user has selected a piece that is theirs and if legal, moves this piece
*
*
* @param Piece board[8][8] an 8x8 array of "Piece" objects which represent the current chess board
* @return returns True if the selected piece is the users, otherwise False
* @see Piece::getColour()
*/
void Interface::movePiece(Piece board[8][8])
{

	myColour = board[c[0]][c[1]].getColour();

	//check selected position is a valid piece of users colour
	if (myColour == 'W')
	{
		cout << endl << endl << "THAT PIECE ISNT THE CORRECT COLOUR, TRY AGAIN!" << endl << endl;
	}
	else if (check.moveLegal(c[1], c[0], c[3], c[2], board))
	{
		board[c[3]][c[2]] = board[c[1]][c[0]]; // changing the source piece to the dest piece
		board[c[1]][c[0]] = piece7; // empty space object piece
		playergo = 0; // to change to the computer's go
		cout << endl << "Users turn is over" << endl;
	// 	cout << endl << "DEBUG: Array coordinates, from: " << c[0] << c[1] << " To: " << c[2] << c[3];
	}
	else 
		cout << endl << endl << "THAT MOVE WAS NOT LEGAL, TRY AGAIN" << endl << endl;
//		playergo = 1; // to restart the users go
}



/**
* Takes the letter character in the input coordinate and converts to corresponding matrix value
*
*
* @param letter
* @return The array value for the column input from user
*/
int Interface::letterToColumn(const std::string letter)
{
	if (letter == "A" || letter == "a") { return 0; }
	else if (letter == "B" || letter == "a") { return 1; }
	else if (letter == "C" || letter == "a") { return 2; }
	else if (letter == "D" || letter == "a") { return 3; }
	else if (letter == "E" || letter == "a") { return 4; }
	else if (letter == "F" || letter == "a") { return 5; }
	else if (letter == "G" || letter == "a") { return 6; }
	else if (letter == "H" || letter == "a") { return 7; }

}

/**
* Takes the row number from the input coordinates and converts to corresponding matrix value
*
*
* @param The array value for the row input from user
* @return The array value for the row input from user
*/

int Interface::NumberToRow(const int Row)
{
	if (Row == 1) { return 0; }
	else if (Row == 2) { return 1; }
	else if (Row == 3) { return 2; }
	else if (Row == 4) { return 3; }
	else if (Row == 5) { return 4; }
	else if (Row == 6) { return 5; }
	else if (Row == 7) { return 6; }
	else if (Row == 8) { return 7; }
}



/**
* Prints out a logo for aesthetics
*
*
*/
void Interface::printLogo(void)
// Jerome Vonk
// Chess Console Game in C++
// 2016
// https://www.codeproject.com/Articles/1214018/Chess-Console-Game-in-Cplusplus
{
	cout << "===============================================\n";
	cout << "       _____ _    _ ______  _____ _____\n";
	cout << "      / ____| |  | |  ____|/ ____/ ____|\n";
	cout << "     | |    | |__| | |__  | (___| (___ \n";
	cout << "     | |    |  __  |  __|  \\___ \\\\___ \\ \n";
	cout << "     | |____| |  | | |____ ____) |___) |\n";
	cout << "      \\_____|_|  |_|______|_____/_____/\n\n";
	cout << "===============================================\n\n";
	cout << " Created by Ruairi, Eamon, Jack, Eoin and Harry \n";
	cout << "===============================================\n\n";
}
