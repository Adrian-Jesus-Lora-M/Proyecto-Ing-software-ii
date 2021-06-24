/*
*/

#include "simple_input_parser.h"
#ifndef CONTRACT_H
#include "contract.h"
#endif

void
simple_input_parser::set_input_stream (istream * new_input)
{
  m_input_stream = new_input;
}

void
simple_input_parser::parse_until_eof (void)
{
  REQUIRE (m_input_stream != NULL);
  while (!(m_input_stream->eof ()))
    {
      read_line ();
      parse_last_line ();
    }
}

void
simple_input_parser::read_line (void)
{
  REQUIRE (!(m_input_stream->eof ()));
  const int
    input_buffer_size = 255;
  char
    input_buffer[input_buffer_size];
  m_input_stream->getline (input_buffer, input_buffer_size);
  //for some reason, the G++ standard library needs me to do this or it
  //doesn't register the EOF condition properly.  This makes no sense
  //to me...
  char c = m_input_stream->get();
  m_input_stream->putback( c );
  std::string input_line (input_buffer);
  //no source code line should be longer than 255!
  CHECK (input_line.size () < 255);
  set_last_line (transformed_line (input_line));
}

void
simple_input_parser::set_last_line (const std::string & new_line)
{
  m_last_line = new_line;
}

const
std::string & simple_input_parser::last_line (void) const
{
  return m_last_line;
}

void
simple_input_parser::parse_last_line (void)
{
  //basic version does nothing
}

std::string simple_input_parser::transformed_line (const std::string & line) const
{
  return line;
}

simple_input_parser::simple_input_parser (void)
{
  reset ();
}

simple_input_parser::~simple_input_parser (void)
{
}

void
simple_input_parser::reset (void)
{
  m_input_stream = NULL;
  m_last_line = "";
}

/*
*/
