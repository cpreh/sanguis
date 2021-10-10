#ifndef SANGUIS_CLIENT_LOAD_MODEL_WEAPON_CATEGORY_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_WEAPON_CATEGORY_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/load/model/weapon_category_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sanguis::client::load::model
{

using weapon_category_unique_ptr = fcppt::unique_ptr<sanguis::client::load::model::weapon_category>;

}

#endif
