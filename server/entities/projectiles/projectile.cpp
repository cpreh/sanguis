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
#include <sge/assert.hpp>
#include <boost/logic/tribool.hpp>

sanguis::projectile_type::type
sanguis::server::entities::projectiles::projectile::ptype() const
{
	return ptype_;
}

sanguis::server::entities::projectiles::projectile::projectile(
	projectile_type::type const nptype,
	server::environment::load_context_ptr const load_context_,
	team::type const team_,
	property_map const &properties,
	dim_type const &dim,
	life_time const life_time_,
	indeterminate::type const indeterminate_
)
:
	entity(
		base_parameters(
			load_context_,
			damage::no_armor(),
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
	life_timer_(
		sge::time::second_f(
			life_time_
		),
		sge::time::activation_state::active,
		diff_clock_.callback()
	)
{}

void
sanguis::server::entities::projectiles::projectile::update(
	time_type const time
)
{
	entity::update(
		time
	);

	diff_clock_.update(time);

	if(life_timer_.expired())
		die();
}

boost::logic::tribool const
sanguis::server::entities::projectiles::projectile::can_collide_with_entity(
	entity const &e
) const
{
	SGE_ASSERT(e.team() != team()); // shouldn't happen for now!

	return
		!e.dead()
		&& !e.invulnerable();
}

void
sanguis::server::entities::projectiles::projectile::collision_entity_begin(
	entity &e
)
{
	if(!dead())
		do_damage(
			e
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
			health(),
			max_health(),
			dim(),
			ptype()
		)
	);
}
