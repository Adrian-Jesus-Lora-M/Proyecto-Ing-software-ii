/*
*/

#ifndef CLASS_BASED_LOC_COUNTER_H
#include "class_based_loc_counter.h"
#endif
#ifndef YAK_EXCEPTION_H
#include "yak_exception.h"
#endif

istream *
input_stream_from_args (int arg_count, const char **arg_vector)
{
  istream *Result = NULL;
  if (arg_count == 1)
    {
      Result = &cin;
    }
  else
    {
      const char *help_text = "PSP exercise 3A: Count class and total LOC.\n Usage:\n\tpsp_3a\n\n ";
      cout << help_text;
    }
  return Result;
}

int
main (int arg_count, const char **arg_vector)
{
  //get the input stream, or print the help text as appropriate
  istream *input_stream = input_stream_from_args (arg_count, arg_vector);
  if (input_stream != NULL)
    {
      class_based_loc_counter counter;
      try
      {
	counter.set_input_stream (input_stream);
	counter.parse_until_eof ();
	//output the counted lines
	//counter.write_countable_lines( cout );
	//output the loc
	cout << "Total LOC: " << counter.loc_count () << "\n";
	cout << "classname:feature count:LOC by class:\n";
	for (std::map < std::string, class_metric >::const_iterator iter =
	     counter.class_map ().begin ();
	     iter != counter.class_map ().end (); ++iter)
	  {
	    cout << iter->first << ":"
	      << iter->second.feature_count << ":"
	      << iter->second.loc << "\n";
	  }
      }
      catch (exception & e)
      {
	cout << "Aborted with exception: " << e.what () << "\n";
	cout << "last line parsed: \n" << counter.last_line () << "\n";
      }
    }
}


/*
*/
