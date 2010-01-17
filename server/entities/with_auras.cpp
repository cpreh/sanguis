#include "with_auras.hpp"
#include "../auras/aura.hpp"
#include "../environment/object.hpp"
#include <fcppt/algorithm/append.hpp>
#include <boost/foreach.hpp>

void
sanguis::server::entities::with_auras::add_aura(
	auras::auto_ptr a
)
{
	auras_.push_back(a);

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
	time_type const
)
{}

sge::collision::shapes::container const
sanguis::server::entities::with_auras::recreate_shapes(
	sge::collision::world_ptr const world_,
	collision::global_groups const &global_groups_
)
{
	sge::collision::shapes::container ret(
		entities::base::recreate_shapes(
			world_,
			global_groups_
		)
	);

	BOOST_FOREACH(
		aura_container::reference aura_,
		auras_
	)
		fcppt::algorithm::append(
			ret,
			aura_.recreate_shapes(
				world_,
				global_groups_
			)
		);

	return ret;
}
