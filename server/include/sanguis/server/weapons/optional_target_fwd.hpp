#ifndef SANGUIS_SERVER_WEAPONS_OPTIONAL_TARGET_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_OPTIONAL_TARGET_FWD_HPP_INCLUDED

#include <sanguis/server/weapons/target_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace sanguis::server::weapons
{

using optional_target = fcppt::optional::object<sanguis::server::weapons::target>;

}

#endif
