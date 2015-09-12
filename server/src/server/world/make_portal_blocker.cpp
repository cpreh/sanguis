#include <sanguis/server/entities/doodad.hpp>
#include <sanguis/server/entities/doodad_unique_ptr.hpp>
#include <sanguis/server/entities/portal_blocker.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/world/make_portal_blocker.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sanguis::server::entities::doodad_unique_ptr
sanguis::server::world::make_portal_blocker(
	sanguis::server::environment::load_context &_load_context
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::server::entities::doodad
		>(
			fcppt::make_unique_ptr<
				sanguis::server::entities::portal_blocker
			>(
				_load_context
			)
		);
}
