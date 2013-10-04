#ifndef SANGUIS_SERVER_WEAPONS_OPTIONAL_MAGAZINE_SIZE_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_OPTIONAL_MAGAZINE_SIZE_FWD_HPP_INCLUDED

#include <sanguis/server/weapons/magazine_size.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

typedef
fcppt::optional<
	sanguis::server::weapons::magazine_size
>
optional_magazine_size;

}
}
}

#endif
