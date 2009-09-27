#include "projectile.hpp"
#include "../with_health.hpp"
#include "../../damage/no_armor.hpp"
#include "../../damage/list.hpp"
#include "../../health_type.hpp"
#include "../../../messages/add_projectile.hpp"
#include "../../../messages/create.hpp"
#include <sge/time/second_f.hpp>
#include <sge/time/resolution.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/optional_impl.hpp>
#include <sge/assert.hpp>
#include <boost/logic/tribool.hpp>

sanguis::projectile_type::type
sanguis::server::entities::projectiles::projectile::ptype() const
{
	return ptype_;
}

sanguis::server::entities::projectiles::projectile::projectile(
	projectile_type::type const ptype_,
	team::type const team_,
	server::movement_speed const movement_speed_,
	dim_type const &dim_,
	life_time const life_time_,
	space_unit const direction_,
	indeterminate::type const indeterminate_
)
:
	base(),
	movable(
		movement_speed_,
		direction_
	),
	with_dim(
		dim_
	),
	team_(team_),
	type_(
		indeterminate_ == indeterminate::yes
		?
			entity_type::indeterminate
		:
			entity_type::projectile
	),
	ptype_(ptype_),
	diff_clock_(),
	life_timer_(
		sge::time::second_f(
			life_time_
		),
		sge::time::activation_state::active,
		diff_clock_.callback()
	)
{}

void
sanguis::server::entities::projectiles::projectile::on_update(
	time_type const time
)
{
	diff_clock_.update(
		time
	);
}

void
sanguis::server::entities::projectiles::projectile::die()
{
	life_timer_.expire();

	on_die();
}

sanguis::server::team::type
sanguis::server::entities::projectiles::projectile::team() const
{
	return team_;
}

void
sanguis::server::entities::projectiles::projectile::on_die()
{}

bool
sanguis::server::entities::projectiles::projectile::dead() const
{
	return life_timer_.expired();
}

bool
sanguis::server::entities::projectiles::projectile::invulnerable() const
{
	return true;
}

sanguis::entity_type::type
sanguis::server::entities::projectiles::projectile::type() const
{
	return type_;
}

boost::logic::tribool const
sanguis::server::entities::projectiles::projectile::can_collide_with_entity(
	base const &e
) const
{
	SGE_ASSERT(e.team() != team()); // shouldn't happen for now!

	return
		!e.dead()
		&& !e.invulnerable();
}

void
sanguis::server::entities::projectiles::projectile::collision_entity_begin(
	base &entity_
)
{
	if(
		!dead()
	)
		do_damage(
			dynamic_cast<
				with_health &
			>(
				entity_	
			)
		);
}

sanguis::messages::auto_ptr
sanguis::server::entities::projectiles::projectile::add_message() const
{
	return messages::create(
		messages::add_projectile(
			id(),
			pos(),
			angle(),
			abs_speed(),
			health_type(0), // health
			health_type(0), // max health
			dim(),
			ptype()
		)
	);
}
