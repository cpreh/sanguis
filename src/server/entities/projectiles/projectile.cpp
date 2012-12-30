#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/entity_type.hpp>
#include <sanguis/projectile_type.hpp>
#include <sanguis/messages/add_projectile.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/types/enum.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/dim_fwd.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/body_velocity_combiner.hpp>
#include <sanguis/server/entities/circle_from_dim.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/nonsolid.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/projectiles/indeterminate.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/entities/projectiles/projectile.hpp>
#include <sanguis/server/entities/property/initial_max.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::projectile_type
sanguis::server::entities::projectiles::projectile::ptype() const
{
	return ptype_;
}

sanguis::server::entities::projectiles::projectile::projectile(
	sanguis::diff_clock const &_diff_clock,
	sanguis::projectile_type const _ptype,
	sanguis::server::team const _team,
	sanguis::server::entities::movement_speed const _movement_speed,
	sanguis::server::dim const &_dim,
	sanguis::server::entities::projectiles::life_time const _life_time,
	sanguis::server::direction const _direction,
	sanguis::server::entities::projectiles::indeterminate const _indeterminate
)
:
	sanguis::server::entities::base(),
	sanguis::server::entities::body_velocity_combiner(),
	sanguis::server::entities::with_body(
		sanguis::server::entities::circle_from_dim(
			_dim,
			sanguis::server::entities::nonsolid()
		)
	),
	sanguis::server::entities::with_velocity(
		sanguis::server::entities::property::initial_max(
			_movement_speed.get()
		),
		_direction
	),
	team_(
		_team
	),
	server_only_(
		_indeterminate
		==
		sanguis::server::entities::projectiles::indeterminate::yes
	),
	ptype_(
		_ptype
	),
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

sanguis::server::team
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

sanguis::entity_type
sanguis::server::entities::projectiles::projectile::type() const
{
	return sanguis::entity_type::projectile;
}

boost::logic::tribool const
sanguis::server::entities::projectiles::projectile::can_collide_with_body(
	sanguis::server::entities::with_body const &_other
) const
{
	FCPPT_ASSERT_PRE(
		_other.team() != this->team()
	); // shouldn't happen for now!

	return
		!_other.dead()
		&&
		dynamic_cast<
			sanguis::server::entities::with_health const *
		>(
			&_other
		);
}

void
sanguis::server::entities::projectiles::projectile::collision_with_body(
	sanguis::server::entities::with_body &_other
)
{
	if(
		!this->dead()
	)
		this->do_damage(
			dynamic_cast<
				sanguis::server::entities::with_health &
			>(
				_other
			)
		);
}

sanguis::messages::auto_ptr
sanguis::server::entities::projectiles::projectile::add_message(
	sanguis::server::player_id const
) const
{
	FCPPT_ASSERT_PRE(
		!this->server_only()
	);

	return
		sanguis::messages::create(
			sanguis::messages::add_projectile(
				this->id(),
				this->center().get(),
				this->angle().get(),
				this->speed().get(),
				static_cast<
					sanguis::messages::types::enum_
				>(
					this->ptype()
				)
			)
		);
}
