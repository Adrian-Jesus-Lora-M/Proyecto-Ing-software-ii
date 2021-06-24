/*
*/
#ifndef SINGLE_FUNCTION_INPUT_PARSER_H
#define SINGLE_FUNCTION_INPUT_PARSER_H

#ifndef SIMPLE_INPUT_PARSER_H
#include "simple_input_parser.h"
#endif
#ifndef SINGLE_VARIABLE_FUNCTION_H
#include "single_variable_function.h"
#endif

class single_function_input_parser : public simple_input_parser
{
 public:
  virtual void parse_last_line( void );
  void set_function( single_variable_function* const new_function );
  single_function_input_parser( void );
 protected:
  single_variable_function* f;
};




#endif

/*
*/
/*
*/
#include "single_function_input_parser.h"

#ifndef CONTRACT_H
#include "contract.h"
#endif

void
single_function_input_parser::parse_last_line( void )
{
  REQUIRE( f != NULL );
  char* conversion_end = NULL;
  double new_x = strtod( last_line().c_str(), &conversion_end );
  if ( conversion_end == last_line().data() )
    {
      cerr << "Not a double : " << last_line() << "\n";
    }
  else
    {
      cout << new_x << ": " << f->at( new_x ) << "\n";
    }
}

void
single_function_input_parser::set_function( single_variable_function* const new_function )
{
  f = new_function;
}

single_function_input_parser::single_function_input_parser( void ):
f( NULL )
{
}

/*
*/
