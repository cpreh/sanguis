#include "projectile.hpp"
#include "../property/initial_max.hpp"
#include "../nonsolid.hpp"
#include "../circle_from_dim.hpp"
#include "../with_health.hpp"
#include "../../damage/no_armor.hpp"
#include "../../damage/list.hpp"
#include "../../../messages/add_projectile.hpp"
#include "../../../messages/create.hpp"
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
	sanguis::diff_clock const &_diff_clock,
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
	with_body(
		entities::circle_from_dim(
			_dim,
			entities::nonsolid()
		)
	),
	with_velocity(
		property::initial_max(
			_movement_speed.get()
		),
		_direction
	),
	team_(_team),
	server_only_(
		_indeterminate == indeterminate::yes
	),
	ptype_(_ptype),
	life_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			_life_time.get()
		)
	)
{
}

sanguis::server::entities::projectiles::projectile::~projectile()
{
}

void
sanguis::server::entities::projectiles::projectile::expire()
{
	life_timer_.expired(
		true
	);
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
	FCPPT_ASSERT(
		!this->server_only()
	);

	return
		messages::create(
			messages::add_projectile(
				this->id(),
				this->center().get(),
				this->angle().get(),
				this->abs_speed().get(),
				this->ptype()
			)
		);
}
