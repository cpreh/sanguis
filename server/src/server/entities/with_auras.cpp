#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/auras/unique_ptr.hpp>
#include <sanguis/server/collision/ghost.hpp>
#include <sanguis/server/collision/ghost_container.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::collision::world::body_enter_container
sanguis::server::entities::with_auras::add_aura(
	sanguis::server::auras::unique_ptr &&_aura
)
{
	auras_.push_back(
		std::move(
			_aura
		)
	);

	return
		this->sanguis::server::entities::with_ghosts::add_ghost(
			auras_.back()->create_ghost()
		);
}

sanguis::server::entities::with_auras::with_auras(
	sanguis::server::auras::container &&_auras
)
:
	sanguis::server::entities::with_ghosts(),
	auras_(
		std::move(
			_auras
		)
	)
{
	// TODO: Can we initialize this directly?
	this->init_ghosts(
		fcppt::algorithm::map<
			sanguis::server::collision::ghost_container
		>(
			_auras,
			[](
				sanguis::server::auras::unique_ptr const &_aura
			)
			{
				return
					_aura->create_ghost();
			}
		)
	);
}

sanguis::server::entities::with_auras::~with_auras()
{
}

sanguis::server::auras::container const &
sanguis::server::entities::with_auras::auras() const
{
	return
		auras_;
}
