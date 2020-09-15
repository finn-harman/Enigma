#ifndef ROTOR_H
#define ROTOR_H

#include <fstream>

using namespace std;

class rotor
{
  /* alphabet size */
  int* alpha;
  
  int input, count = 0;
  char* datafile;
  
  /* array for reading datafile into */
  int* testarr;

  /* array for mapping input to output */
  int** mapping;

  int rotate_count = 0;
  
public:

  rotor(char* dfile, int alphabet);

  /* store any errors encounted */
  int err_code = 0;
  char* err_file;
  
  ~rotor();

  /* load file and test for errors */
  void load();

  /* map rotor according to file specification */
  void rotormap();

  /* rotate rotor */
  void rotate();

  /* set initial position of rotor according to file specification */
  void initial_position(int initial_position);

  /* stores notch location in mapping array */
  bool notch();

  /* pass input through rotor (right to left), return output */
  void pass(int input, int& output);

  /* pass input through rotor (left to right), return output */
  void passback(int input, int& output);
};

#endif
