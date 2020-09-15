#include <fstream>
#include <iostream>
#include <cstring>

#include "errors.h"
#include "rotor.h"

using namespace std;

rotor::rotor(char* dfile, int alphabet) {
  datafile = dfile;

  alpha = new int;
  *alpha = alphabet;

  testarr = new int[*alpha * 2];

  mapping = new int*[*alpha];
  for (int i = 0 ; i < *alpha ; i++)
    mapping[i] = new int[3];

  for (int row = 0 ; row < *alpha ; row++) {
    mapping[row][0] = row;
    mapping[row][1] = mapping[row][0];
    mapping[row][2] = 0;
  }

  for (int element = 0 ; element < *alpha * 2; element++) {
    testarr[element] = *alpha;
  }
}

void rotor::load() {
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

      if ((test_INVALID_ROTOR_MAPPING0(number, testarr, count, alpha) != 0) && (err_code == 0)) {
	err_code = 7;
	return;
      }

      testarr[count] = number;
      count++;
    }
  }

  in_stream.close();

  if ((test_INVALID_ROTOR_MAPPING1(count, alpha) != 0) && (err_code == 0)) {
    err_code = 7;
    return;
  }
}

void rotor::rotormap() {
  for (int element = 0 ; element < *alpha ; element++)
    mapping[element][1] = testarr[element];

  for (int element = *alpha ; element < *alpha * 2 ; element++)
    if (testarr[element] < *alpha)
      mapping[testarr[element]][2] = 1;
}

void rotor::rotate() {
  int temp_mapping[*alpha];

  for (int row = 0 ; row < *alpha ; row++)
    temp_mapping[row] = *alpha;
  
  for (int element = 0 ; element < *alpha ; element++) {
    if (element == *alpha - 1) {
      temp_mapping[element] = mapping[element - (*alpha - 1)][1] - 1;
    }
    else {
      temp_mapping[element] = mapping[element + 1][1] - 1;
    }
    
    if (temp_mapping[element] < 0)
      temp_mapping[element] += *alpha;
  }
  for (int _row = 0 ; _row < *alpha ; _row++) {
    mapping[_row][1] = temp_mapping[_row];
  }

  rotate_count++;
}

void rotor::initial_position(int initial_position) {
  if (initial_position > 0)
    for (int i = 1 ; i <= initial_position ; i++)
      rotate();
}

bool rotor::notch() {
  if (mapping[rotate_count % *alpha][2] == 1) {
    return true;
  }
  return false;
}

void rotor::pass(int input, int& output) {
  for (int element = 0 ; element < *alpha ; element++)
    if (mapping[element][0] == input)
      output = mapping[element][1];
}

void rotor::passback(int input, int& output) {
  for (int element = 0 ; element < *alpha ; element++)
    if(mapping[element][1] == input)
      output = mapping[element][0];
}

rotor::~rotor() {

  for (int i = 0; i < *alpha; i++) {
  delete [] mapping[i];
  }
  delete [] mapping;

  delete [] testarr;

  delete alpha;
}

