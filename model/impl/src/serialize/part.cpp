#include <sanguis/model/part.hpp>
#include <sanguis/model/impl/serialize/image_name.hpp>
#include <sanguis/model/impl/serialize/part.hpp>
#include <sanguis/model/impl/serialize/weapon_category_map.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/array/object_impl.hpp>
#include <fcppt/optional/cat.hpp>
#include <fcppt/optional/object_impl.hpp>

sge::parse::json::object sanguis::model::impl::serialize::part(sanguis::model::part const &_part)
{
  return sge::parse::json::object(fcppt::optional::cat<sge::parse::json::member_map>(
      fcppt::array::object<fcppt::optional::object<sge::parse::json::member>, 2>{
          fcppt::optional::object<sge::parse::json::member>{
              sanguis::model::impl::serialize::weapon_category_map(_part.weapon_categories())},
          sanguis::model::impl::serialize::image_name(_part.image_name())}));
}
