#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <fstream>

using namespace std;

class plugboard
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
  
  plugboard(char* dfile, int alphabet);
  
  ~plugboard();

  /* Load file and test for errors */
  void load();

  /* store any errors encounted */
  int err_code = 0;
  char* err_file;

  /* map plugboard according to file specification */
  void map();

  /* pass input through plugboard, return output */
  void pass(int intput, int& output);
  
};

#endif
