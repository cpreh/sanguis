#ifndef SANGUIS_MODEL_IMPL_SERIALIZE_WEAPON_CATEGORY_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_SERIALIZE_WEAPON_CATEGORY_HPP_INCLUDED

#include <sanguis/model/weapon_category_fwd.hpp>
#include <sge/parse/json/object.hpp>


namespace sanguis::model::impl::serialize
{

sge::parse::json::object
weapon_category(
	sanguis::model::weapon_category const &
);

}

#endif
