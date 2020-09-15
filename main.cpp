#include <iostream>
#include <fstream>

#include "errors.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
#include "enigma.h"

using namespace std;

int const alphabet_size = 26;

void organise_inputs(int argc, char** argv);

int main(int argc, char** argv)
{
  int input, pb_output0, rf_output, rot_output0 = 0, rot_output1 = 0, pb_output1;
  
  int input_number = argc;
  int file_number = input_number - 1;
  int rotor_number = file_number - 3;

  if (test_INSUFFICIENT_NUMBER_OF_PARAMETERS(file_number) != 0) {
    cerr << "Insufficient number of parameters. Usage: enigma plugboard-file reflector-file (<rotor_file>)* rotor_positions";
    return 1;
  }
 
  char* plugboard_file = argv[1];
  char* reflector_file = argv[2];
  char* position_file = argv[input_number - 1];
  char** rotor_files;

  rotor_files = new char*[rotor_number];
  for (int i = 0 ; i < rotor_number ; i++)
    rotor_files[i] = argv[i+3];
  
  Enigma enig(alphabet_size, rotor_number, plugboard_file, reflector_file, rotor_files, position_file);
  
  enig.load();

  enig.error_check();
  
  if (enig.error_code != 0) {
    cerr << enig.error_comment;
    delete [] rotor_files;
    return enig.error_code;
  }

  enig.map();
  
  int MAX_LENGTH = 100;
  char phrase[MAX_LENGTH];
  char output[MAX_LENGTH];
  cin.getline(phrase, MAX_LENGTH);

  int array_length = 0;
  int i = 0;
  while(phrase[i] != '\0') {
    array_length++;
    i++;
  }

  int output_length = 0;
  for (int i = 0 ; i < array_length ; i++) {
    if (test_INVALID_INPUT_CHARACTER(phrase[i]) != 0) {
	for (int j = 0 ; j < output_length ; j++)
	  if (output[j] != ' ')
	    cerr << output[j];
	cerr << endl;
	cerr << "Invalid input character. Input must be capital letter or white space";
	return 2;
      }
    
    if ((phrase[i] == ' ') || (phrase[i] == '\n') || (phrase[i] == 9) || (phrase[i] == 13)) {
      output[i] = ' ';
      output_length++;
    }
    else {
      input = phrase[i] - 'A';
      int pb_input0 = input;

      if (rotor_number > 0) {
	enig.rotate_rotors();
      
	enig.pass_plugboard(pb_input0, pb_output0);

	enig.pass_rotors0(pb_output0, rot_output0);
      
	enig.pass_reflector(rot_output0, rf_output);
      
	enig.pass_rotors1(rf_output, rot_output1);

	enig.pass_plugboard(rot_output1, pb_output1);
      }

      else {
	enig.pass_plugboard(pb_input0, pb_output0);

	enig.pass_reflector(pb_output0, rf_output);

	enig.pass_plugboard(rf_output, pb_output1);
      }
      output[i] = pb_output1 + 'A';
      output_length++;
    }
  }
  
  for (int i = 0 ; i < output_length ; i++)
    if (output[i] != ' ')
      cout << output[i];
  
  delete [] rotor_files;

  return 0;
}

