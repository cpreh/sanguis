#ifndef SANGUIS_MODEL_AUX__SERIALIZE_WEAPON_CATEGORY_HPP_INCLUDED
#define SANGUIS_MODEL_AUX__SERIALIZE_WEAPON_CATEGORY_HPP_INCLUDED

#include <sanguis/model/weapon_category_fwd.hpp>
#include <sge/parse/json/object.hpp>


namespace sanguis
{
namespace model
{
namespace aux_
{
namespace serialize
{

sge::parse::json::object
weapon_category(
	sanguis::model::weapon_category const &
);

}
}
}
}

#endif
