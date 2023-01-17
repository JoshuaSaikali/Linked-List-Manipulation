Purpose :  Managing patients arriving at a hospital emergency department.
Developer Name: Joshua Saikali
Date: November 24th 2022

Files: emergencyRoomMain.c, linked_list_hospital.c, patient.c, linked_list_hospital.h, patient.h
    -emergencyRoomMain.c 
        - This file contains the control for testing the program
    -linked_list_hospital.c
        - This file contains all of the functions to manipulate the linked list
    -patient.c
        - This file contains all of the functions for the PatientInfo struct 

    -All other header files contain the function prototypes for their respective '.c' file.


Compiling Instructions:
- To begin, open a terminal in the same directory as the files
- In the terminal, use the make command to compile all of the files
    Use the following command: 
        > make er.out
- This will compile the files into an executable called 'er'.
- To run the program simply use this command:
    > ./er


Bonus questions:
- I have completed all of the bonus questions.
    functions: releasePatients, reverseList, printListReverse

Limitations/Issues:
- When testing this software, please remeber to free the memory using one of the following methods.
    Method 1 (Recommended): Use 'deleteList(ListNode **head)', this function will free the whole list
    Method 2: Use 'deleteFromList(ListNode **head, PatientInfo *patient)', 
              you will need to use this in a loop until the list is empty.
- If you do not use one of these methods, then there will be a memory leak
- I created a helper function called 'deleteNode', this function delete's how the node will be deleted 
    based on it's position in the list. (No issues. Just for your information)


How-to-use Instructions:
    - To use this program, simply create test cases
    - These test cases should implement the functions that are coded in the 
        linked_list_hospital.c file
