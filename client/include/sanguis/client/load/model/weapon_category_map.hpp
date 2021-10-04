#ifndef SANGUIS_CLIENT_LOAD_MODEL_WEAPON_CATEGORY_MAP_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_WEAPON_CATEGORY_MAP_HPP_INCLUDED

#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/client/load/model/weapon_category_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/optional/comparison.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis::client::load::model
{

using
weapon_category_map
=
std::map<
	sanguis::optional_primary_weapon_type,
	sanguis::client::load::model::weapon_category_unique_ptr
>;

}

#endif
