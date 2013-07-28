#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/friend_type.hpp>
#include <sanguis/pickup_type.hpp>
#include <sanguis/projectile_type.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <sanguis/client/exp.hpp>
#include <sanguis/client/health.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/client/world_parameters.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/log.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/with_center.hpp>
#include <sanguis/client/draw2d/entities/with_health.hpp>
#include <sanguis/client/draw2d/entities/with_orientation.hpp>
#include <sanguis/client/draw2d/entities/with_speed.hpp>
#include <sanguis/client/draw2d/entities/with_weapon.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/factory/aoe_projectile.hpp>
#include <sanguis/client/draw2d/factory/enemy.hpp>
#include <sanguis/client/draw2d/factory/friend.hpp>
#include <sanguis/client/draw2d/factory/pickup.hpp>
#include <sanguis/client/draw2d/factory/projectile.hpp>
#include <sanguis/client/draw2d/factory/player.hpp>
#include <sanguis/client/draw2d/factory/own_player.hpp>
#include <sanguis/client/draw2d/factory/weapon_pickup.hpp>
#include <sanguis/client/draw2d/message/configure_entity.hpp>
#include <sanguis/client/draw2d/message/dispatcher.hpp>
#include <sanguis/client/draw2d/message/environment.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/translate/scalar_to_client.hpp>
#include <sanguis/client/draw2d/translate/vector_to_client.hpp>
#include <sanguis/messages/add_aoe_projectile.hpp>
#include <sanguis/messages/add_enemy.hpp>
#include <sanguis/messages/add_friend.hpp>
#include <sanguis/messages/add_own_player.hpp>
#include <sanguis/messages/add_pickup.hpp>
#include <sanguis/messages/add_player.hpp>
#include <sanguis/messages/add_projectile.hpp>
#include <sanguis/messages/add_weapon_pickup.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/change_weapon.hpp>
#include <sanguis/messages/change_world.hpp>
#include <sanguis/messages/die.hpp>
#include <sanguis/messages/experience.hpp>
#include <sanguis/messages/health.hpp>
#include <sanguis/messages/level.hpp>
#include <sanguis/messages/level_up.hpp>
#include <sanguis/messages/max_health.hpp>
#include <sanguis/messages/move.hpp>
#include <sanguis/messages/remove.hpp>
#include <sanguis/messages/role_name.hpp>
#include <sanguis/messages/rotate.hpp>
#include <sanguis/messages/start_attacking.hpp>
#include <sanguis/messages/stop_attacking.hpp>
#include <sanguis/messages/start_reloading.hpp>
#include <sanguis/messages/stop_reloading.hpp>
#include <sanguis/messages/seed.hpp>
#include <sanguis/messages/speed.hpp>
#include <sanguis/messages/world_id.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/aoe.hpp>
#include <sanguis/messages/roles/aoe_projectile.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/enemy.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/roles/experience.hpp>
#include <sanguis/messages/roles/friend.hpp>
#include <sanguis/messages/roles/health.hpp>
#include <sanguis/messages/roles/max_health.hpp>
#include <sanguis/messages/roles/opening_count.hpp>
#include <sanguis/messages/roles/projectile.hpp>
#include <sanguis/messages/roles/speed.hpp>
#include <sanguis/messages/roles/weapon.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <fcppt/cast_to_enum.hpp>
#include <fcppt/dynamic_cast.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/mpl/for_each.hpp>
#include <majutsu/is_role.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform_view.hpp>
#include <typeinfo>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::message::dispatcher::dispatcher(
	sanguis::client::draw2d::message::environment &_env
)
:
	env_(
		_env
	)
{
}

