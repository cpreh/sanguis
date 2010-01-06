#include "dispatcher.hpp"
#include "environment.hpp"
#include "configure_entity.hpp"

sanguis::client::draw2d::message::dispatcher::dispatcher(
	environment &env_
)
:
	env_(env_)
{}

sanguis::client::draw2d::message::dispatcher::~dispatcher()
{
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::add_aoe_projectile const &m
)
{
	configure_new_object(
		factory::aoe_projectile(
			environment(),
			m.get<messages::roles::entity_id>(),
			static_cast<
				aoe_projectile_type::type
			>(
				m.get<messages::roles::aoe_projectile>()
			),
			m.get<messages::roles::aoe>()
		),
		m
	);
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::add_enemy const &m
)
{
	configure_new_object(
		factory::enemy(
			environment(),
			m.get<messages::roles::entity_id>(),
			static_cast<
				enemy_type::type
			>(
				m.get<messages::roles::enemy>()
			)
		),
		m
	);
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::add_friend const &m
)
{
	configure_new_object(
		factory::friend_(
			environment(),
			m.get<messages::roles::entity_id>(),
			static_cast<
				friend_type::type
			>(
				m.get<messages::roles::friend_>()
			)
		),
		m
	);
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::add_pickup const &m
)
{
	configure_new_object(
		factory::pickup(
			environment(),
			m.get<messages::roles::entity_id>(),
			static_cast<
				pickup_type::type
			>(
				m.get<messages::roles::pickup>()
			)
		),
		m
	);
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::add_player const &m
)
{
	configure_new_object(
		factory::player(
			environment(),
			m.get<messages::roles::entity_id>()
		),
		m
	);
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::add_projectile const &m
)
{
	configure_new_object(
		factory::projectile(
			environment(),
			m.get<messages::roles::entity_id>(),
			static_cast<
				projectile_type::type
			>(
				m.get<messages::roles::projectile>()
			)
		),
		m
	);
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::add_weapon_pickup const &m
)
{
	configure_new_object(
		factory::weapon_pickup(
			environment(),
			m.get<messages::roles::entity_id>(),
			static_cast<
				weapon_type::type
			>(
				m.get<messages::roles::weapon>()
			)
		),
		m
	);
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::change_weapon const &m
)
{
	messages::types::enum_ const value(
		m.get<messages::roles::weapon>()
	);
	
	if(
		value >= static_cast<messages::types::enum_>(weapon_type::size)
	)
	{
		FCPPT_LOG_WARNING(
			log(),
			fcppt::log::_ << FCPPT_TEXT("Invalid change_weapon message: Value out of range!")
		);

		return;
	}
	
	entity(
		m.get<messages::roles::entity_id>()
	).weapon(
		static_cast<weapon_type::type>(
			value
		)
	);
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::experience const &m
)
{
	env_->experience(
		m.get<messages::roles::experience>()
	);
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::health const &m
)
{
	entity(
		m.get<messages::roles::entity_id>()
	).health(
		m.get<messages::roles::health>()
	);
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::level_up const &m
)
{
	env_->level(
		m.get<messages::level_type>()
	);
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::max_health const &m
)
{
	fcppt::dynamic_cast_<
		with_health &
	>(
		entity(
			m.get<messages::roles::entity_id>()
		)
	).max_health(
		m.get<messages::roles::max_health>()
	);
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::move const &m
)
{
	entity(
		m.get<messages::roles::entity_id>()
	).pos(
		virtual_to_screen(
			rend->screen_size(),
			m.get<messages::pos>()
		)
	);
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::remove const &m
)
{
	entity(
		m.get<messages::roles::entity_id>()
	).decay();
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::resize const &m
)
{
	entity(
		m.get<messages::roles::entity_id>()
	).dim(
		fcppt::math::dim::structure_cast<
			sprite::dim
		>(
			m.get<messages::dim>()
		)
	);
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::rotate const &m
)
{
	entity(
		m.get<messages::roles::entity_id>()
	).orientation(
		m.get<messages::roles::angle>()
	);
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::speed const &m
)
{
	entity(
		m.get<messages::roles::entity_id>()
	).speed(
		fcppt::math::vector::structure_cast<
			vector2
		>(
			virtual_to_screen(
				rend->screen_size(),
				m.get<messages::roles::speed>()
			)
		)
	);
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::start_attacking const &m
)
{
	entity(
		m.get<messages::roles::entity_id>()
	).start_attacking();
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::stop_attacking const &m
)
{
	entity(
		m.get<messages::roles::entity_id>()
	).stop_attacking();
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::start_reloading const &m
)
{
	entity(
		m.get<messages::roles::entity_id>()
	).start_reloading();
}

void
sanguis::client::draw2d::message::dispatcher::operator()(
	messages::stop_reloading const &m
)
{
	entity(
		m.get<messages::roles::entity_id>()
	).stop_reloading();
}

void
sanguis::client::draw2d::message::dispatcher::process_default_msg(
	messages::base const &m
)
{
	FCPPT_LOG_WARNING(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("Invalid message event in scene: ")
			<< fcppt::iconv(typeid(m).name())
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
		m.get<messages::roles::entity_id>()
	);

	entities::base &entity_(
		env_->insert(
			e_ptr,
			id
		)
	);

	boost::mpl::for_each<
		boost::mpl::transform_view<
			boost::mpl::filter_view<
				typename Msg::memory_type::types,
				majutsu::is_role<
					boost::mpl::_1
				>
			>,
			messages::role_name<
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
