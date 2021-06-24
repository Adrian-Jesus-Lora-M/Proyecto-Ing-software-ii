/*
*/

#ifndef SIMPSON_INTEGRATOR_H
#define SIMPSON_INTEGRATOR_H

#ifndef SINGLE_VARIABLE_FUNCTION_H
#include "single_variable_function.h"
#endif

class simpson_integrator
{
 public:
  //sets the acceptable error in the computation
  void set_acceptable_error( double new_error );
  //sets the starting number of segments
  void set_starting_segment_count( int new_starting_segment_count );
  //returns the simpson integral of the given single variable function between the two limits
  double integral( const single_variable_function& f, double lower_limit, double upper_limit ) const;
  //constructor
  simpson_integrator::simpson_integrator( void );
 protected:
  double acceptable_error;
  int starting_segment_count;
  double single_pass( const single_variable_function& f, double lower_limit, double upper_limit, int segment_count ) const;
  bool is_odd( int x ) const;
};

#endif
/*
*/
/*
*/

#include "simpson_integrator.h"

#ifndef CONTRACT_H
#include "contract.h"
#endif

void
simpson_integrator::set_acceptable_error( double new_error )
{
  REQUIRE( new_error > 0 );
  acceptable_error = new_error;
}

void
simpson_integrator::set_starting_segment_count( int new_starting_segment_count )
{
  REQUIRE( new_starting_segment_count > 0 );
  REQUIRE( !is_odd( new_starting_segment_count ) );
  starting_segment_count = new_starting_segment_count;
}

simpson_integrator::simpson_integrator( void ) :
acceptable_error( 0.00001 ),
starting_segment_count( 20 )
{
}

double
simpson_integrator::integral( const single_variable_function& f,
			      double lower_limit, double upper_limit ) const
{
  double Result = 0;
  double previous_result = 0;
  double last_error = 0;
  int segment_count = starting_segment_count;
  bool result_has_been_calculated = false;
  while ( !result_has_been_calculated
	  || ( last_error > acceptable_error ) )
    {
      previous_result = Result;
      Result = single_pass( f, lower_limit, upper_limit, segment_count );
      last_error = fabs( Result - previous_result );
      //cout << "Segments: " << segment_count << "; error: " << last_error << "\n";
      segment_count *= 2;
      result_has_been_calculated = true;
    }
  return Result;
}


double
simpson_integrator::single_pass( const single_variable_function& f,
				 double lower_limit, double upper_limit,
				 int segment_count ) const
{
  double Result = 0;
  const double segment_width = ( upper_limit - lower_limit ) / static_cast<double>(segment_count);
  const double third_width = segment_width / static_cast< double >(3);
  Result = f.at( lower_limit ) * third_width;
  //cout << "From " << lower_limit << " to " << upper_limit << "\n";
  //cout << "Width " << segment_width << "\n";
  //cout << "Term 0: " << Result << "\n";
  for ( int i = 1; i < segment_count; ++i )
    {
      const double xi = lower_limit + static_cast< double >( i ) * segment_width;
      const double segment_value = f.at( xi ) * third_width;
      //cout << "Xi: " << xi << " ";
      //cout << "F: " << f.at( lower_limit + static_cast<double>(i) * segment_width ) << "  ";
      if ( is_odd(i) )
	{
	  Result += 4 * segment_value;
	  //cout << "Term " << i << ": " << 4 * segment_value << "\n";
	}
      else
	{
	  Result += 2 * segment_value;
	  //cout << "Term " << i << ": " << 2 * segment_value << "\n";
	}
    }
  //cout << "f( upper ): " << f.at( upper_limit ) << "\n";
  Result += f.at( upper_limit ) * third_width;
  CHECK( fabs( upper_limit - ( lower_limit + segment_count * segment_width ) ) < acceptable_error );
  return Result;
}

bool
simpson_integrator::is_odd( int x ) const
{
  return ( x & 1 );
}
/*
*/
