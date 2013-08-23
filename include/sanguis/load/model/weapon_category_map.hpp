#ifndef SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_MAP_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_MAP_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/load/model/weapon_category_unique_ptr.hpp>
#include <fcppt/optional_comparison.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

typedef
std::map<
	sanguis::optional_primary_weapon_type,
	sanguis::load::model::weapon_category_unique_ptr
>
weapon_category_map;

}
}
}

#endif
