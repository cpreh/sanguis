#ifndef SANGUIS_SERVER_WEAPONS_OPTIONAL_RELOAD_TIME_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_OPTIONAL_RELOAD_TIME_FWD_HPP_INCLUDED

#include <sanguis/server/weapons/reload_time.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

typedef
fcppt::optional<
	sanguis::server::weapons::reload_time
>
optional_reload_time;

}
}
}

#endif
