#ifndef SANGUIS_SERVER_AI_PATHING_OPTIONAL_TARGET_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_AI_PATHING_OPTIONAL_TARGET_FWD_HPP_INCLUDED

#include <sanguis/server/ai/pathing/target_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis::server::ai::pathing
{

using
optional_target
=
fcppt::optional::object<
	sanguis::server::ai::pathing::target
>;

}

#endif
