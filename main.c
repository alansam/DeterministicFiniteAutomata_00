//  @author: Thong Nguyen - FaceBook group: C Programming
/*
 *  (Resolved) Hello, I wrote a program that recognizes the language:
 *  L(DFA M) = { w | w contains odd number of 1s }
 *  The DFA M is defined as:
 *  M = ({q_even, q_odd}, {0, 1}, delta, q_even, {q_odd})
 *  The transition function delta:
 *  delta(q_even, 0) = q_even;
 *  delta(q_even, 1) = q_odd;
 *  delta(q_odd, 0) = q_odd;
 *  delta(q_odd, 1) = q_even;
 *
 *  Here, the source
 *    @see: http://codepad.org/n3PXds8x
 *  The program gets an input string, and gives no outputs if the
 *  program recognizes the string, otherwise, rejects the input and
 *  report error.
 *. After the input string 0111 is given, the program prints the error
 *  "Invalid string" even though the string is in the language. Why?
 */

#include <stdio.h>
#include <sys/types.h>
#include <ctype.h>

#define ARRAYSIZE(a)	(sizeof(a) / sizeof(a[0]))

enum states { EVEN, ODD };

int delta(int state, int c);
ssize_t set_search(int *set, size_t size, int v);

int main(void)
{
	int c, state;
  [[maybe_unused]]
	int Q[] = { EVEN, ODD };	/* set of states */
	int F[] = { ODD };	/* set of accept states */
	int sigma[] = { '0', '1' };	/* alphabet */

	state = EVEN;
	while ((c = getchar()) != EOF) {
		if (!isdigit(c) || set_search(sigma, ARRAYSIZE(sigma), c) == -1) {
			state = EVEN;
			break;
		}
		state = delta(state, c);
	}

	if (set_search(F, ARRAYSIZE(F), state) == -1) {
		fprintf(stderr, "Invalid string\n");
		return 1;
	}
	return 0;
}

int delta(int state, int c)
{
	switch (state) {
	case EVEN:
		if (c == '0')
			state = EVEN;
		else if (c == '1')
			state = ODD;
		break;
	case ODD:
		if (c == '0')
			state = ODD;
		else if (c == '1')
			state = EVEN;
		break;
	default:
		break;
	}
	return state;
}

ssize_t set_search(int *set, size_t size, int v)
{
	int *ps;

	for (ps = set; ps != set+size-1; ps++)
		if (*ps == v)
			return ps - set;
	return -1;
}
