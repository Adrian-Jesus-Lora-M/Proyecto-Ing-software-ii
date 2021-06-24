#ifndef NORMAL_DISTRIBUTION_INTEGRAL_H
#define NORMAL_DISTRIBUTION_INTEGRAL_H

#ifndef NORMAL_FUNCTION_BASE_H
#include "normal_function_base.h"
#endif
#ifndef SIMPSON_INTEGRATOR_H
#include "simpson_integrator.h"
#endif

class normal_distribution_integral : public single_variable_function
{
 public:
  virtual double at( double x ) const;
 protected:
  simpson_integrator homer;
  normal_function_base base;
};

#endif
#include "normal_distribution_integral.h"

#ifndef CONTRACT_H
#include "contract.h"
#endif

double
normal_distribution_integral::at( double x ) const
{
  double Result = 0;
  if ( x < 0 )
    {
      Result = 0.5 - homer.integral( base, 0, 0-x );
    }
  else if ( x > 0 )
    {
      Result = 0.5 + homer.integral( base, 0, x );
    }
  else if ( x == 0 )
    {
      Result = 0.5;
    }
  else
    {
      CHECK( false );
    }
  return Result;
}
