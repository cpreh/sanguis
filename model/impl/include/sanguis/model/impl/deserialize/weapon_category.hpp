#ifndef SANGUIS_MODEL_IMPL_DESERIALIZE_WEAPON_CATEGORY_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_DESERIALIZE_WEAPON_CATEGORY_HPP_INCLUDED

#include <sanguis/model/weapon_category.hpp>
#include <sge/parse/json/object_fwd.hpp>

namespace sanguis::model::impl::deserialize
{

sanguis::model::weapon_category weapon_category(sge::parse::json::object const &);

}

#endif
