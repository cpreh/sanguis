#ifndef SANGUIS_SERVER_WEAPONS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/weapons/weapon_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

typedef std::unique_ptr<
	sanguis::server::weapons::weapon
> unique_ptr;

}
}
}

#endif
