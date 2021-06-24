/*
*/

#ifndef NUMBER_LIST_H
#define NUMBER_LIST_H

#include <list>
#include <iostream>

//a class which encapsulates a list of double values, adding the features of
//mean and standard deviation
class number_list : public list< double >
{
 public:
  void read_from_stream( istream& input );
  void read_entry_from_stream( istream& input, int line_number );
  double sum( void ) const;
  double mean( void ) const;
  double standard_deviation( void ) const;
  int entry_count( void ) const;
  void add_entry( double new_entry );
};

#endif

/*
*/
