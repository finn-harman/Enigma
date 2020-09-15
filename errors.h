#include <fstream>
using namespace std;

/* error codes  */
#define INSUFFICIENT_NUMBER_OF_PARAMETERS         1
#define INVALID_INPUT_CHARACTER                   2
#define INVALID_INDEX                             3
#define NON_NUMERIC_CHARACTER                     4
#define IMPOSSIBLE_PLUGBOARD_CONFIGURATION        5
#define INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS  6
#define INVALID_ROTOR_MAPPING                     7
#define NO_ROTOR_STARTING_POSITION                8
#define INVALID_REFLECTOR_MAPPING                 9
#define INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS  10
#define ERROR_OPENING_CONFIGURATION_FILE          11
#define NO_ERROR                                  0

/* if insufficient number of command line */
int test_INSUFFICIENT_NUMBER_OF_PARAMETERS(int number);

/* if input character not upper case (A-Z) */
int test_INVALID_INPUT_CHARACTER(char letter);

/* if file contains number not between 0 and 25 */
int test_INVALID_INDEX(int number, int* alpha);

/* if file contains characters other than numeric characters */
int test_NON_NUMERIC_CHARACTER(ifstream& in);

/* if file attempts to connect a contact with itself, or with more than one other contact */
int test_IMPOSSIBLE_PLUGBOARD_CONFIGURATION(int number, int* test, int count, int* alpha);

/* if file containts odd number of parameters */
int test_INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS(int count, int* alpha);

/* if file attempts to map more than one input to the same output */
int test_INVALID_ROTOR_MAPPING0(int number, int* test, int count, int* alpha);

/* if file does not provide a mapping for some input */
int test_INVALID_ROTOR_MAPPING1(int count, int* alpha);

/* if file file does not provide enough starting positions for number of rotors specified */
int test_NO_ROTOR_STARTING_POSITION(int count, int rot_number);

/* if file attempts to map an input to itself or pair each index with more than one other */
int test_INVALID_REFLECTOR_MAPPING(int number, int* test, int count, int* alpha);

/* if file does not contain exactly 13 pairs of numbers */
int test_INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS(int count, int* alpha);

/* if program encounters any errors opening or reading file */
int test_ERROR_OPENING_CONFIGURATION_FILE(ifstream& in);
