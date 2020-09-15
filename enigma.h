#ifndef ENIGMA_H
#define ENIGMA_H

#include <fstream>
#include <string>
#include "rotor.h"
#include "plugboard.h"
#include "reflector.h"


using namespace std;

class Enigma 
{
  /* alphabet size */
  int* alpha;

  /* number of rotors */
  int rot_number;
  
  int input, count = 0;
  char* pb_file;
  char* rf_file;
  char** rot_files;
  char* pos_file;

  /* load rotor starting positions */
  void load_position();
  
  plugboard plug;
  reflector reflect;
  rotor** rot;

public:
  Enigma(int alphabet, int rotor_number, char* plugboard_file, char* reflector_file, char** rotor_files, char* position_file);

  ~Enigma();

  /* store any errors encountered */
  int error_code = 0;
  char* error_file;
  string error_comment;

  /* load files */
  void load();

  /* see if any errors found loading files */
  void error_check();

  /* map components */
  void map();

  void rotate_rotors();

  /* pass inputs through components */
  void pass_plugboard(int input, int& output);
  void pass_rotors0(int input, int& output);
  void pass_reflector(int input, int& output);
  void pass_rotors1(int input, int& output);  
};

#endif
