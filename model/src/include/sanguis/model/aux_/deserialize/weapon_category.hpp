#ifndef SANGUIS_MODEL_AUX__DESERIALIZE_WEAPON_CATEGORY_HPP_INCLUDED
#define SANGUIS_MODEL_AUX__DESERIALIZE_WEAPON_CATEGORY_HPP_INCLUDED

#include <sanguis/model/weapon_category.hpp>
#include <sanguis/model/aux_/deserialize/parameters_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace model
{
namespace aux_
{
namespace deserialize
{

sanguis::model::weapon_category
weapon_category(
	sanguis::model::aux_::deserialize::parameters const &,
	sge::parse::json::object const &
);

}
}
}
}

#endif
