#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <fstream>

using namespace std;

class reflector
{
  /* alphabet size */
  int* alpha;
  
  int input, count = 0;
  char* datafile;

  /* array for reading datafile into */
  int* testarr;

  /* array for mapping input to output */
  int** mapping;

public:

  reflector(char* dfile, int alphabet);

  ~reflector();

  /* Load file and test for errors */
  void load();

  /* store any errors encountered */
  int err_code = 0;
  char* err_file;

  /* map reflector according to file specification */
  void map();

  /* pass input through reflector, return output */
  void pass(int input, int& output);
};

#endif
