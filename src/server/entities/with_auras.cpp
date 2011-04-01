#include "with_auras.hpp"
#include "../auras/aura.hpp"
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
			_ptr
		)
	);

	auras::aura &ref(
		auras_.back()
	);

	ref.owner(
		this->id()
	);

	// FIXME!
#if 0
	if(
		this->is_in_world()
	)
		collision::body::add_shapes(
			this->recreate_ghosts(
				
			ref.recreate_shapes(
				environment()->collision_world(),
				environment()->global_collision_groups()
			)
		);
#endif
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
	collision::ghost_parameters const &_params
)
{
	BOOST_FOREACH(
		aura_container::reference aura,
		auras_
	)
		with_ghosts::add_ghost(
			aura->recreate(
				_params,
				this->center()
			)
		);

	return ret;
}
