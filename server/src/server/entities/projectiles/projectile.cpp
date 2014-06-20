#include <sanguis/projectile_type.hpp>
#include <sanguis/collision/world/group.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/roles/projectile_type.hpp>
#include <sanguis/messages/roles/speed.hpp>
#include <sanguis/messages/server/add_projectile.hpp>
#include <sanguis/messages/server/create_ptr.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/model_name.hpp>
#include <sanguis/server/model_size.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/collision/result_fwd.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/movement_speed_initial.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/projectiles/collision_group.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/entities/projectiles/projectile.hpp>
#include <sanguis/server/entities/property/initial_max.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::projectiles::projectile::projectile(
	sanguis::projectile_type const _projectile_type,
	sanguis::server::team const _team,
	sanguis::server::entities::movement_speed const _movement_speed,
	sanguis::server::model_name const &_model_name,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::entities::projectiles::life_time const _life_time,
	sanguis::server::direction const _direction
)
:
	sanguis::server::entities::ifaces::with_team(),
	sanguis::server::entities::with_id(
		_load_context.next_id()
	),
	sanguis::server::entities::with_links(),
	sanguis::server::entities::with_velocity(
		_load_context.model_size(
			_model_name
		),
		sanguis::server::entities::movement_speed_initial(
			sanguis::server::entities::property::initial_max(
				_movement_speed.get()
			)
		),
		_direction
	),
	team_(
		_team
	),
	projectile_type_(
		_projectile_type
	),
	life_timer_(
		sanguis::diff_timer::parameters(
			this->diff_clock(),
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
sanguis::server::entities::projectiles::projectile::dead() const
{
	return life_timer_.expired();
}

void
sanguis::server::entities::projectiles::projectile::on_world_collision(
	sanguis::server::collision::result const &_result
)
{
	this->expire();

	sanguis::server::entities::with_body::on_world_collision(
		_result
	);
}

boost::logic::tribool const
sanguis::server::entities::projectiles::projectile::can_collide_with_body(
	sanguis::server::entities::with_body const &_other
) const
{
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

sanguis::collision::world::group
sanguis::server::entities::projectiles::projectile::collision_group() const
{
	return
		sanguis::server::entities::projectiles::collision_group(
			this->team()
		);
}

sanguis::messages::server::unique_ptr
sanguis::server::entities::projectiles::projectile::add_message(
	sanguis::server::player_id const
) const
{
	return
		sanguis::messages::server::create_ptr(
			sanguis::messages::server::add_projectile(
				sanguis::messages::roles::entity_id{} =
					this->id(),
				sanguis::messages::roles::center{} =
					this->center().get(),
				sanguis::messages::roles::angle{} =
					this->angle().get(),
				sanguis::messages::roles::speed{} =
					this->speed().get(),
				sanguis::messages::roles::projectile_type{} =
					projectile_type_
			)
		);
}
