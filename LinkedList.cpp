/*******************************************************************************************
* File Name          : dataStructureAssignmentFirst.c
* Description        : Prog8130 - Assignment 1: Linked Lists
*					   This program uses linked lists to hold and print a list of words
*					   organized by index number assosciated with each word. Each word can
*					   consist of maximum 30 characters.
*
* Author:            :  Sinan KARACA - 8743013
* Date:              :  03.10.2021
********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_DATA_ITEMS   10				// the number of data items to be used in list

int globalIndex = 0;

// structure/typedef used for holding data
typedef struct {
	char name[30];
	int index;
} inputData;

// definition of linked list data nodes
typedef struct LinkedListNode {
	struct LinkedListNode* ptrNextNode;		// pointer to next node in list (NULL if the end)
	char   NameData[30];		// the name to be stored (no need to store index)
} LinkedListNodeDef;

// prototypes
LinkedListNodeDef* AddToLinkedList(LinkedListNodeDef* ptrHead, char* NameData, int DataIndex);
void PrintLinkedList(LinkedListNodeDef* ptrHead);
void deleteNode(LinkedListNodeDef* ptrHead, int DataIndex);
void clear(void);

// Used the following data in your assignment #1
inputData iData[10] = {
		{ "fish", 5 },
		{ "car", 7 },
		{ "carrot", 4 },
		{ "pickels", 8 },
		{ "airplane", 6 },
		{ "chocolate", 9 },
		{ "allan", 7 },
		{ "butter", 4 },
		{ "water", 1 },
		{ "milk", 8 }
};
//end of data for assignment

// Correct order after inserting into list is:
// 1. water
// 2. fish
// 3. car
// 4. carrot
// 5. butter
// 6. pickels
// 7. airplane
// 8. milk
// 9. chocolate
// 10. allan


// make the data positions the last 5 digits of student number
// for example if my student number ended in 94330 the data will be as supplied

// data used for test
// paste the data here that was created by Prog8130Assign1DataCreator.exe




// FUNCTION      : clear()
// DESCRIPTION   : Function used for clearing scanf buffer
// PARAMETERS    : NONE
// RETURNS       : NONE

void clear(void) {
	int c;
	while ((c = getchar() != '\n' && c != EOF));
}



int main(void) {

	int i;

	int opt;
	int retValue = 0;
	char name[30] = { "\n" };

	// define linked list head
	struct LinkedListNode* ptrHead = NULL;

	// Print out the input data
	printf("Data before Linked List is:\n");
	for (i = 0; i < NUMBER_OF_DATA_ITEMS; i++) {
		printf("%s , %d\n", iData[i].name, iData[i].index);
	}


	// insert the data into Linked List
	for (i = 0; i < NUMBER_OF_DATA_ITEMS; i++) {
		globalIndex = globalIndex + 1;
		ptrHead = AddToLinkedList(ptrHead, iData[i].name, iData[i].index);
	}


	while (1) {

		printf("\n ***************************************\n");
		printf("\n *  Linked list operations:            *\n");
		printf("\n *  1. Print the whole list            *\n");
		printf("\n *  2. Add an element to the list      *\n");
		printf("\n *  3. Delete an element in the list   *\n");
		printf("\n *  4. Quit						     *\n");
		printf("\n ***************************************\n");
		printf("\n Choose an option [1-3] :				  \n");

		retValue = scanf_s("%d", &opt);

		if (opt < 1 || opt > 4 || retValue != 1) {
			printf(" *Error: Invalid input. Try again. ***\n");
		}
		clear();

		if (opt == 1) {
			PrintLinkedList(ptrHead);
		}
		else if (opt == 2) {

			printf("\n *  Enter Name :                   *\n");
			retValue = scanf_s("%[^\n]s", name, 30);
			clear();

			printf("\n *  Enter Index Number :           *\n");
			retValue = scanf_s("%d", &opt);
			if (retValue == 1) {
				ptrHead = AddToLinkedList(ptrHead, name, opt);
			}
			else {
				printf(" *Error: Invalid input. Try again. ***\n");
			}

			clear();
		}
		else if (opt == 3) {

			printf("\n *  Enter the position of element :    *\n");
			retValue = scanf_s("%d", &opt);
			deleteNode(ptrHead, opt);
			clear();
		}
		else if (opt == 4) {
			return 0;
		}
	}
}


// FUNCTION      : deleteNode()
// DESCRIPTION   : This function takes ptrHead and DataIndex Inputs,
//    Note that: Data index input used as list index parameter
// PARAMETERS    :
// 				   char *NameData				- Array of Characters with data 
//		           int DataIndex				- Index of list
// RETURNS       : NONE
void deleteNode(LinkedListNodeDef* ptrHead, int DataIndex) {
	struct LinkedListNode* deletedNode = NULL;
	LinkedListNode* currentNode = ptrHead;

	for (int i = 2; i < DataIndex; i++) {

		currentNode = currentNode->ptrNextNode;
	}

	deletedNode = currentNode->ptrNextNode;
	currentNode->ptrNextNode = currentNode->ptrNextNode->ptrNextNode;


	//Free the correspounding area
	free(deletedNode);
}



// FUNCTION      : AddToLinkedList()
// DESCRIPTION   : This function takes an input of Data of 30 Char word and an index and 
//				   places them in a linked list organized by priority of index number. 
// PARAMETERS    : LinkedListNodeDef *ptrHead	- variable to store address of ptrHead
//				   char *NameData				- Array of Characters with data 
//		           int DataIndex				- Index of data
// RETURNS       : possibly updated pointer to the head of the list
LinkedListNodeDef* AddToLinkedList(LinkedListNodeDef* ptrHead, char* NameData, int DataIndex) {

	// If data index between 0 or 1 make it top Node.
	if (DataIndex == 0 || DataIndex == 1) {

		LinkedListNode* newNode;

		newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));

		newNode->ptrNextNode = ptrHead;

		strncpy_s(newNode->NameData, NameData, 29);

		ptrHead = newNode;

		return ptrHead;
	}

	// If data index is bigger than the size of linkedlist
	// Put new Node end of linkedlist
	else if (DataIndex > globalIndex) {

		LinkedListNode* currentNode = ptrHead;

		while (currentNode != NULL && currentNode->ptrNextNode != NULL) {
			currentNode = currentNode->ptrNextNode;

		}

		LinkedListNode* newNode;

		newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));

		newNode->ptrNextNode = NULL;

		strncpy_s(newNode->NameData, NameData, 29);

		if (currentNode != NULL) {
			currentNode->ptrNextNode = newNode;
		}
		else {
			ptrHead = newNode;
		}
		return ptrHead;
	}

	// If dataIndex smllar than size of linked list 
	// Put new node in the linked list according to the DataIndex value
	else {

		LinkedListNode* currentNode = ptrHead;

		LinkedListNode* newNode;

		newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));

		strncpy_s(newNode->NameData, NameData, 29);


		//Find the position to put the data in
		for (int i = 2; i < DataIndex; i++) {
			if (currentNode->ptrNextNode != NULL) {
				currentNode = currentNode->ptrNextNode;
			}
		}

		newNode->ptrNextNode = currentNode->ptrNextNode;
		currentNode->ptrNextNode = newNode;

		return ptrHead;
	}

}

// FUNCTION      : PrintLinkedList()
// DESCRIPTION   : This function takes an input of the head of the linked list, then loops through
//				   and prints each word in the linked list until the ptrNextNode is NULL.
// PARAMETERS    : LinkedListNodeDef *ptrHead 
// RETURNS       : void
void PrintLinkedList(LinkedListNodeDef* ptrHead) {
	int y = 0;
	LinkedListNode* currentNode = ptrHead;

	while (currentNode != NULL) {
		y = y + 1;
		printf("%d : %s\n", y, currentNode->NameData);
		currentNode = currentNode->ptrNextNode;
	}

}
