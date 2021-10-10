#ifndef SANGUIS_SERVER_WEAPONS_CONST_OPTIONAL_REF_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_CONST_OPTIONAL_REF_FWD_HPP_INCLUDED

#include <sanguis/server/weapons/weapon_fwd.hpp>
#include <fcppt/optional/reference_fwd.hpp>

namespace sanguis::server::weapons
{

using const_optional_ref = fcppt::optional::reference<sanguis::server::weapons::weapon const>;

}

#endif
