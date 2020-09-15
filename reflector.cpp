#include <fstream>
#include <iostream>
#include <cstring>

#include "errors.h"
#include "reflector.h"

using namespace std;

reflector::reflector(char* dfile, int alphabet) {
  datafile = dfile;

  alpha = new int;
  *alpha = alphabet;

  testarr = new int[*alpha];

  mapping = new int*[*alpha];
  for(int i = 0; i < *alpha; i++)
    mapping[i] = new int[2];

  for (int column = 0 ; column < *alpha ; column++) {
    mapping[column][0] = column;
    mapping[column][1] = mapping[column][0];
  }

  for (int element = 0 ; element < *alpha ; element++) {
    testarr[element] = *alpha;
  }
}

void reflector::load() {
  ifstream in_stream;
  int number;

  in_stream.open(datafile);
  err_file = datafile;
  
  if ((test_ERROR_OPENING_CONFIGURATION_FILE(in_stream) != 0) && (err_code == 0)) {
    err_code = 11; 
    return;
  }

  while(!in_stream.eof())
  {

    in_stream >> noskipws;

    if ((test_NON_NUMERIC_CHARACTER(in_stream) != 0) && (err_code == 0)) {
      err_code = 4;
      return;
    }

    in_stream >> ws;
    in_stream >> number;
    if(!in_stream.eof()) {

      if ((test_INVALID_INDEX(number, alpha) != 0) && (err_code == 0)) {
      	err_code = 3;
	return;
      }

      if ((test_INVALID_REFLECTOR_MAPPING(number, testarr, count, alpha) != 0) && (err_code == 0)) {
	err_code = 9;
	return;
      }

      if (count < *alpha)
	testarr[count] = number;
      
      count++;
    }
  }

  in_stream.close();
     
  if ((test_INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS(count, alpha) != 0) && (err_code == 0)) {
    err_code = 10;
    return;
  }
}

void reflector::map() {
  for (int element = 0 ; element < count ; element ++)
    for (int _element = 0 ; _element < *alpha ; _element++) {
      if ((testarr[element] == mapping[_element][0]) && (element % 2 == 0))
        mapping[_element][1] = testarr[element + 1];
      if ((testarr[element] == mapping[_element][0]) && (element % 2 == 1))
        mapping[_element][1] = testarr[element - 1];
    }
}

void reflector::pass(int input, int& output) {
  for (int element = 0 ; element < *alpha ; element++)
    if (mapping[element][0] == input)
      output = mapping[element][1];
}

reflector::~reflector() {
  for (int i = 0; i < *alpha; i++) {
  delete [] mapping[i];
  }
  delete [] mapping;

  delete [] testarr;

  delete alpha;
}
