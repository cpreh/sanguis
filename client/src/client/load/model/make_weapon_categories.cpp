#include <sanguis/client/load/model/global_parameters.hpp>
#include <sanguis/client/load/model/lookup_weapon_name.hpp>
#include <sanguis/client/load/model/make_weapon_categories.hpp>
#include <sanguis/client/load/model/weapon_category.hpp>
#include <sanguis/client/load/model/weapon_category_map.hpp>
#include <sanguis/model/part.hpp>
#include <sanguis/model/weapon_category_map.hpp>
#include <fcppt/copy.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::client::load::model::weapon_category_map
sanguis::client::load::model::make_weapon_categories(
    fcppt::log::object &_log,
    sanguis::model::part const &_part,
    sanguis::client::load::model::global_parameters const &_parameters)
{
  return fcppt::algorithm::map<sanguis::client::load::model::weapon_category_map>(
      _part.weapon_categories(),
      [&_log,
       &_parameters](sanguis::model::weapon_category_map::value_type const &_weapon_category_pair)
      {
        return std::make_pair(
            sanguis::client::load::model::lookup_weapon_name(_weapon_category_pair.first),
            fcppt::make_unique_ptr<sanguis::client::load::model::weapon_category>(
                _log,
                _weapon_category_pair.second,
                _parameters.new_image(fcppt::copy(_weapon_category_pair.second.image_name()))));
      });
}
