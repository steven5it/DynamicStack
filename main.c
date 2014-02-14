/* Dynamically Allocated Stack - implementation of push, pop, empty functions for a stack */
/* reads in commands from a file and outputs final stack of stack to another file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 64

void push(char c);  /* push c onto the top of the stack */
char pop();  /* pop the value off the top of the stack and return it */
int empty();  /* return nonzero if the stack is empty, zero, otherwise */

#define DEBUG 0

struct node 
{
	char data;
	struct node *next;
};

struct node *head = NULL;		// global pointer to top of stack

/* read in input and perform stack commands */
int main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: program input_file output_file\n");
		exit(-1);
	}

	// perform input and output operations
	char command[MAX_LINE];
	char value;
	FILE *infile, *outfile;
	infile = fopen(argv[1], "r");
	if (infile == NULL)
	{
		fprintf(stderr, "Invalid input file.\n");
		exit(-1);
	}

	fflush(stdin);
	while (fscanf(infile, "%63s", command) == 1 )
	{
		#if DEBUG
		printf("command is: %s, strlen is: %d.\n", command, (int)strlen(command));
		#endif
		// if pop
		if (strcmp(command, "pop") == 0)
		{
			#if DEBUG 
			printf("%s\n", command);
			#endif
			pop();
		}

		// if push, check next char
		else if (strcmp(command, "push") == 0)
		{
			if (fscanf(infile, " %c", &value) != 1)
				fprintf(stderr, "Invalid character to push.\n");
			#if DEBUG
			printf("%s, %c\n", command, value);
			#endif
			push(value);
		}

		else
		{
			fprintf(stderr, "Command %s not found.\n", command);
		}
	}

	fclose(infile);

	// output state of stack to file
	outfile = fopen(argv[2], "w");
	if (outfile == NULL)
	{
		fprintf(stderr, "Invalid output file.\n");
		exit(-1);
	}

	// clear rest of stack, writing stack to file
	char top;
	while (!empty())
	{
		top = pop();
		fprintf(outfile, "%c", top);
	}


	fclose(outfile);

	// pop remaining stack items

}


/*  push to stack: create new node with data, point it to top of stack, reassign top of stack to new node */
void push(char c)
{
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	if (temp == NULL)		// memory allocation error
	{
		exit(-1);
	}
	temp->data = c;
	temp->next = head;
	head = temp;

	// different stack implementaiton
	// // if stack is empty
	// if (empty())
	// {
	// 	struct node *temp = (struct node*)malloc(sizeof(struct node));
	// 	if (temp == NULL)		// memory allocation error
	// 	{
	// 		exit(-1);
	// 	}
	// 	temp->data = c;
	// 	temp->next = NULL;
	// 	head = temp;
	// }
}

/* pop stack and return value: create temp pointer to top, reset top to next node, free previous top */
char pop()
{

	// if stack is empty, output error message
	if (empty())
	{
		fprintf(stderr, "Error: can't pop from empty stack.");
		exit(-1);
	}

	char value = head->data;		// store popped value to return
	struct node *temp = head;		// create temporary pointer to head
	// if item is last being popped, point head to null
	if (head->next == NULL)
	{
		head = NULL;
		free(temp);
	}

	// otherwise, move pointer down and free memory
	else
	{
		head = head->next;
		free(temp);
	}

	return value;
}

/* if stack is empty, return 1, else return 0 */
int empty()
{
	if (head == NULL)
		return 1;
	else	//stack has items
		return 0;

}