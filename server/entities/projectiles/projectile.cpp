#include "projectile.hpp"
#include "../base_parameters.hpp"
#include "../../damage/no_armor.hpp"
#include "../../damage/list.hpp"
#include "../../../messages/add_projectile.hpp"
#include "../../../messages/create.hpp"
#include <sge/time/second_f.hpp>
#include <sge/time/resolution.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/optional_impl.hpp>
#include <boost/logic/tribool.hpp>

sanguis::projectile_type::type
sanguis::server::entities::projectiles::projectile::ptype() const
{
	return ptype_;
}

sanguis::server::entities::projectiles::projectile::projectile(
	projectile_type::type const nptype,
	server::environment const &env,
	pos_type const &center,
	space_unit const angle,
	team::type const team_,
	property_map const &properties,
	dim_type const &dim,
	optional_life_time const &lifetime,
	indeterminate::type const indeterminate_)
:
	entity(
		base_parameters(
			env,
			damage::no_armor(),
			center,
			angle,
			angle,
			team_,
			properties,
			indeterminate_ == indeterminate::yes
				? entity_type::indeterminate
				: entity_type::projectile,
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

boost::logic::tribool const
sanguis::server::entities::projectiles::projectile::can_collide_with_entity(
	entity const &e) const
{
	return e.team() != team()
		&& !e.dead()
		&& !e.invulnerable();
}

void
sanguis::server::entities::projectiles::projectile::collision_entity(
	entity &e)
{
	if(!dead())
		do_damage(
			e
		);
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
