#include "dispatcher.hpp"
#include "environment.hpp"
#include "configure_entity.hpp"
#include "../entities/base.hpp"
#include "../entities/with_center.hpp"
#include "../entities/with_health.hpp"
#include "../entities/with_orientation.hpp"
#include "../entities/with_speed.hpp"
#include "../entities/with_weapon.hpp"
#include "../entities/model/parameters.hpp"
#include "../factory/aoe_projectile.hpp"
#include "../factory/enemy.hpp"
#include "../factory/friend.hpp"
#include "../factory/pickup.hpp"
#include "../factory/projectile.hpp"
#include "../factory/player.hpp"
#include "../factory/own_player.hpp"
#include "../factory/weapon_pickup.hpp"
#include "../sprite/center.hpp"
#include "../translate/scalar_to_client.hpp"
#include "../translate/vector_to_client.hpp"
#include "../aoe.hpp"
#include "../log.hpp"
#include "../speed.hpp"
#include "../vector2.hpp"
#include "../../../messages/base.hpp"
#include "../../../messages/role_name.hpp"
#include "../../../cast_enum.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/dynamic_cast.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/text.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform_view.hpp>
#include <majutsu/is_role.hpp>
#include <typeinfo>

sanguis::client::draw2d::message::dispatcher::dispatcher(
	environment &_env
)
:
	env_(_env)
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
		factory::aoe_projectile(
			env_.model_parameters(),
			env_.particle_system(),
			env_.insert_own_callback(),
			SANGUIS_CAST_ENUM(
				aoe_projectile_type,
				_message.get<sanguis::messages::roles::aoe_projectile>()
			),
			draw2d::aoe(
				draw2d::translate::scalar_to_client(
					_message.get<sanguis::messages::roles::aoe>()
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
		factory::enemy(
			env_.model_parameters(),
			SANGUIS_CAST_ENUM(
				enemy_type,
				_message.get<sanguis::messages::roles::enemy>()
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
		factory::friend_(
			env_.model_parameters(),
			SANGUIS_CAST_ENUM(
				friend_type,
				_message.get<sanguis::messages::roles::friend_>()
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
		factory::own_player(
			env_.model_parameters(),
			env_.transform_callback()	
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
		factory::pickup(
			env_.model_parameters(),
			SANGUIS_CAST_ENUM(
				pickup_type,
				_message.get<sanguis::messages::roles::pickup>()
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
		factory::player(
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
		factory::projectile(
			env_.model_parameters(),
			SANGUIS_CAST_ENUM(
				projectile_type,
				_message.get<sanguis::messages::roles::projectile>()
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
		factory::weapon_pickup(
			env_.model_parameters(),
			SANGUIS_CAST_ENUM(
				weapon_type,
				_message.get<sanguis::messages::roles::weapon>()
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
		entities::with_weapon &
	>(
		this->entity(
			_message.get<sanguis::messages::roles::entity_id>()
		)
	).weapon(
		SANGUIS_CAST_ENUM(
			weapon_type,
			_message.get<sanguis::messages::roles::weapon>()
		)
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::die const &_message
)
{
	this->entity(
		_message.get<sanguis::messages::roles::entity_id>()
	).decay();
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::experience const &_message
)
{
	env_.experience(
		client::exp(
			_message.get<sanguis::messages::roles::experience>()
		)
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::health const &_message
)
{
	fcppt::dynamic_cast_<
		entities::with_health &
	>(
		this->entity(
			_message.get<sanguis::messages::roles::entity_id>()
		)
	).health(
		client::health(
			_message.get<sanguis::messages::roles::health>()
		)
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::level_up const &_message
)
{
	env_.level(
		client::level(
			_message.get<sanguis::messages::level>()
		)
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::max_health const &_message
)
{
	fcppt::dynamic_cast_<
		entities::with_health &
	>(
		this->entity(
			_message.get<sanguis::messages::roles::entity_id>()
		)
	).max_health(
		client::health(
			_message.get<sanguis::messages::roles::max_health>()
		)
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::move const &_message
)
{
	fcppt::dynamic_cast_<
		entities::with_center &
	>(
		this->entity(
			_message.get<sanguis::messages::roles::entity_id>()
		)
	).center(
		draw2d::sprite::center(
			fcppt::math::vector::structure_cast<
				draw2d::sprite::point
			>(
				draw2d::translate::vector_to_client(
					_message.get<sanguis::messages::roles::center>()
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
		_message.get<sanguis::messages::roles::entity_id>()
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::rotate const &_message
)
{
	fcppt::dynamic_cast_<
		entities::with_orientation &
	>(
		this->entity(
			_message.get<sanguis::messages::roles::entity_id>()
		)
	).orientation(
		_message.get<sanguis::messages::roles::angle>()
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::speed const &_message
)
{
	fcppt::dynamic_cast_<
		entities::with_speed &
	>(
		this->entity(
			_message.get<sanguis::messages::roles::entity_id>()
		)
	).speed(
		draw2d::speed(
			draw2d::translate::vector_to_client(
				_message.get<sanguis::messages::roles::speed>()
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
		entities::with_weapon &
	>(
		this->entity(
			_message.get<sanguis::messages::roles::entity_id>()
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
		entities::with_weapon &
	>(
		this->entity(
			_message.get<sanguis::messages::roles::entity_id>()
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
		entities::with_weapon &
	>(
		this->entity(
			_message.get<sanguis::messages::roles::entity_id>()
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
			_message.get<sanguis::messages::roles::entity_id>()
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
		draw2d::log(),
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
	entities::unique_ptr _ptr,
	Msg const &_message
)
{
	sanguis::entity_id const id(
		_message. template get<sanguis::messages::roles::entity_id>()
	);

	env_.insert(
		move(
			_ptr
		),
		id
	);

	boost::mpl::for_each<
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
		configure_entity<
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
