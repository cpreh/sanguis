#ifndef SANGUIS_SERVER_WEAPONS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/weapons/weapon_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

typedef
fcppt::unique_ptr<
	sanguis::server::weapons::weapon
>
unique_ptr;

}
}
}

#endif
