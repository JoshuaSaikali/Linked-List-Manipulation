
/*
File name is linked_list_hospital.c
 Purpose: file contains functions for manipulating singly linked list

 Revisions
 Doron Nussbaum 2022 File created






 Copyright 2022 Doron Nussbaum

 */

/******************************************************************/
// INCLUDE

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "linked_list_hospital.h"
#include "patient.h"

/************************************************************************/
// Define

/************************************************************************/

/*
Purpose: insert a new node into the list as the first element
input
patient - the patient record

input/output
head - head of linked list

return
A pointer to the node that was allocated.

NULL - if the operation was not successful

*/

ListNode *insertToList(ListNode **head, PatientInfo *patient)

{
	ListNode *p = NULL;

	// allocate memory for the node and initialize all pointers to NULL
	p = (ListNode *)malloc(sizeof(ListNode));
	// if an error then return 1
	if (p == NULL)
	{
		return NULL;
	}

	// Step 2 assign the patient
	p->patient = *patient;

	// update the next field of the new node to point to the first node in the list as a next node
	p->next = *head;

	// update the list head to point to the new node.
	*head = p;

	return p;
}

/************************************************************************/
/*
Purpose: insert a new node into the list after the given node

Input
input
patient - the patient record


return
A pointer to the node that was allocated.

NULL - if the operation was not successful

*/

ListNode *insertAfter(ListNode *node, PatientInfo *patient)
{
	// check if previous node is NULL
	if (node == NULL)
	{
		return NULL;
	}
	ListNode *p = NULL;
	// allocate memory for the node and initialize all pointers to NULL
	p = (ListNode *)malloc(sizeof(ListNode));
	if (p == NULL)
	{
		return NULL;
	}
	// assign patient data
	p->patient = *patient;
	// set next pointer of new node to next of prev
	p->next = node->next;
	// update next pointer of prev
	node->next = p;

	return p;
}

/************************************************************************/
/*
Purpose: search for the first patient with the matching priority
Input
head - the head of the list
priority - first priority of the patient

output
patient - the patient record

return
a pointer to the node that was found.
NULL - if no node was found or list empty

*/

ListNode *searchFirstPatientByPriority(ListNode *head, unsigned char priority, PatientInfo *patient)

{
	// check if list is empty
	if (head == NULL)
	{
		return NULL;
	}
	ListNode *temp = NULL;
	temp = head;
	// while list is not empty
	while (temp != NULL)
	{
		// check if priority is matched
		if (temp->patient.priorityLevel == priority)
		{
			// assign patient data and return node
			*patient = temp->patient;
			return temp;
		}
		else
		{
			temp = temp->next;
		}
	}
	temp = NULL;
	// if no node found then return NULL
	return NULL;
}

/************************************************************************/
/*
Purpose: search for the first patient with the matching criteria.  The criteria is determined
by the comparison function
Input
head - the head of the list
findPatient -  a function pointer that returns a 0 if the patient's record matches that criteria

output
patient - the patient record

return
a pointer to the node that was found.
NULL - if no node was found or list empty

*/

ListNode *searchNextPatient(ListNode *head, int (*findPatient)(PatientInfo *), PatientInfo *patient)
{
	// check if list is empty
	if (head == NULL)
	{
		return NULL;
	}
	ListNode *temp = NULL;
	temp = head;
	// while list is not empty
	while (temp != NULL)
	{
		// check if criteria is matched
		if (findPatient(&temp->patient) == 0)
		{
			// assign patient data and return node
			*patient = temp->patient;
			return temp;
		}
		else
		{
			temp = temp->next;
		}
	}
	temp = NULL;
	// if no node found then return NULL
	return NULL;
}

/***************************************************************/

/*
Purpose: delete the first node from the list
Input
head - the head of the list

output
head - the head of the list
patient - the patient record


return

0 if node was deleted
1 if node was not deleted or list is empty

*/

int deleteFromList(ListNode **head, PatientInfo *patient)

