#ifndef SANGUIS_LOAD_MODEL_MAKE_WEAPON_CATEGORIES_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_MAKE_WEAPON_CATEGORIES_HPP_INCLUDED

#include <sanguis/load/model/global_parameters_fwd.hpp>
#include <sanguis/load/model/weapon_category_map.hpp>
#include <sanguis/model/part_fwd.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

sanguis::load::model::weapon_category_map
make_weapon_categories(
	sanguis::model::part const &,
	sanguis::load::model::global_parameters const &
);

}
}
}

#endif
