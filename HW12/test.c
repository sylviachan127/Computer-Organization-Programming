#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Here we are going to write some functions to support a linked list that stores
 * Person data (name, age)
 * Student Name: Yuen Han Chan
 */
typedef struct person_t
{
    char* name;
    int age;
} Person;

/* Example functions given to you. If you want to truly grasp these concepts, try
 * writing your own structs and functions as well!
 */

// Create a new Person
Person* create_person(const char* name, int age)
{
    Person* p = (Person*) malloc(sizeof(Person));
    p->name = strdup(name);
    p->age = age;
    return p;
}

// Make a deep copy of a Person
void* copy_person(const void* data)
{
    Person *p = (Person*) data;
    return create_person(p->name, p->age);
}

// Print a Person
void print_person(void* data)
{
    Person *p = (Person*) data;
    printf("%s, %d\n", p->name, p->age);
}

// Free a Person
void free_person(void* data)
{
    Person *p = (Person*) data;
    // free any malloc'd pointers contained in the Person struct
    free(p->name);
    free(p);
}

// Return 1 if the person's name is 8+ characters long
int long_name(const void *data)
{
	Person *p = (Person*) data;
	return strlen(p->name) > 7;
}

/* This main function does a little testing
   Like all good CS Majors you should test
   your code here. There is no substitute for testing
   and you should be sure to test for all edge cases
   e.g., calling remove_front on an empty list.
*/
int main(void)
{
	/* Now to make use of all of this stuff */
	list* llist = create_list();

  	/* What does an empty list contain?  Lets use our handy traversal function */
  	printf("TEST CASE 1\nAn Empty list should print nothing here:\n");
  	traverse(llist, print_person);
	printf("\n");

 	/* Lets add a person and then print */
 	push_front(llist, create_person("Andrew", 24));
 	printf("TEST CASE 2\nA List with one person should print that person:\n");
 	traverse(llist, print_person);
 	printf("\n");

 	/* Lets remove that person and then print */
 	remove_front(llist, free_person);
 	printf("TEST CASE 3\nAnother Empty list should print nothing here:\n");
 	traverse(llist, print_person);
 	printf("\n");

 	/* Lets add two people and then print */
 	push_front(llist, create_person("Nick", 22));
 	push_front(llist, create_person("Randal", 21));
 	printf("TEST CASE 4\nA List with two people should print those two people:\n");
 	traverse(llist, print_person);
 	printf("\n");

	/* Lets copy this list */
	list* llist2 = copy_list(llist, copy_person);
	printf("TEST CASE 5\nA copied list should print out the same two people:\n");
 	traverse(llist2, print_person);
 	printf("\n");

  	/* Lets kill the list */
  	empty_list(llist, free_person);
 	printf("TEST CASE 6\nAfter freeing all nodes the list should be empty:\n");
 	traverse(llist, print_person);
	printf("\n");

	/* Let's make a list of people, and remove certain ones! */
	/* Should remove anyone whose name is 8+ characters long */
	push_front(llist, create_person("Josephine", 27));
	push_front(llist, create_person("Dave", 34));
	push_front(llist, create_person("Benjamin", 23));
	push_front(llist, create_person("Lisa", 41));
	push_front(llist, create_person("Maximilian", 24));
	remove_if(llist, long_name, free_person);
	printf("TEST CASE 7\nShould only print 2 people with short names:\n");
	traverse(llist, print_person);

 	/* YOU ARE REQUIRED TO MAKE MORE TEST CASES THAN THE ONES PROVIDED HERE */
 	/* You will get points off if you do not you should at least test each function here */

	/* MY OWN TEST STARTS HERE!!!!! */
	empty_list(llist, free_person);

	/* Test push_front and push_back */
	printf("\nOWN TEST CASE 1\nAdd Only 1 node using push front and then print\n");
	printf("\nShould return Sylvia, 19\n");
	push_front(llist, create_person("Sylvia", 19));
	traverse(llist, print_person);
	printf("\nanother Push front, Should return Cheng Han, 24, Sylvia, 19\n");
	push_front(llist, create_person("Cheng Han", 24));
	traverse(llist, print_person);
	printf("\nanother push front, Should rturn additional Sally Handson, 23\n");
	push_front(llist, create_person("Sally Handson", 23));
	traverse(llist, print_person);
	printf("\nPush to back, Dog, 1 should be the new Tail\n");
	push_back(llist, create_person("Dog", 1));
	traverse(llist, print_person);
	printf("\nanother push_back, Dog2, 2 should be the new Tail\n");
	push_back(llist, create_person("Dog2", 2));
	traverse(llist, print_person);
	printf("\nSize should be 5");
	printf("\nList Size: %d\n", size(llist));

	/* Test front and back, remove_front, remove_back*/
	printf("\nOWN TEST CASE 2");
	printf("\nThe head should be Sally Handson, 23");
	printf("\nHead is: ");
	print_person(front(llist));
	printf("\nThe tail should be Dog2, 2");
	printf("\nTail is: ");
	print_person(back(llist));
	remove_front(llist, free_person);
	printf("\nThe head should now be Cheng Han, 24");
	printf("\nHead is: \n");
	print_person(front(llist));
	remove_back(llist, free_person);
	printf("\nThe tail should now be Dog, 1");
	printf("\nTail is: \n");
	print_person(back(llist));
	printf("\nThe size should be 3");
	printf("\nList Size: %d\n", size(llist));

	/* Test more remove_front, remove_back*/
	printf("\nOWN TEST CASE 3");
	empty_list(llist, free_person);
	push_front(llist, create_person("Sylvia", 19));
	printf("\nHead and Tail should be the same");
	printf("\nHead is: ");
	print_person(front(llist));
	printf("\nTail is: ");
	print_person(back(llist));

	remove_front(llist, free_person);
	printf("\nThe head should now be NULL");
	printf("\nHead is: ");
	if(front(llist)==NULL){
		printf("NULL\n");
	}
	else{
		printf("NOT NULL\n");
	}
	printf("\nThe tail should now be NULL as well");
	printf("\nTail is: ");
	if(back(llist)==NULL){
		printf("NULL\n");
	}
	else{
		printf("NOT NULL\n");
	}
	printf("\nList is now empty");
	printf("\nList: ");
	traverse(llist, print_person);
	printf("\nThe size should be 0");
	printf("\nList Size: %d\n", size(llist));

	/* Test is_empty*/
	printf("\nOWN TEST CASE 4");
	printf("\nShould be 1");
	printf("\nResult: %d\n",is_empty(llist));

 	/* Testing over clean up*/
	empty_list(llist, free_person);
 	free(llist);
	empty_list(llist2, free_person);
	free(llist2);

  	return 0;
}

