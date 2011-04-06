#include "projectile.hpp"
#include "../property/initial_max.hpp"
#include "../nonsolid.hpp"
#include "../with_health.hpp"
#include "../../damage/no_armor.hpp"
#include "../../damage/list.hpp"
#include "../../../messages/add_projectile.hpp"
#include "../../../messages/create.hpp"
#include <sge/time/second_f.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert.hpp>
#include <boost/logic/tribool.hpp>

sanguis::projectile_type::type
sanguis::server::entities::projectiles::projectile::ptype() const
{
	return ptype_;
}

sanguis::server::entities::projectiles::projectile::projectile(
	projectile_type::type const _ptype,
	server::team::type const _team,
	entities::movement_speed const _movement_speed,
	server::dim const &_dim,
	life_time const _life_time,
	server::direction const _direction,
	indeterminate::type const _indeterminate
)
:
	base(),
	movable(
		property::initial_max(
			_movement_speed.get()
		),
		_direction
	),
	with_dim(
		entities::nonsolid(),
		_dim
	),
	team_(_team),
	server_only_(
		_indeterminate == indeterminate::yes
	),
	ptype_(_ptype),
	diff_clock_(),
	life_timer_(
		sge::time::second_f(
			_life_time.get()
		),
		sge::time::activation_state::active,
		diff_clock_.callback()
	)
{
}

sanguis::server::entities::projectiles::projectile::~projectile()
{
}

void
sanguis::server::entities::projectiles::projectile::on_update(
	time_type const _time
)
{
	diff_clock_.update(
		_time
	);
}

void
sanguis::server::entities::projectiles::projectile::expire()
{
	life_timer_.expire();
}

sanguis::server::team::type
sanguis::server::entities::projectiles::projectile::team() const
{
	return team_;
}

bool
sanguis::server::entities::projectiles::projectile::server_only() const
{
	return server_only_;	
}

bool
sanguis::server::entities::projectiles::projectile::dead() const
{
	return life_timer_.expired();
}

sanguis::entity_type::type
sanguis::server::entities::projectiles::projectile::type() const
{
	return entity_type::projectile;
}

boost::logic::tribool const
sanguis::server::entities::projectiles::projectile::can_collide_with_body(
	entities::with_body const &_other
) const
{
	FCPPT_ASSERT(
		_other.team() != this->team()
	); // shouldn't happen for now!

	return
		!_other.dead()
		&&
		dynamic_cast<
			entities::with_health const *
		>(
			&_other
		);
}

void
sanguis::server::entities::projectiles::projectile::collision_with_body(
	entities::with_body &_other
)
{
	if(
		!this->dead()
	)
		this->do_damage(
			dynamic_cast<
				with_health &
			>(
				_other
			)
		);
}

sanguis::messages::auto_ptr
sanguis::server::entities::projectiles::projectile::add_message(
	player_id const
) const
{
	return
		messages::create(
			messages::add_projectile(
				this->id(),
				this->pos().get(),
				this->angle().get(),
				this->dim(),
				this->abs_speed().get(),
				this->ptype()
			)
		);
}
