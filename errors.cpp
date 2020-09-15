#include <fstream>
#include <iostream>

#include "errors.h"

int test_INSUFFICIENT_NUMBER_OF_PARAMETERS(int number) {
  if (number < 3) {
    return 1;
  }
  return 0;
}

int test_INVALID_INPUT_CHARACTER(char letter) {
  if (((letter < 'A') || (letter > 'Z')) && (!isspace(letter))) {
      return 2;
    }
  return 0;
}

int test_INVALID_INDEX(int number, int* alpha) {

  if ((number < 0) || (number > *alpha - 1)) {
    return 3;
  }
  return 0;
}

int test_NON_NUMERIC_CHARACTER(ifstream& in) {
  char character;
  int count_get = 0;

  in >> character;
  //  cerr << character << " " << int(character) << "." << endl;
  count_get++;

  while ((isspace(character)) && (!in.eof())) {
    in >> character;
    //    cerr << character << " " <<  int(character) << "/" << endl;
    count_get++;
  }
    
  while (!isspace(character) && (!in.eof())) {
    if ((character < '0') || (character > '9'))
      return 4;
    in >> character;
    //    cerr << character << " " << int(character) << "!" << endl;
    count_get++;
  }

  for (int i = 0 ; i < count_get ; i++)
    in.unget();
					     
  return 0;
}

int test_IMPOSSIBLE_PLUGBOARD_CONFIGURATION(int number, int* test, int count, int* alpha) {
  if (count < *alpha)
    for (int element = 0 ; element <= count ; element++) {
      if (test[element] == number) {
	return 5;
      }
    }
  return 0;
}

int test_INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS(int count, int* alpha) {
  if ((count % 2 == 1) || (count > *alpha)) {
    return 6;
  }
  return 0;
}

int test_INVALID_ROTOR_MAPPING0(int number, int* test, int count, int* alpha) {
  if ((count > 0) && (count < *alpha))
    for (int element = 0 ; element <= count - 1 ; element++) 
	if (test[element] == number) {
	  return 7;
	}
  return 0;
}

int test_INVALID_ROTOR_MAPPING1(int count, int* alpha) {
  if (count < *alpha) {
    return 7;
  }
  return 0;
}

int test_NO_ROTOR_STARTING_POSITION(int count, int rot_number) {
  if (count < rot_number) {
    return 8;
  }
  return 0;
}

int test_INVALID_REFLECTOR_MAPPING(int number, int* test, int count, int* alpha) {
  if (count < *alpha)
    for (int element = 0 ; element <= count ; element++) {
      if (test[element] == number) {
	return 9;
      }
    }
  return 0;
}

int test_INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS(int count, int* alpha) {
  if (count != *alpha) {
    return 10;
  }
  return 0;
}

int test_ERROR_OPENING_CONFIGURATION_FILE(ifstream& in) {
  if (in.fail()) {
    return 11;
  }
  return 0;
}
    
