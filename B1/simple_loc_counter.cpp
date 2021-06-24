
/*
*/

#include "simple_loc_counter.h"

#ifndef YAK_MIN_MAX_H
#include "yak_min_max.h"
#endif

void
simple_loc_counter::parse_last_line (void)
{
  if (last_line_is_countable ())
    {
      m_countable_lines.push_back (last_line ());
    }
}

int
simple_loc_counter::loc_count (void) const
{
  return m_countable_lines.size ();
}

bool
simple_loc_counter::last_line_is_comment (void) const
{
  bool Result = false;
  if (last_line_starts_with (block_comment_begin)
      || last_line_starts_with (inline_comment_begin)
      || is_in_block_comment ())
    {
      Result = true;
    }
  return Result;
}


bool
simple_loc_counter::last_line_is_compiler_directive (void) const
{
  bool Result = false;
  if (last_line_starts_with (compiler_directive_begin))
    {
      Result = true;
    }
  return Result;
}

bool
simple_loc_counter::is_in_block_comment (void) const
{
  bool Result = false;
  if (m_block_comment_nesting_level > 0)
    {
      Result = true;
    }
  return Result;
}

bool
simple_loc_counter::last_line_is_begin_or_end (void) const
{
  bool Result = false;
  if (last_line_starts_with (block_begin)
      || last_line_starts_with (block_end))
    {
      Result = true;
    }
  return Result;
}

bool
simple_loc_counter::last_line_is_empty (void) const
{
  return (last_line ().length () == 0);
}

bool
simple_loc_counter::last_line_is_countable (void) const
{
  bool Result = true;
  if ((last_line_is_comment ())
      || (last_line_is_begin_or_end ())
      || (last_line_is_compiler_directive ()) || (last_line_is_empty ()))
    {
      Result = false;
    }
  return Result;
}


void
simple_loc_counter::update_block_comment_count (void)
{
  //count through the string; add 1 to the block comment count if the begin
  //string is encountered, subtract one if the end string is encountered.
  for (unsigned int i = 0; i < last_line ().length (); ++i)
    {
      std::string line_remaining =
	last_line ().substr (i, last_line ().length ());
      if (string_starts_with (line_remaining, block_comment_begin))
	{
	  ++m_block_comment_nesting_level;
	}
      else if (string_starts_with (line_remaining, block_comment_end))
	{
	  --m_block_comment_nesting_level;
	}
    }
}

bool
  simple_loc_counter::
last_line_starts_with (const std::string & search_string) const
{
  return string_starts_with (last_line (), search_string);
}

bool
  simple_loc_counter::string_starts_with (const std::string & given_string,
					  const std::string & search_string)
{
  int
    substring_size =
    yak_min (given_string.length (), search_string.length ());
  std::string substring = given_string.substr (0, substring_size);
  bool Result = (substring == search_string);
  return Result;
}

std::string
  simple_loc_counter::
string_stripped_of_whitespace (const std::string & input_string) const
{
  std::string::size_type start =
    input_string.find_first_not_of (whitespace_characters);
  if (start == input_string.npos)
    {
      start = 0;
    }
  std::string::size_type end =
    input_string.find_last_not_of (whitespace_characters);
  if (end == input_string.npos)
    {
      end = 0;
    }
  std::string Result = input_string.substr (start, (end == 0) ? 0 : end + 1);
  return Result;
}

std::string
  simple_loc_counter::transformed_line (const std::string & input_string) const
{
  return string_stripped_of_whitespace (input_string);
}

simple_loc_counter::simple_loc_counter (void)
{
  reset ();
}

simple_loc_counter::~simple_loc_counter (void)
{
}

void
simple_loc_counter::reset (void)
{
  m_countable_lines.clear ();
  m_block_comment_nesting_level = 0;
}

void
simple_loc_counter::write_countable_lines (ostream & ostr) const
{
  for (std::vector < std::string >::const_iterator iter =
       m_countable_lines.begin (); iter != m_countable_lines.end (); ++iter)
    {
      ostr << *iter << "\n";
    }
}

const
  std::string & simple_loc_counter::block_comment_begin = "/*";

const
  std::string & simple_loc_counter::block_comment_end = "*/";

const
  std::string & simple_loc_counter::inline_comment_begin = "//";

const
  std::string & simple_loc_counter::compiler_directive_begin = "#";

const
  std::string & simple_loc_counter::block_begin = "{";

const
  std::string & simple_loc_counter::block_end = "}";

const
  std::string & simple_loc_counter::whitespace_characters = " \t\n\0x32";

/*
*/
