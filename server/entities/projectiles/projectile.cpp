#include "projectile.hpp"
#include "../base_parameters.hpp"
#include "../../damage_types.hpp"
#include "../../../exception.hpp"
#include "../../../messages/add_projectile.hpp"
#include "../../../messages/create.hpp"
#include <sge/time/second_f.hpp>
#include <sge/time/resolution.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/text.hpp>

namespace
{

sanguis::entity_type::type
to_entity_type(
	sanguis::projectile_type::type);

}

sanguis::projectile_type::type
sanguis::server::entities::projectiles::projectile::ptype() const
{
	return ptype_;
}

sanguis::server::entities::projectiles::projectile::projectile(
	projectile_type::type const nptype,
	server::environment const &env,
	pos_type const& center,
	space_unit const angle,
	team::type const team_,
	property_map const &properties,
	dim_type const &dim,
	optional_life_time const &lifetime)
:
	entity(
		base_parameters(
			env,
			damage::list(
				static_cast<space_unit>(0)),
			center,
			angle,
			angle,
			team_,
			properties,
			to_entity_type(nptype),
			true,
			dim
		)
	),
	ptype_(nptype),
	diff_clock_(),
	lifetime(
		sge::time::second_f(
			lifetime
				? *lifetime
				: 0.f
		),
		lifetime
			? sge::time::activation_state::active
			: sge::time::activation_state::inactive,
		diff_clock_.callback()
	)
{}

void sanguis::server::entities::projectiles::projectile::die()
{
	entity::die();
	do_die();
}

void sanguis::server::entities::projectiles::projectile::update(
	time_type const time,
	container &entities)
{
	entity::update(
		time,
		entities
	);

	diff_clock_.update(time);

	if(lifetime.expired())
		die();
}

bool sanguis::server::entities::projectiles::projectile::can_collide_with_entity(
	entity const &e) const
{
	return e.team() != team()
		&& !e.dead()
		&& !e.invulnerable();
}

void sanguis::server::entities::projectiles::projectile::do_die()
{}

sanguis::messages::auto_ptr
sanguis::server::entities::projectiles::projectile::add_message() const
{
	return messages::create(
		messages::add_projectile(
			id(),
			pos(),
			angle(),
			abs_speed(),
			health(),
			max_health(),
			dim(),
			ptype()
		)
	);
}

namespace
{

sanguis::entity_type::type
to_entity_type(
	sanguis::projectile_type::type const p)
{
	// TODO: maybe this is not the best way to do this
	switch(p) {
	case sanguis::projectile_type::rocket:
	case sanguis::projectile_type::simple_bullet:
		return sanguis::entity_type::projectile;
	case sanguis::projectile_type::aoe_damage:
	case sanguis::projectile_type::melee:
		return sanguis::entity_type::indeterminate;
	default:
		throw sanguis::exception(
			SGE_TEXT("Invalid projectile type in to_entity_type()!"));
	}
}

}


