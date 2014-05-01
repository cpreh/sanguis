#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/auras/create_callback.hpp>
#include <sanguis/server/auras/create_callback_container.hpp>
#include <sanguis/server/auras/unique_ptr.hpp>
#include <sanguis/server/collision/ghost.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


void
sanguis::server::entities::with_auras::add_aura(
	sanguis::server::auras::unique_ptr &&_aura
)
{
	auras_.push_back(
		std::move(
			_aura
		)
	);

	this->sanguis::server::entities::with_ghosts::add_ghost(
		auras_.back()->create_ghost()
	);
}

sanguis::server::entities::with_auras::with_auras(
	sanguis::server::auras::create_callback_container const &_auras
)
:
	sanguis::server::entities::with_ghosts(),
	auras_()
{
	for(
		sanguis::server::auras::create_callback const &create_aura
		:
		_auras
	)
		this->add_aura(
			create_aura(
				this->diff_clock()
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
