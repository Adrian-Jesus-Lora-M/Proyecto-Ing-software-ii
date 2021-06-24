/*
*/

#ifndef SIMPLE_LOC_COUNTER_H
#define SIMPLE_LOC_COUNTER_H

#ifndef SIMPLE_INPUT_PARSER_H
#include "simple_input_parser.h"
#endif

#include <string>
#include <vector>

//subclass of simple_input_parser that stores countable lines of code in a buffer
//and can return their count.
class simple_loc_counter:public simple_input_parser
{
  public:
    //adds last line to the buffered lines if it is countable
  void parse_last_line (void);
  //the count of LOC
  int loc_count (void) const;
  //whether last line was comment
  bool last_line_is_comment (void) const;
  //whether last line was compiler directive
  bool last_line_is_compiler_directive (void) const;
  //whether we are in a block comment
  bool is_in_block_comment (void) const;
  //whether last line was a block begin
  bool last_line_is_block_begin (void) const;
  //whether last line was a block end
  bool last_line_is_block_end (void) const;
  //whether last line was part of a begin/end pair
  bool last_line_is_block_begin_or_end (void) const;
  //whether the last line was countable
  bool last_line_is_countable (void) const;
  //whether the last line was empty
  bool last_line_is_empty (void) const;
  //updates the block comment count
  void update_block_comment_count (void);
  //updates the block nesting level
  void update_block_nesting_level (void);
  //are we in a block?
  bool is_in_block (void) const;
  //block nesting level
  int block_nesting_level (void) const;
  //whether the last line starts with the given string
  bool last_line_starts_with (const std::string & search_string) const;
  //whether a given string starts with a search string
  static bool string_starts_with (const std::string & given_string,
				  const std::string & search_string);

  //returns the input string stripped of leading/trailing whitespace

     std::string string_stripped_of_whitespace (const std::string & input_string) const;
  //returns the transformed line (here, the line stripped of whitespace)
  virtual std::
    string transformed_line (const std::string & input_string) const;

  //constructor
    simple_loc_counter (void);
  //destructor
    virtual ~ simple_loc_counter (void);
  //resets the object
  virtual void reset (void);

  //writes the countable lines to the given output stream
  void write_countable_lines (ostream & ostr) const;

    protected:
    //the buffered countable lines
    std::vector < std::string > m_countable_lines;
  //the "block comment" nesting level
  int m_block_comment_nesting_level;
  //the "block" nesting level
  int m_block_nesting_level;
  //the beginning of a block comment
  static const std::string & block_comment_begin;
  //the end of a block comment
  static const std::string & block_comment_end;
  //the beginning of an inline comment
  static const std::string & inline_comment_begin;
  //the beginning of a compiler directive
  static const std::string & compiler_directive_begin;
  //the "begin block" string
  static const std::string & block_begin;
  //the "end block" string
  static const std::string & block_end;
  //whitespace characters
  static const std::string & whitespace_characters;
};

#endif

/*
*/
