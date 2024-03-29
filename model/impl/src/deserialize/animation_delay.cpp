#include <sanguis/model/animation_delay.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/impl/deserialize/animation_delay.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>

sanguis::model::optional_animation_delay
sanguis::model::impl::deserialize::animation_delay(sge::parse::json::object const &_object)
{
  return fcppt::optional::map(
      fcppt::optional::copy_value(sge::parse::json::find_member<sge::parse::json::int_type>(
          fcppt::make_cref(_object.members), sge::charconv::utf8_string{"delay"})),
      [](sge::parse::json::int_type const _value)
      { return sanguis::model::animation_delay{std::chrono::milliseconds{_value}}; });
}
