/*
*/

#include <fstream>
#include <iostream>
#include "string.h"

#ifndef NUMBER_LIST_H
#include "number_list.h"
#endif

istream *
input_stream_from_args( int arg_count, const char** arg_vector )
{
  istream* Result = NULL;
  if ( arg_count == 1 )
    {
      Result = &cin;
    }
  else
    {
      const char* help_text = "\
PSP exercise 1A: Get the mean and standard deviation of a list\n
of ASCII real numbers, from either standard input or a text\n
file.\n\n\
Usage: \n \
\tpsp_1a\n\n";
      cout << help_text;
    }
  return Result;
}

int main( int arg_count, const char** arg_vector )
{
  //get the input stream, or print the help text as appropriate
  istream* input_stream = input_stream_from_args( arg_count, arg_vector );
  if ( input_stream != NULL )
    {
      //read the entries from the input stream
      number_list a_list;
      a_list.read_from_stream( *input_stream );
      cout << a_list.entry_count() << " numbers processed.\n";
      //output the mean, as appropriate
      if ( a_list.entry_count() > 0 )
	{
	  cout << "Mean: " << a_list.mean() << "\n";
	}
      else
	{
	  cout << "Too few entries to calculate mean\n";
	}
      //output the standard deviation, as appropriate
      if ( a_list.entry_count() > 1 )
	{
	  cout << "Standard Deviation: " << a_list.standard_deviation() << "\n";
	}
      else
	{
	  cout << "Too few entries to calculate standard deviation.\n";
	}
    }
}

/*
*/
