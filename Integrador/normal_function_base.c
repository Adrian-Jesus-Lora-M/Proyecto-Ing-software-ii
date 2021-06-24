/*
*/

#ifndef NORMAL_FUNCTION_BASE_H
#define NORMAL_FUNCTION_BASE_H

#ifndef SINGLE_VARIABLE_FUNCTION_H
#include "single_variable_function.h"
#endif

class normal_function_base : public single_variable_function
{
 public:
  virtual double at( double x ) const;
};


#endif

/*
*/
/*
*/
