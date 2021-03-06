// Practica1CarlosHD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/********/

const int BULLET_AMOUNT_POSITIONS_TO_FIRST_BIT = 16;
const int BULLET_AMOUNT_ORIGINAL_POSITION_BITMASK = 0x00FF0000;
const int BULLET_AMOUNT_FIRST_BIT_POSITION_BITMASK = 0x000000FF;

const int INFINITE_BULLETS_POSITIONS_TO_FIRST_BIT = 1;
const int INFINITE_BULLETS_ORIGINAL_POSITION_BITMASK = 0x00000002;
const int INFINITE_BULLETS_FIRST_BIT_POSITION_BITMASK = 0x00000001;

/********/


/********/

int getBulletCount(int characterData);
void addBullets(int &characterData, int bulletsToAdd);
bool hasInfiniteBullets(int characterData);
void setInfiniteBullets(int &characterData, bool doActivate);

/********/


/**
Returns the current number of bullets of the character

@param characterData The integer containing the character data
@return The current number of bullets of the character
*/
int getBulletCount(int characterData)
{
	// Moves the bullet amount bytes to the first bit position and then sets the other bytes to 0, returning the lowest possible integer with the bullet amount value.
	// This way, as the mask is applied after shifting the bytes, the result is the same wheter the number is negative or positive.
	int bulletCount = ((characterData >> BULLET_AMOUNT_POSITIONS_TO_FIRST_BIT) & BULLET_AMOUNT_FIRST_BIT_POSITION_BITMASK);

	return bulletCount;
}



/**
Adds a positive or negative number of bullets to the current character amount of bullets. Bullets cannot be lower than 0.

@param characterData Reference to the integer containing the character data. The value of the current bullets will be overwritten.
@param bulletsToAdd Number of bullets to be added. It can be both a negative or positive value. If it is greater than 255, it will be treated as if it would be 255.
*/
void addBullets(int &characterData, int bulletsToAdd)
{
	int currentBulletCount = getBulletCount(characterData);
	int newBulletCount = currentBulletCount + bulletsToAdd;

	if (newBulletCount > 255)
		newBulletCount = 255; // The amount of bullets cannot be stored in more than 2 bytes. Its greatest assignable value is 255.
	else if (newBulletCount < 0)
		newBulletCount = 0; // The amount of bullets cannot be a negative value.

							// Moves the bytes which contain the bullet amount to its final position.
	newBulletCount <<= BULLET_AMOUNT_POSITIONS_TO_FIRST_BIT;

	// Sets the bullet amount bytes to 0, maintaining the other bytes unchanged.
	characterData &= ~BULLET_AMOUNT_ORIGINAL_POSITION_BITMASK;

	// Finally, sets the new value to the bullet amount, maintaining the other bytes unchanged as newBulletCount had every other byte set to 0 at this point.
	characterData |= newBulletCount;
}



/**
Returns the current state of the infinite bullets flag.

@param characterData The integer containing the character data
@return A boolean value: true if the flag is activated, false otherwise.
*/
bool hasInfiniteBullets(int characterData)
{
	// Sets the bytes that don't belong to the infinite bullets flag to 0.
	int infiniteBulletFlag = characterData & INFINITE_BULLETS_ORIGINAL_POSITION_BITMASK;

	return (infiniteBulletFlag != 0);
}


/**
Activates or deactivates the infinite bullets flag in a character.

@param characterData Reference to the integer containing the character data. The value of the infinite bullets state will be overwritten.
@param bulletsToAdd Number of bullets to be added. It can be both a negative or positive value. If it is greater than 255, it will be treated as if it would be 255.
*/
void setInfiniteBullets(int &characterData, bool doActivate)
{
	if (doActivate)
		characterData |= INFINITE_BULLETS_ORIGINAL_POSITION_BITMASK;
	else
		characterData &= ~INFINITE_BULLETS_ORIGINAL_POSITION_BITMASK;
}



int main()
{
	int characterData = 0;
	int bulletsToAdd = 0;
	char optionSelected;
	bool showPressAnyKey = true;

	do {

		printf("\n\n");
		printf("Current character data: 0x%08x\n", characterData);
		printf("\nSelect an option:\n");
		printf("\n1 - Display current bullet amount");
		printf("\n2 - Add bullets");
		printf("\n3 - Display infinite bullets state");
		printf("\n4 - Activate infinite bullets");
		printf("\n5 - Dectivate infinite bullets");
		printf("\n6 - Introduce complete character data");
		printf("\nq - Quit");
		printf("\n\n");

		scanf_s("%s", &optionSelected, 2);

		switch (optionSelected)
		{
		case '1': // Display current bullet amount
			printf("\n\nCurrent bullet amount: %d", getBulletCount(characterData));
			break;

		case '2': // Add bullets
			printf("\n\nEnter the number of bullets to add: ");
			scanf_s("%d", &bulletsToAdd);
			addBullets(characterData, bulletsToAdd);
			printf("\nThe character has now %d bullets", getBulletCount(characterData));
			break;

		case '3': // Display infinite bullets state
			printf("\n\nInfinite bullets: %s", hasInfiniteBullets(characterData) ? "yes" : "no");
			break;

		case '4': // Activate infinite bullets
			setInfiniteBullets(characterData, true);
			printf("\n\nInfinite bullets activated");
			break;

		case '5': // Dectivate infinite bullets
			setInfiniteBullets(characterData, true);
			printf("\n\nInfinite bullets deactivated");
			break;

		case '6': // Introduce character data
			printf("\n\nEnter character data: ");
			scanf_s("%d", &characterData);
			break;

		default: // Quit
			optionSelected = 'q';
			showPressAnyKey = false;
			break;
		}

		if (showPressAnyKey)
		{
			printf("\nPress any key to continue...");
			while ('\n' != getchar());
			getchar(); // wait for ENTER
		}

	} while ('q' != optionSelected && 'Q' != optionSelected);

	return 0;
}