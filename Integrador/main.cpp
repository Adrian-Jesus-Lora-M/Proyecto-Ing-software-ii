
/*
*/

#include <fstream>
#include <iostream>
#include "string.h"

#ifndef SINGLE_FUNCTION_INPUT_PARSER_H
#include "single_function_input_parser.h"
#endif
#ifndef NORMAL_DISTRIBUTION_INTEGRAL_H
#include "normal_distribution_integral.h"
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
      const char* help_text = "PSP exercise 5A: Integrate the normal distribution from\nnegative infinity to the values given from standard input\nUsage: \n\tpsp_5a\n\n";
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
      single_function_input_parser parser;
      parser.set_input_stream( input_stream );
      normal_distribution_integral f;
      parser.set_function( &f );
      parser.parse_until_eof();
    }
}

/*
*/
