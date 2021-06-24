/*
*/

#ifndef SIMPLE_INPUT_PARSER_H
#define SIMPLE_INPUT_PARSER_H

#include <string>
#include <iostream>

//a standard "framework" for parsing a set of input lines
class simple_input_parser
{
  public:
    //sets input stream
  void set_input_stream (istream * new_input);
  //parse input until EOF
  void parse_until_eof (void);
  //reads single line from input, transforms it, stores it in last_line
  void read_line (void);
  //sets the last line read
  void set_last_line (const std::string & new_line);
  //last line read from input
  const std::string & last_line (void) const;
  //parses the last line read
  virtual void parse_last_line (void);
  //returns a "transformed" copy of the given line
  virtual std::string transformed_line (const std::string & line) const;
  //constructor
    simple_input_parser (void);
  //virtual destructor
    virtual ~ simple_input_parser (void);
  //resets the parser
  virtual void reset (void);

    private:
    //the input stream
    istream * m_input_stream;
  //the last line of input
    std::string m_last_line;
};

#endif

/*
*/
