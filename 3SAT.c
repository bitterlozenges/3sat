#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#define N 1000

// represents a literal in a 3-CNF clause, including negation
typedef struct{
	bool neg;
	int index;
} literal;

// represents a clause in 3-CNF formula
typedef struct{
	literal a;
	literal b;
	literal c;
} clause;

// function prototypes
bool evaluate(clause cl, bool vars[]);
int evaluate_eq(clause equation[], int length, bool vars[]);
void print_literal(literal l);
void print_clause(clause cl);
void print_eq(clause equation[], int length);

int main(void)
{
	// seed the random number generator
	srand(time(NULL));

	// array to contain randomly generated clauses
	clause equation[3*N];

	// array to keep variables x_0... x_{N-1}
	bool vars[N]; 

	// generate N clauses
	for (int i = 0; i < 3*N; i++)
	{
		// declare the 3 literals in the clause 
		literal a, b, c;

		// generate whether each literal will be +/- 
		a.neg = rand() % 2;
		b.neg = rand() % 2;
		c.neg = rand() % 2;

		// generate the index for each literal
		// TODO MAKE DISTINCT GAHHHHHHHHHHHH
		a.index = rand() % N;
		b.index = rand() % N;
		c.index = rand() % N;

		// shove our clause into the equation
		equation[i].a = a;
		equation[i].b = b;
		equation[i].c = c;
	}

	int limit = 1000;

	// perform this entire thing for LIMIT times
	for (int i = 0; i < limit; i++)
	{
		// randomly generate an assignment for vars
		for (int j = 0; j < N; j++)
		{
			vars[j] = rand() % 2;
		}

		// counter to see how many times we run the thing
		int count = 0;

		// index of the first unsatisfied clause, or -1 if all sat
		int first_unsat = (evaluate_eq(equation, 9 * N, vars));

		// actual algorithm YAY
		while((first_unsat != -1) && (count < 3 * N))
		{
			// choose which literal to toggle
			int a_or_b_or_c = rand() % 3;
			switch (a_or_b_or_c)
			{
				case 0:
					vars[equation[first_unsat].a.index] = !vars[equation[first_unsat].a.index]; 
					break;
				case 1:
					vars[equation[first_unsat].b.index] = !vars[equation[first_unsat].b.index]; 
					break;
				default:
					vars[equation[first_unsat].c.index] = !vars[equation[first_unsat].c.index]; 
			}
			first_unsat = evaluate_eq(equation, 3 * N, vars);
			count++;
		}

		if (first_unsat == -1)
		{
			printf("Satisfied!");
			return 0;
		}

	}

	printf("Unsatisfied!");
	
}




// evaluate the clause
bool evaluate(clause cl, bool vars[])
{
	return ((((cl.a).neg) ^ (vars[(cl.a).index])) || (((cl.b).neg) ^ (vars[(cl.b).index])) || (((cl.c).neg) ^ (vars[(cl.c).index])));
}

// return the index of the first unsatisfied clause if it exists, -1 if satisfied
int evaluate_eq(clause equation[], int length, bool vars[])
{
	for(int i = 0; i < length; i++)
	{
		if (!evaluate(equation[i], vars))
		{
			return i;
		}
	}

	return -1;
}

// pretty-print a literal
void print_literal(literal l)
{
	if (l.neg)
	{
		printf("!x_%i", l.index);
	}
	else
	{
		printf("x_%i", l.index);
	}
}

// pretty-print a clause
void print_clause(clause cl)
{
	printf("(");
	print_literal(cl.a);
	printf(" || ");
	print_literal(cl.b);
	printf(" || ");
	print_literal(cl.c);
	printf(")");
}

// helpful function to print out an equation in readable form
void print_eq(clause equation[], int length)
{
	for (int i = 0; i < length; i++)
	{
		print_clause(equation[i]);
		printf(" & ");
	}
}



