#include <sanguis/doodad_type.hpp>
#include <sanguis/server/entities/doodad.hpp>
#include <sanguis/server/entities/portal_blocker.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>


sanguis::server::entities::portal_blocker::portal_blocker(
	sanguis::server::environment::load_context &_load_context
)
:
	sanguis::server::entities::doodad(
		_load_context,
		sanguis::doodad_type::portal_blocker
	)
{
}

sanguis::server::entities::portal_blocker::~portal_blocker()
= default;
