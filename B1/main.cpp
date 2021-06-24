/*
*/

#ifndef SIMPLE_LOC_COUNTER_H
#include "simple_loc_counter.h"
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
      const char *help_text = "PSP exercise 2A: Count the physical LOC from standard input\n according to the style and counting guidelines in reports \n 1A and 2A. \n \n Usage:\n \tpsp_2a \n \n";
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
      simple_loc_counter counter;
      counter.set_input_stream (input_stream);
      counter.parse_until_eof ();
      //output the loc
      cout << "LOC: " << counter.loc_count () << "\n";
    }
}


/*
*/
simple_input_parser.e
deferred class SIMPLE_INPUT_PARSER

feature {ANY}

   parse_until_eof is
      --parses all input until an EOF is reached
      require
         input_stream /= Void;
      do
         from
         until
            input_stream.end_of_input
         loop
            read_line;
            if not input_stream.end_of_input then
               parse_last_line;
            end;
         end;
      end -- parse_until_eof

   set_input(new_input_stream: INPUT_STREAM) is
      --sets the input stream
      do
         input_stream := new_input_stream;
      end -- set_input

   read_line is
      --reads a line from standard input
      do
         input_stream.read_line;
         last_line := transformed_line(input_stream.last_string);
      end -- read_line

   last_line: STRING;

   input_stream: INPUT_STREAM;

   parse_last_line is

deferred
      end -- parse_last_line

   transformed_line(to_transform: STRING): STRING is
      --transforms the line according to rules defined in subclasses
      do
         Result := to_transform;
      end -- transformed_line

end -- class SIMPLE_INPUT_PARSER
simple_loc_counter.e
class SIMPLE_LOC_COUNTER
-- counts one form of LOC in eiffel files

inherit
   SIMPLE_INPUT_PARSER
      redefine parse_last_line, transformed_line
      end;

creation {ANY}
   make

feature {ANY}

   make is
      do
         !!counted_lines.make(1,0);
      end -- make

   parse_last_line is
      -- store countable lines in an array
      do
         if last_line_is_countable then
            counted_lines.add_last(last_line);
         end;
      end -- parse_last_line

   counted_lines: ARRAY[STRING];
      --array containing countable lines

   loc_count: INTEGER is
      -- number of lines counted as LOC
      do
         Result := counted_lines.count;
      end -- loc_count

   last_line_is_comment: BOOLEAN is
      do
         if last_line_starts_with(comment_begin) then
            Result := true;
         else
            Result := false;
         end;
      end -- last_line_is_comment

   comment_begin: STRING is "--";

   last_line_is_compiler_directive: BOOLEAN is false;

   in_block_comment: BOOLEAN is false;

   last_line_starts_with(test_string: STRING): BOOLEAN is
      do
         if last_line.has_prefix(test_string) then
            Result := true;
         else
            Result := false;
         end;
      end -- last_line_starts_with

   last_line_is_countable: BOOLEAN is
      do
         if last_line_is_comment or last_line_is_begin_or_end or last_line_is_empty then
            Result := false;
         else
            Result := true;
         end;
      end -- last_line_is_countable

   last_line_is_begin_or_end: BOOLEAN is
      do
         if last_line_starts_with("do") or last_line_starts_with("end") then
            Result := true;
         else
            Result := false;
         end;
      end -- last_line_is_begin_or_end

   last_line_is_empty: BOOLEAN is
      do
         if last_line.empty then
            Result := true;
         else
            Result := false;
         end;
      end -- last_line_is_empty

   transformed_line(string: STRING): STRING is
      do
         Result := string_stripped_of_whitespace(string);
      end -- transformed_line

   string_stripped_of_whitespace(string: STRING): STRING is
      do
         Result := string.twin;
         Result.replace_all('%T',' ');
         Result.left_adjust;
         Result.right_adjust;
      end -- string_stripped_of_whitespace

   print_counted_lines(output: OUTPUT_STREAM) is
      local
         index: INTEGER;
      do
         from
            index := counted_lines.lower;
         until
            not counted_lines.valid_index(index)
         loop
            output.put_string(counted_lines.item(index));
            output.put_string("%N");
            index := index + 1;
         end;
      end -- print_counted_lines

end -- class SIMPLE_LOC_COUNTER
main.e
class MAIN

creation {ANY}
   make

feature {ANY}

   make is
      local
         simple_loc_counter: SIMPLE_LOC_COUNTER;
      do
         !!simple_loc_counter.make;
         simple_loc_counter.set_input(io);
         simple_loc_counter.parse_until_eof;
         std_output.put_string("LOC: ");
         std_output.put_integer(simple_loc_counter.loc_count);
      end -- make

end -- class MAIN
