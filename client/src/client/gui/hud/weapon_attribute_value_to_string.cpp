#include <sanguis/weapon_attribute_value.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_value_to_string.hpp>
#include <sge/font/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <sstream>
#include <fcppt/config/external_end.hpp>

sge::font::string sanguis::client::gui::hud::weapon_attribute_value_to_string(
    sanguis::weapon_attribute_value const _value)
{
  std::basic_ostringstream<sge::font::char_type> stream;

  stream.precision(4);

  stream << _value;

  return stream.str();
}
