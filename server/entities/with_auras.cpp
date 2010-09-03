#include "with_auras.hpp"
#include "../auras/aura.hpp"
#include "../environment/object.hpp"
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/algorithm/append.hpp>
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
		id()
	);

	if(
		is_in_world()
	)
		collision::body::add_shapes(
			ref.recreate_shapes(
				environment()->collision_world(),
				environment()->global_collision_groups()
			)
		);
}

sanguis::server::entities::with_auras::with_auras()
:
	base(),
	auras_()
{}

sanguis::server::entities::with_auras::~with_auras()
{}

void
sanguis::server::entities::with_auras::on_update(
	time_type
)
{}

sge::collision::shapes::container const
sanguis::server::entities::with_auras::recreate_shapes(
	sge::collision::world_ptr const _world,
	collision::global_groups const &_global_groups
)
{
	sge::collision::shapes::container ret(
		entities::base::recreate_shapes(
			_world,
			_global_groups
		)
	);

	BOOST_FOREACH(
		aura_container::reference aura,
		auras_
	)
		fcppt::algorithm::append(
			ret,
			aura.recreate_shapes(
				_world,
				_global_groups
			)
		);

	return ret;
}
