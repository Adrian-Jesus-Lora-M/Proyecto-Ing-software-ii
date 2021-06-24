/*
*/

#include "class_based_loc_counter.h"
#ifndef CONTRACT_H
#include "contract.h"
#endif

const
std::string class_based_loc_counter::class_begin ("class ");

const
std::string class_based_loc_counter::scope_operator ("::");

class_based_loc_counter::class_based_loc_counter (void):
simple_loc_counter ()
{
  reset ();
}

void
class_based_loc_counter::reset (void)
{
  simple_loc_counter::reset();
  m_class_map.clear ();
  m_in_class_declaration = false;
  m_in_class_feature = false;
  m_current_class_name = "UNSET";
  m_previous_line = "";
}

void
class_based_loc_counter::parse_last_line (void)
{
  simple_loc_counter::parse_last_line ();
  //cout << m_class_map[ "class_based_loc_counter" ].loc << ":" << m_countable_lines.size() << ":" << last_line() << "\n";
  if (last_line_is_countable ())
    {
      if (last_line_is_class_begin ())
	{
	  CHECK (m_in_class_declaration == false);
	  m_in_class_declaration = true;
	  m_current_class_name = class_name_from_class_begin (last_line ());
	}
      if (m_in_class_declaration)
	{
	  adjust_class_loc_count (m_current_class_name, 1);
	  if (last_line_declares_feature ())
	    {
	      adjust_class_feature_count (m_current_class_name, 1);
	    }
	}
      if (last_line_is_feature_begin ())
	{
	  //cout << "<<begin feature; previous line = " << m_previous_line << ">>";
	  CHECK (m_in_class_feature == false);
	  m_in_class_feature = true;
	  m_current_class_name =
	    class_name_from_external_feature (last_line ());
	  //add one for the return type declaration, as indent usu puts it on the previous line
	  if ((m_previous_line.length () > 0))
	    {
	      //cout << "*" << m_previous_line;
	      adjust_class_loc_count (m_current_class_name, 1);
	    }
	}
      if (m_in_class_feature)
	{
	  adjust_class_loc_count (m_current_class_name, 1);
	}
      if (last_line_is_data_feature ())
	{
	  adjust_class_loc_count (class_name_from_external_feature
				  (last_line ()), 1);
	  if (m_previous_line.length () > 0)
	    {
	      //cout << "&" << m_previous_line;
	      adjust_class_loc_count (m_current_class_name, 1);
	    }
	}
    }
  if (last_line_is_class_end ())
    {
      CHECK (block_nesting_level () == 0);
      CHECK (m_in_class_declaration == true);
      CHECK (m_in_class_feature == false);
      m_in_class_declaration = false;
    }
  if (last_line_is_feature_end ())
    {
      //cout << "<<end feature, nesting:" << block_nesting_level() << ">>";
      CHECK (block_nesting_level () == 0);
      CHECK (m_in_class_declaration == false);
      CHECK (m_in_class_feature == true);
      m_in_class_feature = false;
    }
  m_previous_line = last_line ();
}


std::string
  class_based_loc_counter::
class_name_from_class_begin (const std::string & str) const
{
  REQUIRE (last_line_is_class_begin ());
  std::string::size_type class_begin_position =
    last_line ().find (class_begin);
  CHECK (class_begin_position != last_line ().npos);
  std::string::size_type next_white_space_position =
    last_line ().find_first_of (whitespace_characters, class_begin_position);
  CHECK (class_begin_position != last_line ().npos);
  std::string::size_type next_word_position =
    last_line ().find_first_not_of (whitespace_characters,
				    next_white_space_position);
  CHECK (next_word_position != last_line ().npos);

  std::string whitespace_characters_and_colon = whitespace_characters;
  whitespace_characters_and_colon.append (":");

  std::string::size_type end_of_class_name_position =
    last_line ().find_first_of (whitespace_characters_and_colon,
				next_word_position);
  if (end_of_class_name_position == last_line ().npos)
    {
      end_of_class_name_position = last_line ().length ();
    }
  std::string Result =
    last_line ().substr (next_word_position,
			 end_of_class_name_position - next_word_position);
  //cout << Result;
  return Result;
}

