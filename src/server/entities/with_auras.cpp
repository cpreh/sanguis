#include "with_auras.hpp"
#include "ghost_parameters.hpp"
#include "../auras/aura.hpp"
#include "../collision/ghost.hpp"
#include "../environment/object.hpp"
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <boost/foreach.hpp>

void
sanguis::server::entities::with_auras::add_aura(
	auras::unique_ptr _aura
)
{
	fcppt::container::ptr::push_back_unique_ptr(
		auras_,
		move(
			_aura
		)
	);

	auras::aura &ref(
		auras_.back()
	);

	ref.owner(
		this->id()
	);

	if(
		this->is_in_world()
	)
		with_ghosts::add_ghost(
			ref.recreate(
				this->environment().collision_world(),
				this->environment().global_collision_groups(),
				this->center()
			)
		);
}

sanguis::server::entities::with_auras::with_auras()
:
	base(),
	auras_()
{
}

sanguis::server::entities::with_auras::~with_auras()
{
}

void
sanguis::server::entities::with_auras::on_update(
	time_type
)
{
}

void
sanguis::server::entities::with_auras::recreate_ghosts(
	entities::ghost_parameters const &_params
)
{
	BOOST_FOREACH(
		aura_container::reference aura,
		auras_
	)
		with_ghosts::add_ghost(
			aura.recreate(
				_params.world(),
				_params.global_groups(),
				_params.center()
			)
		);
}
