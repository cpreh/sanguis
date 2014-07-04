#include <sanguis/entity_id.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <sanguis/client/health.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/client/weapon_description_from_message.hpp>
#include <sanguis/client/world_parameters.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/log.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/hover/name.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_auras.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_buffs.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_center.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_health.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_orientation.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_speed.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_weapon.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters.hpp>
#include <sanguis/client/draw2d/factory/aoe_projectile.hpp>
#include <sanguis/client/draw2d/factory/destructible.hpp>
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
#include <sanguis/client/draw2d/message/health_pair.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/translate/scalar_to_client.hpp>
#include <sanguis/client/draw2d/translate/vector_to_client.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/aoe.hpp>
#include <sanguis/messages/roles/aura_type.hpp>
#include <sanguis/messages/roles/aura_type_container.hpp>
#include <sanguis/messages/roles/aoe_projectile_type.hpp>
#include <sanguis/messages/roles/buff_type.hpp>
#include <sanguis/messages/roles/buff_type_container.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/destructible_type.hpp>
#include <sanguis/messages/roles/enemy_type.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/roles/friend_type.hpp>
#include <sanguis/messages/roles/health.hpp>
#include <sanguis/messages/roles/max_health.hpp>
#include <sanguis/messages/roles/name.hpp>
#include <sanguis/messages/roles/opening_count.hpp>
#include <sanguis/messages/roles/pickup_type.hpp>
#include <sanguis/messages/roles/primary_weapon.hpp>
#include <sanguis/messages/roles/projectile_type.hpp>
#include <sanguis/messages/roles/seed.hpp>
#include <sanguis/messages/roles/speed.hpp>
#include <sanguis/messages/roles/weapon_status.hpp>
#include <sanguis/messages/roles/world_id.hpp>
#include <sanguis/messages/server/add_aoe_projectile.hpp>
#include <sanguis/messages/server/add_aura.hpp>
#include <sanguis/messages/server/add_buff.hpp>
#include <sanguis/messages/server/add_destructible.hpp>
#include <sanguis/messages/server/add_enemy.hpp>
#include <sanguis/messages/server/add_friend.hpp>
#include <sanguis/messages/server/add_own_player.hpp>
#include <sanguis/messages/server/add_pickup.hpp>
#include <sanguis/messages/server/add_player.hpp>
#include <sanguis/messages/server/add_projectile.hpp>
#include <sanguis/messages/server/add_weapon_pickup.hpp>
#include <sanguis/messages/server/base.hpp>
#include <sanguis/messages/server/change_weapon.hpp>
#include <sanguis/messages/server/change_world.hpp>
#include <sanguis/messages/server/die.hpp>
#include <sanguis/messages/server/health.hpp>
#include <sanguis/messages/server/max_health.hpp>
#include <sanguis/messages/server/move.hpp>
#include <sanguis/messages/server/remove.hpp>
#include <sanguis/messages/server/remove_buff.hpp>
#include <sanguis/messages/server/rotate.hpp>
#include <sanguis/messages/server/speed.hpp>
#include <sanguis/messages/server/weapon_status.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <alda/serialization/load/optional.hpp>
#include <alda/serialization/load/static_size.hpp>
#include <majutsu/unwrap_role.hpp>
#include <fcppt/dynamic_cast.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
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
	sanguis::messages::server::add_aoe_projectile const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::aoe_projectile(
			env_.model_parameters(),
			env_.insert_own_callback(),
			_message.get<
				sanguis::messages::roles::aoe_projectile_type
			>(),
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
	sanguis::messages::server::add_aura const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::ifaces::with_auras &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).add_aura(
		_message.get<
			sanguis::messages::roles::aura_type
		>()
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::server::add_buff const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::ifaces::with_buffs &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).add_buff(
		_message.get<
			sanguis::messages::roles::buff_type
		>()
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::server::add_destructible const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::destructible(
			env_.model_parameters(),
			_message.get<
				sanguis::messages::roles::destructible_type
			>()
		),
		_message
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::server::add_enemy const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::enemy(
			env_.model_parameters(),
			env_.aura_resources(),
			_message.get<
				sanguis::messages::roles::enemy_type
			>(),
			_message.get<
				sanguis::messages::roles::aura_type_container
			>(),
			_message.get<
				sanguis::messages::roles::buff_type_container
			>(),
			sanguis::client::draw2d::entities::hover::name(
				sge::charconv::utf8_string_to_fcppt(
					_message.get<
						sanguis::messages::roles::name
					>()
				)
			),
			sanguis::client::draw2d::message::health_pair(
				_message
			)
		),
		_message
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::server::add_friend const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::friend_(
			env_.model_parameters(),
			env_.aura_resources(),
			_message.get<
				sanguis::messages::roles::friend_type
			>(),
			_message.get<
				sanguis::messages::roles::aura_type_container
			>(),
			_message.get<
				sanguis::messages::roles::buff_type_container
			>(),
			sanguis::client::draw2d::message::health_pair(
				_message
			)
		),
		_message
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::server::add_own_player const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::own_player(
			env_.aura_resources(),
			env_.model_parameters(),
			env_.player_center_callback(),
			env_.collide_callback(),
			env_.player_health_callback(),
			_message.get<
				sanguis::messages::roles::aura_type_container
			>(),
			_message.get<
				sanguis::messages::roles::buff_type_container
			>(),
			sanguis::client::draw2d::message::health_pair(
				_message
			)
		),
		_message
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::server::add_pickup const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::pickup(
			env_.model_parameters(),
			_message.get<
				sanguis::messages::roles::pickup_type
			>()
		),
		_message
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::server::add_player const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::player(
			env_.aura_resources(),
			env_.model_parameters(),
			_message.get<
				sanguis::messages::roles::aura_type_container
			>(),
			_message.get<
				sanguis::messages::roles::buff_type_container
			>(),
			sanguis::client::draw2d::message::health_pair(
				_message
			),
			sanguis::client::draw2d::entities::hover::name(
				sge::charconv::utf8_string_to_fcppt(
					_message.get<
						sanguis::messages::roles::name
					>()
				)
			)
		),
		_message
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::server::add_projectile const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::projectile(
			env_.model_parameters(),
			_message.get<
				sanguis::messages::roles::projectile_type
			>()
		),
		_message
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::server::add_weapon_pickup const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::weapon_pickup(
			env_.model_parameters(),
			sanguis::client::weapon_description_from_message(
				_message
			)
		),
		_message
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::server::change_weapon const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::ifaces::with_weapon &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).weapon(
		_message.get<
			sanguis::messages::roles::primary_weapon
		>()
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::server::change_world const &_message
)
{
	env_.change_world(
		sanguis::client::world_parameters(
			_message.get<
				sanguis::messages::roles::world_id
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
					sanguis::messages::roles::seed
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
	sanguis::messages::server::die const &_message
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
	sanguis::messages::server::health const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::ifaces::with_health &
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
	sanguis::messages::server::max_health const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::ifaces::with_health &
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
	sanguis::messages::server::move const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::ifaces::with_center &
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
	sanguis::messages::server::remove const &_message
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
	sanguis::messages::server::remove_buff const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::ifaces::with_buffs &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).remove_buff(
		_message.get<
			sanguis::messages::roles::buff_type
		>()
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::server::rotate const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::ifaces::with_orientation &
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
	sanguis::messages::server::speed const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::ifaces::with_speed &
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
	sanguis::messages::server::weapon_status const &_message
)
{
	fcppt::dynamic_cast_<
		sanguis::client::draw2d::entities::ifaces::with_weapon &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).weapon_status(
		_message.get<
			sanguis::messages::roles::weapon_status
		>()
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::process_default_msg(
	sanguis::messages::server::base const &_message
)
{
	FCPPT_LOG_WARNING(
		sanguis::client::draw2d::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Invalid message event in dispatcher: ")
			<< fcppt::type_name_from_info(
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
			majutsu::unwrap_role<
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
