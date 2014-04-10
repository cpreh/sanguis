#ifndef SANGUIS_SERVER_WEAPONS_OPTIONAL_TARGET_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_OPTIONAL_TARGET_FWD_HPP_INCLUDED

#include <sanguis/server/weapons/target_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

typedef
fcppt::optional<
	sanguis::server::weapons::target
>
optional_target;

}
}
}

#endif
