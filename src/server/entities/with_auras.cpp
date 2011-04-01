#include "with_auras.hpp"
#include "../auras/aura.hpp"
#include "../environment/object.hpp"
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <boost/foreach.hpp>

void
sanguis::server::entities::with_auras::add_aura(
	auras::unique_ptr _ptr
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

sanguis::server::collision::ghost_reference_vector const
sanguis::server::entities::with_auras::recreate_ghosts(
	collision::ghost_parameters const &_params
)
{
	sanguis::server::collision::ghost_reference_vector ret;

	BOOST_FOREACH(
		aura_container::reference aura,
		auras_
	)
		ret.push_back(
			fcppt::ref(
				aura->recreate(
					_params
				)
			)
		);

	return ret;
}
