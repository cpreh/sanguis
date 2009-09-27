#include "with_auras.hpp"
#include "../auras/aura.hpp"
#include "../environment/object.hpp"
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

void
sanguis::server::entities::with_auras::on_transfer(
	collision::global_groups const &collision_groups_,
	collision::create_parameters const &create_param
)
{
	BOOST_FOREACH(
		aura_container::reference aura_,
		auras_
	)
		aura_.recreate(
			environment()->collision_world(),
			collision_groups_,
			create_param
		);
}

void
sanguis::server::entities::with_auras::on_center(
	pos_type const &center_
)
{
	BOOST_FOREACH(
		aura_container::reference r,
		auras_
	)
		r.center(
			center_
		);
}

void
sanguis::server::entities::with_auras::on_destroy()
{
	BOOST_FOREACH(
		aura_container::reference aura_,
		auras_
	)
		aura_.destroy();
}