sanguis::client::draw2d::message::dispatcher::~dispatcher()
{
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::add_aoe_projectile const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::aoe_projectile(
			env_.model_parameters(),
			env_.insert_own_callback(),
			fcppt::cast_to_enum<
				sanguis::aoe_projectile_type
			>(
				_message.get<
					sanguis::messages::roles::aoe_projectile
				>()
			),
			sanguis::client::draw2d::aoe(
				sanguis::client::draw2d::translate::scalar_to_client(
					_message.get<
						sanguis::messages::roles::aoe
					>()
				)
			)
		),
		_message
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::add_enemy const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::enemy(
			env_.model_parameters(),
			fcppt::cast_to_enum<
				sanguis::enemy_type
			>(
				_message.get<
					sanguis::messages::roles::enemy
				>()
			)
		),
		_message
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::add_friend const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::friend_(
			env_.model_parameters(),
			fcppt::cast_to_enum<
				sanguis::friend_type
			>(
				_message.get<
					sanguis::messages::roles::friend_
				>()
			)
		),
		_message
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::add_own_player const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::own_player(
			env_.model_parameters(),
			env_.transform_callback(),
			env_.collide_callback()
		),
		_message
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::add_pickup const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::pickup(
			env_.model_parameters(),
			fcppt::cast_to_enum<
				sanguis::pickup_type
			>(
				_message.get<
					sanguis::messages::roles::pickup
				>()
			)
		),
		_message
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::add_player const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::player(
			env_.model_parameters()
		),
		_message
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::add_projectile const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::projectile(
			env_.model_parameters(),
			fcppt::cast_to_enum<
				sanguis::projectile_type
			>(
				_message.get<
					sanguis::messages::roles::projectile
				>()
			)
		),
		_message
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::add_weapon_pickup const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::weapon_pickup(
			env_.model_parameters(),
			fcppt::cast_to_enum<
				sanguis::weapon_type
			>(
				_message.get<
					sanguis::messages::roles::weapon
				>()
			)
		),
		_message
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::change_weapon const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::with_weapon &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).weapon(
		fcppt::cast_to_enum<
			sanguis::weapon_type
		>(
			_message.get<
				sanguis::messages::roles::weapon
			>()
		)
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::change_world const &_message
)
{
	env_.change_world(
		sanguis::client::world_parameters(
			_message.get<
				sanguis::messages::world_id
			>(),
			sanguis::creator::top_parameters(
				sanguis::creator::name(
					sge::charconv::utf8_string_to_fcppt(
						_message.get<
							sanguis::messages::roles::generator_name
						>()
					)
				),
				_message.get<
					sanguis::messages::seed
				>(),
				sanguis::creator::opening_count(
					_message.get<
						sanguis::messages::roles::opening_count
					>()
				)
			)
		)
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::die const &_message
)
{
	this->entity(
		_message.get<
			sanguis::messages::roles::entity_id
		>()
	).die();
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::experience const &_message
)
{
	env_.experience(
		sanguis::client::exp(
			_message.get<
				sanguis::messages::roles::experience
			>()
		)
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::health const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::with_health &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).health(
		sanguis::client::health(
			_message.get<
				sanguis::messages::roles::health
			>()
		)
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::level_up const &_message
)
{
	env_.level(
		sanguis::client::level(
			_message.get<
				sanguis::messages::level
			>()
		)
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::max_health const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::with_health &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).max_health(
		sanguis::client::max_health(
			_message.get<
				sanguis::messages::roles::max_health
			>()
		)
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::move const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::with_center &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).center(
		sanguis::client::draw2d::sprite::center(
			fcppt::math::vector::structure_cast<
				sanguis::client::draw2d::sprite::point
			>(
				sanguis::client::draw2d::translate::vector_to_client(
					_message.get<
						sanguis::messages::roles::center
					>()
				)
			)
		)
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::remove const &_message
)
{
	env_.remove(
		_message.get<
			sanguis::messages::roles::entity_id
		>()
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::rotate const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::with_orientation &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).orientation(
		_message.get<
			sanguis::messages::roles::angle
		>()
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::speed const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::with_speed &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).speed(
		sanguis::client::draw2d::speed(
			sanguis::client::draw2d::translate::vector_to_client(
				_message.get<
					sanguis::messages::roles::speed
				>()
			)
		)
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::start_attacking const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::with_weapon &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).attacking(
		true
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::stop_attacking const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::with_weapon &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).attacking(
		false
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::start_reloading const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::with_weapon &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).reloading(
		true
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::stop_reloading const &_message
)
{
	fcppt::dynamic_cast_<
		entities::with_weapon &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).reloading(
		false
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::process_default_msg(
	sanguis::messages::base const &_message
)
{
	FCPPT_LOG_WARNING(
		sanguis::client::draw2d::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Invalid message event in dispatcher: ")
			<< fcppt::type_name(
				typeid(
					_message
				)
			)
	);
}


template<
	typename Msg
>
void
sanguis::client::draw2d::message::dispatcher::configure_new_object(
	sanguis::client::draw2d::entities::unique_ptr &&_ptr,
	Msg const &_message
)
{
	sanguis::entity_id const id(
		_message. template get<
			sanguis::messages::roles::entity_id
		>()
	);

	env_.insert(
		std::move(
			_ptr
		),
		id
	);

	fcppt::mpl::for_each<
		boost::mpl::transform_view<
			boost::mpl::filter_view<
				typename Msg::memory_type::types,
				majutsu::is_role<
					boost::mpl::_1
				>
			>,
			sanguis::messages::role_name<
				boost::mpl::_1
			>
		>
	>(
		sanguis::client::draw2d::message::configure_entity<
			Msg
		>(
			*this,
			id,
			_message
		)
	);
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::message::dispatcher::entity(
	sanguis::entity_id const _id
)
{
	return
		env_.entity(
			_id
		);
}