std::string
  class_based_loc_counter::
class_name_from_external_feature (const std::string & str) const
{
  //this is used by last_line_is_feature_begin, so we can't use it here as
  //a requirement...  be cautious!

  std::string::size_type scope_operator_position = last_line ().length ();
  while (scope_operator_position != last_line ().npos)
    {
      scope_operator_position =
	last_line ().rfind (scope_operator, scope_operator_position - 1);
      if (scope_operator_position != last_line ().npos);
      {
	std::string beginning_of_string =
	  last_line ().substr (0, scope_operator_position);
	//cout << "<<" << beginning_of_string << ">>";
	std::string::size_type begin =
	  beginning_of_string.find_last_of (whitespace_characters);
	if (begin == beginning_of_string.npos)
	  {
	    begin = 0;
	  }
	else
	  {
	    begin = begin + 1;
	  }
	std::string possible_result =
	  beginning_of_string.substr (begin, scope_operator_position);
	//cout << "POSS:" << possible_result;
	if (has_entry_for_class_name (possible_result))
	  {
	    return possible_result;
	  }
      }
    }
  return "";
}

bool
class_based_loc_counter::last_line_is_class_begin (void) const
{
  bool Result = false;
  if (last_line_starts_with (class_begin))
    {
      Result = true;
    }
  return Result;
}


bool
class_based_loc_counter::last_line_is_class_end (void) const
{
  bool Result = false;
  if (last_line_is_block_end () && m_in_class_declaration)
    {
      Result = true;
    }
  return Result;
}

bool
class_based_loc_counter::last_line_contains_scope_operator (void) const
{
  return (last_line ().find (scope_operator) != last_line ().npos);
}

bool
  class_based_loc_counter::last_line_contains_known_class_before_scope_operator
  (void) const
{
  bool Result = false;
  if (last_line_contains_scope_operator ())
    {
      std::string class_name =
	class_name_from_external_feature (last_line ());
      if (has_entry_for_class_name (class_name))
	{
	  Result = true;
	}
    }
  return Result;
}

bool
class_based_loc_counter::last_line_is_feature_begin (void) const
{
  bool Result = false;
  if (last_line_contains_known_class_before_scope_operator ())
    {
      if (!last_line_is_data_feature ())
	{
	  Result = true;
	}
    }
  return Result;
}

bool
class_based_loc_counter::last_line_is_feature_end (void) const
{
  bool Result = false;
  if (last_line_is_block_end ()
      && m_in_class_feature && (block_nesting_level () == 0))
    {
      Result = true;
    }
  return Result;
}

bool
class_based_loc_counter::last_line_is_data_feature (void) const
{
  bool Result = false;
  if (last_line_contains_known_class_before_scope_operator ())
    {
      if (last_line ().find (";") != last_line ().npos)
	{
	  Result = true;
	}
    }
  return Result;
}

bool
class_based_loc_counter::last_line_declares_feature (void) const
{
  bool Result = false;
  if (m_in_class_declaration
      && (last_line ().find (";") != last_line ().npos))
    {
      Result = true;
    }
  return Result;
}

bool
  class_based_loc_counter::has_entry_for_class_name (const yak_string &
						     class_name) const
{
  bool Result = false;
  if (class_map ().find (class_name) != class_map ().end ())
    {
      Result = true;
    }
  return Result;
}

void
class_based_loc_counter::
adjust_class_feature_count (const std::string & class_name, int adjustment)
{
  if (!has_entry_for_class_name (class_name))
    {
      m_class_map[class_name] = class_metric ();
    }
  m_class_map[class_name].feature_count += adjustment;
}

void
class_based_loc_counter::
adjust_class_loc_count (const std::string & class_name, int adjustment)
{
  if (!has_entry_for_class_name (class_name))
    {
      m_class_map[class_name] = class_metric ();
    }
  m_class_map[class_name].loc += adjustment;
}

const
std::map < std::string,
  class_metric > & class_based_loc_counter::class_map (void) const
{
  return m_class_map;
}

/*
*/
