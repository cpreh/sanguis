#ifndef SANGUIS_SERVER_WEAPONS_OPTIONAL_RELOAD_TIME_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_OPTIONAL_RELOAD_TIME_FWD_HPP_INCLUDED

#include <sanguis/server/weapons/reload_time.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace sanguis::server::weapons
{

using optional_reload_time = fcppt::optional::object<sanguis::server::weapons::reload_time>;

}

#endif
