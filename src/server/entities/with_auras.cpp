#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/unique_ptr.hpp>
#include <sanguis/server/collision/ghost.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


void
sanguis::server::entities::with_auras::add_aura(
	sanguis::server::auras::unique_ptr &&_aura
)
{
	fcppt::container::ptr::push_back_unique_ptr(
		auras_,
		std::move(
			_aura
		)
	);

	sanguis::server::auras::aura &ref(
		auras_.back()
	);

	sanguis::server::entities::with_ghosts::add_ghost(
		ref.recreate()
	);
}

sanguis::server::entities::with_auras::with_auras()
:
	sanguis::server::entities::with_ghosts(),
	auras_()
{
}

sanguis::server::entities::with_auras::~with_auras()
{
}
