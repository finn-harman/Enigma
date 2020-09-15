#include <fstream>
#include <iostream>
#include <cstring>

#include "errors.h"
#include "enigma.h"
#include "plugboard.h"
#include "reflector.h"
#include "rotor.h"

using namespace std;

Enigma::Enigma(int alphabet, int rotor_number, char* plugboard_file, char* reflector_file, char** rotor_files, char* position_file) :
  plug(plugboard_file, alphabet),
  reflect(reflector_file, alphabet)
  
{
  alpha = new int;
  *alpha = alphabet;

  rot_files = rotor_files;
  pos_file = position_file;

  rot_number = rotor_number;

  rot = new rotor*[rot_number];
  for (int i = 0 ; i < rot_number ; i++)
    rot[i] = new rotor(rot_files[i], *alpha);  
}

void Enigma::load() {

  plug.load();
  
  reflect.load();

  if (rot_number > 0)
    for (int i = 0 ; i < rot_number ; i++)
      rot[i]->load();
}

void Enigma::error_check() {
  if (plug.err_code != 0) {
    error_code = plug.err_code;
    error_file = plug.err_file;
  }
  
  if ((reflect.err_code != 0) && (error_code == 0)) {
    error_code = reflect.err_code;
    error_file = reflect.err_file;
  }
  
  
  for (int i = 0 ; i < rot_number ; i++) {
    if ((rot[i]->err_code != 0) && (error_code == 0)) {
      error_code = rot[i]->err_code;
      error_file = rot[i]->err_file;
    }
  }

  load_position();

  if (error_code == 3) {
    error_comment = "Invalid index (must be between 0 and 25) in file: ";
    error_comment += error_file;
    return;
  }
  
  if (error_code == 4) {
    error_comment = "Non-numeric character in file: ";
    error_comment += error_file;
    return;
  }

  if  (error_code ==5) {
    error_comment =  "Impossible plugboard configuration in file: ";
    error_comment += error_file;
    return;
  }
  
  if (error_code == 6) {
    error_comment = "Incorrect number of parameters in file: ";
    error_comment += error_file;
    return;
  }

  if (error_code == 7) {
    error_comment = "Invalid rotor mapping in file: ";
    error_comment += error_file;
    return;
  }

  if (error_code == 8) {
    error_comment = "Insufficient number of rotor starting positions in file: ";
    error_comment += error_file;
    return;
  }

  if (error_code == 9) {
    error_comment = "Invalid reflector mapping in file: ";
    error_comment += error_file;
    return;
  }

  if (error_code == 10) {
    error_comment = "Incorrect number of reflector parameters in file: ";
    error_comment += error_file;
    return;
    }

  if (error_code == 11) {
    error_comment = "Error opening configuration file: ";
    error_comment += error_file;
    return;
  }
}

void Enigma::map() {
  plug.map();
  reflect.map();
  
  if (rot_number > 0) {
    ifstream in_stream;
    int number;
    
    in_stream.open(pos_file);
    
    for (int i = 0 ; i < rot_number ; i++) {
      rot[i]->rotormap();

      in_stream >> number;
      rot[i]->initial_position(number);
    }
  }
}

void Enigma::load_position() {
  ifstream in_stream;
  int number, count = 0;

  if (error_code == 0) {
    error_file = pos_file;
  }
  
  in_stream.open(pos_file);

  if ((test_ERROR_OPENING_CONFIGURATION_FILE(in_stream) != 0) && (error_code == 0)) {
     error_code = 11;
     return;
  }

  while(!in_stream.eof())
  {
    in_stream >> noskipws;
    
    if ((test_NON_NUMERIC_CHARACTER(in_stream) != 0) && (error_code == 0)) {
      error_code = 4;
      return;
    }

    in_stream >> ws;
    in_stream >> number;

    if(!in_stream.eof()) {;

      if ((test_INVALID_INDEX(number, alpha) != 0) && (error_code == 0)) {
	error_code = 3;
	return;
      }
      count++;
    }
  }

  in_stream.close();

if ((test_NO_ROTOR_STARTING_POSITION(count, rot_number) != 0) && (error_code == 0)) {
    error_code = 8;
    return;
 }
}

void Enigma::rotate_rotors() {
  rot[rot_number - 1]->rotate();

  if (rot_number > 1) 
    for (int i = rot_number - 2 ; i>=0 ; i--) 
      if (rot[i+1]->notch())
	rot[i]->rotate();
}

void Enigma::pass_plugboard(int input, int& output) {

  plug.pass(input, output);
}

void Enigma::pass_rotors0(int input, int& output) {
  int inputarr[rot_number], outputarr[rot_number];
  inputarr[rot_number - 1] = input;

  rot[rot_number - 1]->pass(inputarr[rot_number - 1], outputarr[rot_number - 1]);
  if (rot_number > 1)
    for (int i = rot_number - 2 ; i >= 0 ; i--) {
      rot[i]->pass(outputarr[i+1], outputarr[i]);
    }

  output = outputarr[0];
}

void Enigma::pass_reflector(int input, int& output) {

  reflect.pass(input, output);
}

void Enigma::pass_rotors1(int input, int& output) {
  int inputarr[rot_number], outputarr[rot_number];
  inputarr[0] = input;

  rot[0]->passback(inputarr[0], outputarr[0]);

  if (rot_number > 1)
    for (int i = 1 ; i < rot_number ; i++) {
      rot[i]->passback(outputarr[i-1], outputarr[i]);
    }

  output = outputarr[rot_number - 1];
}

Enigma::~Enigma() {
  
  for (int i = 0 ; i < rot_number; i++) {
    delete rot[i]; 
  }
  delete [] rot;
  
  delete alpha;
  
}
