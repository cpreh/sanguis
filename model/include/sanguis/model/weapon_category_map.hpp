#ifndef SANGUIS_MODEL_WEAPON_CATEGORY_MAP_HPP_INCLUDED
#define SANGUIS_MODEL_WEAPON_CATEGORY_MAP_HPP_INCLUDED

#include <sanguis/model/weapon_category.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace model
{

typedef
std::unordered_map<
	fcppt::string,
	sanguis::model::weapon_category
>
weapon_category_map;

}
}

#endif
