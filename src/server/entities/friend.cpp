#include <sanguis/server/entities/friend.hpp>
#include <sanguis/server/entities/circle_from_dim.hpp>
#include <sanguis/server/entities/default_solid.hpp>
#include <sanguis/server/entities/pickups/pickup.hpp>
#include <sanguis/server/entities/property/initial.hpp>
#include <sanguis/server/ai/base.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/load/friend_name.hpp>
#include <sanguis/messages/add_friend.hpp>
#include <sanguis/messages/create.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::server::entities::friend_::friend_(
	sanguis::diff_clock const &_diff_clock,
	friend_type::type const _ftype,
	server::environment::load_context &_load_context,
	damage::armor const &_armor,
	server::health const _health,
	entities::movement_speed const _movement_speed,
	ai::create_function const &_ai,
	weapons::unique_ptr _weapon
)
:
	with_ai(
		_diff_clock,
		_ai,
		move(
			_weapon
		)
	),
	with_body(
		entities::circle_from_dim(
			_load_context.entity_dim(
				load::friend_name(
					_ftype
				)
			),
			entities::default_solid()
		)
	),
	with_buffs(),
	with_health(
		_diff_clock,
		_health,
		_armor
	),
	with_velocity(
		property::initial(
			_movement_speed.get(),
			0
		),
		server::direction(
			0
		)
	),
	ftype_(_ftype)
{
}

void
sanguis::server::entities::friend_::on_update()
{
	with_ai::on_update();

	with_buffs::on_update();

	with_health::on_update();
}

sanguis::entity_type::type
sanguis::server::entities::friend_::type() const
{
	return entity_type::friend_;
}

sanguis::server::team::type
sanguis::server::entities::friend_::team() const
{
	return server::team::players;
}

sanguis::messages::auto_ptr
sanguis::server::entities::friend_::add_message(
	server::player_id const
) const
{
	return
		messages::create(
			messages::add_friend(
				this->id(),
				this->center().get(),
				this->angle().get(),
				this->abs_speed().get(),
				this->current_health().get(),
				this->max_health().get(),
				ftype_
			)
		);
}
