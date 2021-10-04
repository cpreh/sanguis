#ifndef SANGUIS_SERVER_AI_PATHING_OPTIONAL_TRAIL_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_AI_PATHING_OPTIONAL_TRAIL_FWD_HPP_INCLUDED

#include <sanguis/server/ai/pathing/trail.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis::server::ai::pathing
{

using
optional_trail
=
fcppt::optional::object<
	sanguis::server::ai::pathing::trail
>;

}

#endif