{
	ListNode *p = NULL;

	// if list is empty, patient is null and no node is deleted
	if (*head == NULL)
	{
		patient = NULL;
		return 1;
	}
	// if node is only node in list
	else if ((*head)->next == NULL)
	{
		// set patient data
		*patient = (*head)->patient;
		// free head and set null
		free(*head);
		*head = NULL;
	}
	else
	{
		// set p to head
		p = *head;
		// set patient data
		*patient = (*head)->patient;
		// set new head to the next node
		*head = (*head)->next;
		// free old head and set null
		free(p);
		p = NULL;
	}
	return 0;
}

int deleteNode(ListNode **head, ListNode *temp, PatientInfo *patient)
{
	if (temp == *head)
	{
		// if node is first in list
		deleteFromList(head, patient);
		return 0;
	}
	else if (temp->next == NULL)
	{
		// if node is last in list
		ListNode *secondLast = NULL;
		secondLast = *head;
		while (secondLast->next->next != NULL)
		{
			secondLast = secondLast->next;
		}
		// set second last node to point to null
		secondLast->next = NULL;
		// free node and set null
		free(temp);
		temp = NULL;
		return 0;
	}
	else
	{
		// delete node from middle of list
		ListNode *prev = NULL;
		ListNode *current = NULL;
		current = *head;
		// find the prev node
		while (current->next != temp)
		{
			current = current->next;
		}
		prev = current;

		//  set previous node's next to the node's next (bypass)
		prev->next = temp->next;

		//  free node
		free(temp);
		temp = NULL;
		return 0;
	}
}

/***************************************************************/

/*
Purpose: Retrieve the first node that matches the priority.  When found the node is deleted and the patient
information is provided.

Input
head - the head of the list

output
head - the head of the list
patient - the patient record


return

0 if node was deleted
1 if node was not found or list is empty

*/

int retrieveNextPatientByPriority(ListNode **head, unsigned char priority, PatientInfo *patient)

{
	// check if list is empty
	if (*head == NULL)
	{
		patient = NULL;
		return 1;
	}
	ListNode *temp = NULL;
	temp = searchFirstPatientByPriority(*head, priority, patient);
	// if null, then node not found
	if (temp == NULL)
	{
		patient = NULL;
		return 1;
	}
	else
	{
		// set patient data and delete node (this function returns 0)
		*patient = temp->patient;
		return deleteNode(head, temp, patient);
	}
	return 1;
}

/***************************************************************/

/*
Purpose: Retrieve the patient with the highest criteria to be treated.  The maximum criteria is determined by
a comparePatients function.  Once the patient is found it is deleted from the list and its information is
returned.

Input
head - the head of the list
comparePatients - this function takes two paitent records and compares them.
				It returns, -1, 0 or 1 if p1 < p2, p1 == p2, or p1 > p2, respectively.

output
head - the head of the list
patient - the patient record


return
0 if  patient was found and the node was deleted
1 if no paitent was found or the list is empty


Algorithm:
The function first finds the patient with the hights criteria by comparing all the patients records and
finding the first patient with the maximum criteria to be treated.  It then deletes the patient and returns
its information.
*/

int retrieveNextPatientByCriteria(ListNode **head, int (*comparePatients)(PatientInfo *p1, PatientInfo *p2, int currentTime), int currentTime, PatientInfo *patient)

{
	// check if list is empty
	if (*head == NULL)
	{
		patient = NULL;
		return 1;
	}
	else
	{
		ListNode *temp = NULL;
		ListNode *next = NULL;
		temp = *head;
		// find next patient (similar to find a maximum value)
		while (temp != NULL)
		{
			if (temp->next != NULL)
			{
				if (comparePatients(&temp->patient, &temp->next->patient, currentTime) == 1)
				{
					next = temp;
				}
			}
			temp = temp->next;
		}
		// if null, then node not found
		if (next == NULL)
		{
			patient = NULL;
			return 1;
		}
		else
		{
			// set patient data and delete node
			*patient = next->patient;
			return deleteNode(head, next, patient);
		}
	}

	return 1;
}

/************************************************************************/
/*
Purpose: deletes all nodes from the list
input/output
head - the head of the list


*/

void deleteList(ListNode **head)
{
	ListNode *current = NULL;
	ListNode *next = NULL;
	current = *head;

	// while there is a node in the list
	while (current != NULL)
	{
		// get the next node
		next = current->next;
		// free current node
		free(current);
		// set current to the next
		current = next;
	}
	current = NULL;
	*head = NULL;
}

