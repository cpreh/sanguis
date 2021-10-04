#ifndef SANGUIS_SERVER_WEAPONS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/weapons/weapon_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis::server::weapons
{

using
unique_ptr
=
fcppt::unique_ptr<
	sanguis::server::weapons::weapon
>;

}

#endif
