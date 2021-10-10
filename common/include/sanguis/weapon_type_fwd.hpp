#ifndef SANGUIS_WEAPON_TYPE_FWD_HPP_INCLUDED
#define SANGUIS_WEAPON_TYPE_FWD_HPP_INCLUDED

#include <sanguis/weapon_types_fwd.hpp>
#include <fcppt/variant/from_list_fwd.hpp>

namespace sanguis
{

using weapon_type = fcppt::variant::from_list<sanguis::weapon_types>;

}

#endif
