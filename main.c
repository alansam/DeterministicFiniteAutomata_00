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
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>

#define ARRAYSIZE(a)	(sizeof(a) / sizeof(a[0]))

enum states { EVEN, ODD, };

int delta(int state, int ch);
ssize_t set_search(int *set, size_t size, int vh);

/*
 *  MARK: main()
 */
int main(int argc, char const * argv[]) {
	int ch, state;
  int RC = EXIT_SUCCESS;

  [[maybe_unused]]
	int QS[] = { EVEN, ODD, };	/* set of states */
	int FS[] = { ODD, };	/* set of accept states */
	int sigma[] = { '0', '1', };	/* alphabet */

  state = EVEN;
	while ((ch = getchar()) != EOF) {
    if (isspace(ch)) {
      printf("%12s: isspace(%#04x) ...\n",
             __func__, ch);
      break;
    }

    printf("%12s: isdigit(%#04x): %-5s\n",
           __func__, ch, (isdigit(ch) ? "true" : "false"));

    if (!isdigit(ch)
    ||  set_search(sigma, ARRAYSIZE(sigma), ch) == -1) {
      printf("%12s: GRONK!\n", __func__);
			state = EVEN;
			break;
		}

    state = delta(state, ch);
    putchar('\n');
	}

  putchar('\n');

  if (set_search(FS, ARRAYSIZE(FS), state) == -1) {
		fprintf(stderr, "%12s: Invalid string\n", __func__);
		RC = EXIT_FAILURE;
	}

  printf("%12s: state[f] = %4s, RC = %d\n",
         __func__, (state == ODD ? "odd" : "even"), RC);

  return RC;
}

/*
 *  MARK: delta()
 */
int delta(int state, int ch) {
  printf("%12s: state[i] = %4s, c = %#04x\n",
         __func__, (state == ODD ? "odd" : "even"), ch);

	switch (state) {
	case EVEN:
		if (ch == '0')      { state = EVEN; }
		else if (ch == '1') { state = ODD; }
		break;

  case ODD:
		if (ch == '0')      { state = ODD; }
		else if (ch == '1') { state = EVEN; }
		break;

	default:
		break;
	}

  printf("%12s: state[o] = %4s\n",
         __func__, (state == ODD ? "odd" : "even"));

  return state;
}

/*
 *  MARK: set_search()
 */
ssize_t set_search(int *set, size_t size, int vh) {
	int *ps;
  ssize_t rv = -1;

  printf("%12s: %p, %zu, %#04x\n",
         __func__, set, size, vh);

	for (ps = set; ps != set + size; ps++) {
    printf("%12s: %#04x == %#04x : %-5s\n",
           __func__, *ps, vh,
           (*ps == vh) ? "true" : "false");
		if (*ps == vh) {
			rv = ps - set;
    }
  }
	// rv = -1;
  printf("%12s: ret = %ld\n",
         __func__, rv);

  return rv;
}
