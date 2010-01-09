#include "dispatcher.hpp"
#include "environment.hpp"
#include "configure_entity.hpp"
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
#include "../log.hpp"
#include "../virtual_to_screen.hpp"
#include "../../../messages/role_name.hpp"
#include "../../../messages/base.hpp"
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
	environment &env_
)
:
	env_(env_)
{}

sanguis::client::draw2d::message::dispatcher::~dispatcher()
{
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::add_aoe_projectile const &m
)
{
	configure_new_object(
		factory::aoe_projectile(
			env_.model_parameters(),
			env_.particle_system(),
			env_.insert_callback(),
			SANGUIS_CAST_ENUM(
				aoe_projectile_type,
				m.get<sanguis::messages::roles::aoe_projectile>()
			),
			m.get<sanguis::messages::roles::aoe>()
		),
		m
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::add_enemy const &m
)
{
	configure_new_object(
		factory::enemy(
			env_.model_parameters(),
			SANGUIS_CAST_ENUM(
				enemy_type,
				m.get<sanguis::messages::roles::enemy>()
			)
		),
		m
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::add_friend const &m
)
{
	configure_new_object(
		factory::friend_(
			env_.model_parameters(),
			SANGUIS_CAST_ENUM(
				friend_type,
				m.get<sanguis::messages::roles::friend_>()
			)
		),
		m
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::add_pickup const &m
)
{
	configure_new_object(
		factory::pickup(
			env_.model_parameters(),
			SANGUIS_CAST_ENUM(
				pickup_type,
				m.get<sanguis::messages::roles::pickup>()
			)
		),
		m
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::add_player const &m
)
{
	configure_new_object(
		m.get<sanguis::messages::roles::entity_id>() == env_.own_player_id()
		?
			factory::own_player(
				env_.model_parameters(),
				env_.transform_callback()	
			)
		:
			factory::player(
				env_.model_parameters()
			),
		m
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::add_projectile const &m
)
{
	configure_new_object(
		factory::projectile(
			env_.model_parameters(),
			SANGUIS_CAST_ENUM(
				projectile_type,
				m.get<sanguis::messages::roles::projectile>()
			)
		),
		m
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::add_weapon_pickup const &m
)
{
	configure_new_object(
		factory::weapon_pickup(
			env_.model_parameters(),
			SANGUIS_CAST_ENUM(
				weapon_type,
				m.get<sanguis::messages::roles::weapon>()
			)
		),
		m
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::change_weapon const &m
)
{
	fcppt::dynamic_cast_<
		entities::with_weapon &
	>(
		entity(
			m.get<sanguis::messages::roles::entity_id>()
		)
	).weapon(
		SANGUIS_CAST_ENUM(
			weapon_type,
			m.get<sanguis::messages::roles::weapon>()
		)
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::experience const &m
)
{
	env_.experience(
		m.get<sanguis::messages::roles::experience>()
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::health const &m
)
{
	fcppt::dynamic_cast_<
		entities::with_health &
	>(
		entity(
			m.get<sanguis::messages::roles::entity_id>()
		)
	).health(
		m.get<sanguis::messages::roles::health>()
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::level_up const &m
)
{
	env_.level(
		m.get<sanguis::messages::level_type>()
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::max_health const &m
)
{
	fcppt::dynamic_cast_<
		entities::with_health &
	>(
		entity(
			m.get<sanguis::messages::roles::entity_id>()
		)
	).max_health(
		m.get<sanguis::messages::roles::max_health>()
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::move const &m
)
{
	entity(
		m.get<sanguis::messages::roles::entity_id>()
	).pos(
		virtual_to_screen(
			env_.screen_size(),
			m.get<sanguis::messages::pos>()
		)
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::remove const &m
)
{
	entity(
		m.get<sanguis::messages::roles::entity_id>()
	).decay();
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::resize const &m
)
{
	entity(
		m.get<sanguis::messages::roles::entity_id>()
	).dim(
		fcppt::math::dim::structure_cast<
			sprite::dim
		>(
			m.get<sanguis::messages::dim>()
		)
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::rotate const &m
)
{
	fcppt::dynamic_cast_<
		entities::with_orientation &
	>(
		entity(
			m.get<sanguis::messages::roles::entity_id>()
		)
	).orientation(
		m.get<sanguis::messages::roles::angle>()
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::speed const &m
)
{
	fcppt::dynamic_cast_<
		entities::with_speed &
	>(
		entity(
			m.get<sanguis::messages::roles::entity_id>()
		)
	).speed(
		fcppt::math::vector::structure_cast<
			vector2
		>(
			virtual_to_screen(
				env_.screen_size(),
				m.get<sanguis::messages::roles::speed>()
			)
		)
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::start_attacking const &m
)
{
	fcppt::dynamic_cast_<
		entities::with_weapon &
	>(
		entity(
			m.get<sanguis::messages::roles::entity_id>()
		)
	).attacking(
		true
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::stop_attacking const &m
)
{
	fcppt::dynamic_cast_<
		entities::with_weapon &
	>(
		entity(
			m.get<sanguis::messages::roles::entity_id>()
		)
	).attacking(
		false
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::start_reloading const &m
)
{
	fcppt::dynamic_cast_<
		entities::with_weapon &
	>(
		entity(
			m.get<sanguis::messages::roles::entity_id>()
		)
	).reloading(
		true
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::operator()(
	sanguis::messages::stop_reloading const &m
)
{
	fcppt::dynamic_cast_<
		entities::with_weapon &
	>(
		entity(
			m.get<sanguis::messages::roles::entity_id>()
		)
	).reloading(
		false
	);
}

sanguis::client::draw2d::message::dispatcher::result_type
sanguis::client::draw2d::message::dispatcher::process_default_msg(
	sanguis::messages::base const &m
)
{
	FCPPT_LOG_WARNING(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("Invalid message event in scene: ")
			<< fcppt::type_name(typeid(m))
	);
}


template<
	typename Msg
>
void
sanguis::client::draw2d::message::dispatcher::configure_new_object(
	entities::auto_ptr e_ptr,
	Msg const &m
)
{
	entity_id const id(
		m. template get<sanguis::messages::roles::entity_id>()
	);

	env_.insert(
		e_ptr,
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
			m
		)
	);
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::message::dispatcher::entity(
	entity_id const id
)
{
	return
		env_.entity(
			id
		);
}
