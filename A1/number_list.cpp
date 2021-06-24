/*
*/

#include "number_list.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>

void
number_list::read_from_stream( istream& input )
{
  int line_number = 1;
  while ( !(input.eof()) )
    {
      read_entry_from_stream( input, line_number );
    }
}

void
number_list::read_entry_from_stream( istream& input, int line_number )
{
  double next_entry;
  const int input_buffer_size = 255;
  char input_buffer[ input_buffer_size ];
  input.getline( input_buffer, input_buffer_size );
  //now convert to floating point using strtod
  char* conversion_end = NULL;
  next_entry = strtod( input_buffer, &conversion_end );
  if ( conversion_end != input_buffer )
    {
      add_entry( next_entry );
    }
  else if ( !(input.eof()) )
    {
      cerr << "(unknown file):" << line_number << ":Error in conversion to double\n";
    }
}

double
number_list::sum( void ) const
{
  double Result = 0;
  for ( list<double>::const_iterator iter = begin();
	iter != end();
	++iter )
    {
      Result += *iter;
    }
  return Result;
}

double
number_list::mean( void ) const
{
  assert( entry_count() > 0 );
  return sum() / entry_count();
}

double
number_list::standard_deviation( void ) const
{
  assert( entry_count() > 1 );
  double sum_of_square_differences = 0;
  for ( list<double>::const_iterator iter = begin();
	iter != end();
	++iter )
    {
      const double this_square_difference = *iter - mean();
      sum_of_square_differences += this_square_difference * this_square_difference;
    }
  return sqrt( sum_of_square_differences / ( entry_count() - 1 ));
}

int
number_list::entry_count( void ) const
{
  return size();
}

void
number_list::add_entry( double new_entry )
{
  push_back( new_entry );
}

/*
*/
