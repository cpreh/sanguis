#ifndef SANGUIS_SERVER_AI_PATHING_UPDATE_TRAIL_HPP_INCLUDED
#define SANGUIS_SERVER_AI_PATHING_UPDATE_TRAIL_HPP_INCLUDED

#include <sanguis/server/ai/pathing/optional_target.hpp>
#include <sanguis/server/ai/pathing/trail.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <fcppt/reference_fwd.hpp>


namespace sanguis::server::ai::pathing
{

sanguis::server::ai::pathing::optional_target
update_trail(
	fcppt::reference<
		sanguis::server::ai::pathing::trail
	>,
	sanguis::server::entities::with_ai const &
);

}

#endif
