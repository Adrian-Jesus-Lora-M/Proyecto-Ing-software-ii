/*
*/

#ifndef CLASS_BASED_LOC_COUNTER_H
#define CLASS_BASED_LOC_COUNTER_H

#ifndef SIMPLE_LOC_COUNTER_H
#include "simple_loc_counter.h"
#endif
#ifndef CLASS_METRIC_H
#include "class_metric.h"
#endif

#include <map>

class class_based_loc_counter:public simple_loc_counter
{
  protected:
    //mapping of class names to metrics
  std::map < std::string, class_metric > m_class_map;
  //are we in a class declaration?
  bool m_in_class_declaration;
  //are we in a class feature implementation?
  bool m_in_class_feature;
  //name of the class we're in
    std::string m_current_class_name;
  static const std::string class_begin;
  static const std::string scope_operator;
    std::string m_previous_line;

    public:
    //adds the last line to method/class counts as appropriate
    virtual void parse_last_line (void);
    std::string class_name_from_class_begin (const std::string & str) const;
    std::string class_name_from_external_feature (const std::string & str) const;
  bool last_line_is_class_begin (void) const;
  bool last_line_is_class_end (void) const;
  bool last_line_is_feature_begin (void) const;
  bool last_line_is_feature_end (void) const;
  bool last_line_is_data_feature (void) const;
  bool last_line_declares_feature (void) const;
  bool last_line_contains_scope_operator (void) const;
  bool last_line_contains_known_class_before_scope_operator (void) const;
  void adjust_class_feature_count (const std::string & class_name,
				   int adjustment);
  void adjust_class_loc_count (const std::string & class_name,
			       int adjustment);
  bool has_entry_for_class_name (const std::string & class_name) const;
  const std::map < std::string, class_metric > &class_map (void) const;

    class_based_loc_counter (void);
  virtual void reset (void);

};

#endif


/*
*/