/************************************************************************/
/*
Purpose: prints all the records in the list

input
head - the head of the list
myPrint - a function pointer for print the patient information.
*/

void printList(ListNode *head, void (*myPrint)(PatientInfo *patient))
{
	ListNode *temp = NULL;
	temp = head;
	// while list is not empty print
	while (temp != NULL)
	{
		myPrint(&temp->patient);
		temp = temp->next;
	}
}

/************************************************************************/
/*
Purpose: counts the number of patients that are waiting to be treted
input
head - the head of the list

return
the number of registered patients

*/

int numPatientsInEmergency(ListNode *head)
{
	// if list is empty
	if (head == NULL)
	{
		return 0;
	}
	ListNode *p = NULL;
	p = head;
	int count = 0;
	// while list is not empty add 1 to count
	while (p != NULL)
	{
		count++;
		p = p->next;
	}
	return count;
}

/************************************************************************/
/*
Purpose: counts the number of patients with a matching priority
input
head - the head of the list


return
the number of patients with a matching priority


*/

int countPatients(ListNode *head, unsigned char priority)
{
	// if list is empty
	if (head == NULL)
	{
		return 0;
	}
	ListNode *p = NULL;
	p = head;
	int count = 0;
	// while list is not empty, if patient matches priority add 1 to count
	while (p != NULL)
	{
		if (p->patient.priorityLevel == priority)
		{
			count++;
		}
		p = p->next;
	}
	return count;
}

// BONUS SECTION

/************************************************************************/
/*

Purpose: removes all Patients with priority less than or equal to the given priority
(remove all patients with priorityLevel <= priority).


input
head - the head of the  list

Ouput
head - the head of the list where all patients with priorityLevel < priority are removed

*/

int releasePatients(ListNode **head, unsigned char priority)
{
	// if list is empty
	if (*head == NULL)
	{
		return 0;
	}
	ListNode *temp = NULL;
	temp = *head;
	// if only 1 node in list
	if (temp->next == NULL)
	{
		if (temp->patient.priorityLevel <= priority)
		{
			// if priority matches, then delete
			deleteNode(head, temp, NULL);
		}
	}
	else
	{
		ListNode *prev = NULL;
		prev = temp;
		// while list is not empty
		while (temp != NULL)
		{
			// if criteria matches
			if (temp->patient.priorityLevel <= priority)
			{
				// check if its the first node in list
				if (prev == temp)
				{
					prev = temp->next;
					// Delete node first node in list
					ListNode *p = NULL;
					p = *head;
					*head = (*head)->next;
					free(p);
					p = NULL;
					// replace current node to previous
					temp = prev;
				}
				else
				{
					// if not first node, then delete and go to next node
					deleteNode(head, temp, NULL);
					temp = prev->next;
				}
			}
			else
			{
				// if criteria does not match then go to next node
				prev = temp;
				temp = temp->next;
			}
		}
	}
	return (0);
}

/************************************************************************/
/*
Purpose: prints all the patients' records in the list in reverse order using recursion

input
head - the head of the list
*/

void printListReverse(ListNode *head, void (*myPrint)(PatientInfo *patient))
{
	// if list is empty
	if (head == NULL)
	{
		return;
	}
	// recursive call to print list in reverse
	printListReverse(head->next, myPrint);
	// function pointer that prints patient
	myPrint(&head->patient);
}

/*****************************************************************************/

/************************************************************************/
/*
Purpose: Reverse the list such that the last node in the list becomes the first node and the first node in the list becomes the last node.

Restrictions:
1.	This operation must be achieved using recursive calls
2.	No memory is to be allocated or released at any time during the execution of the function



input
head - the head of the list


Returns:
the head of the new list
*/

ListNode *reverse(ListNode *head)

{
	// if list is empty
	if (head == NULL)
	{
		return head;
	}
	// if node is last node in list, return the head
	else if (head->next == NULL)
	{
		return head;
	}
	else
	{
		// sets newHead to the return value of the recursive call
		ListNode *newHead = NULL;
		newHead = reverse(head->next);
		head->next->next = head;
		head->next = NULL;
		return newHead;
	}
}
