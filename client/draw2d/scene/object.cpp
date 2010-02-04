#include "object.hpp"
#include "message_environment.hpp"
#include "control_environment.hpp"
#include "screen_center.hpp"
#include "../message/dispatcher.hpp"
#include "../factory/client.hpp"
#include "../sprite/order.hpp"
#include "../sprite/matrix.hpp"
#include "../entities/with_visibility.hpp"
#include "../z_ordering.hpp"
#include "../vector2.hpp"
#include "../../invalid_id.hpp"
#include "../../next_id.hpp"
#include "../../log.hpp"
#include "../../messages/add.hpp"
#include "../../messages/visible.hpp"
#include "../../../messages/call/object.hpp"
#include "../../../messages/role_name.hpp"
#include "../../../exception.hpp"
#include "../../../load/context.hpp"

#include <sge/renderer/device.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/sprite/default_equal.hpp>
#include <sge/sprite/intrusive/system_impl.hpp>
#include <sge/sprite/object_impl.hpp>

#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/dynamic_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/format.hpp>
#include <fcppt/exception.hpp>

#include <boost/foreach.hpp>

#include <utility>

sanguis::client::draw2d::scene::object::object(
	load::context const &resources_,
	sge::renderer::device_ptr const rend_,
	sge::font::object &font,
	client::cursor::object_ptr const cursor_
)
:
	resources_(resources_),
	rend_(rend_),
	normal_system_(rend_),
	colored_system_(rend_),
	client_system_(rend_),
	particle_system_(rend_),
	hud_(font),
	paused_(false),
	player_id_(invalid_id),
	transform_callback_(
		std::tr1::bind(
			&object::transform,
			this,
			std::tr1::placeholders::_1
		)
	),
	insert_callback_(
		std::tr1::bind(
			&object::insert,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	),
	message_environment_(
		new message_environment(
			*this,
			hud_
		)
	),
	control_environment_(
		new scene::control_environment(
			*this,
			cursor_
		)
	),
	message_dispatcher_(
		new message::dispatcher(
			*message_environment_
		)
	),
	entities_()
{}

sanguis::client::draw2d::scene::object::~object()
{}

void
sanguis::client::draw2d::scene::object::process_message(
	sanguis::messages::base const &m
)
{
	static sanguis::messages::call::object<
		boost::mpl::vector21<
			sanguis::messages::add_aoe_projectile,
			sanguis::messages::add_enemy,
			sanguis::messages::add_friend,
			sanguis::messages::add_pickup,
			sanguis::messages::add_player,
			sanguis::messages::add_projectile,
			sanguis::messages::add_weapon_pickup,
			sanguis::messages::change_weapon,
			sanguis::messages::experience,
			sanguis::messages::health,
			sanguis::messages::level_up,
			sanguis::messages::max_health,
			sanguis::messages::move,
			sanguis::messages::remove,
			sanguis::messages::resize,
			sanguis::messages::rotate,
			sanguis::messages::start_attacking,
			sanguis::messages::stop_attacking,
			sanguis::messages::start_reloading,
			sanguis::messages::stop_reloading,
			sanguis::messages::speed
		>,
		message::dispatcher
	> dispatcher;

	dispatcher(
		m,
		*message_dispatcher_,
		std::tr1::bind(
			&message::dispatcher::process_default_msg,
			message_dispatcher_.get(),
			std::tr1::placeholders::_1
		)
	);
}

sanguis::entity_id
sanguis::client::draw2d::scene::object::client_message(
	client::messages::add const &m
)
{
	std::pair<
		entity_map::iterator,
		bool
	> const ret(
		entities_.insert(
			next_id(),
			factory::client(
				client_system(),
				resources_.resources().textures(),
				m.type(),
				screen_size()
			)
		)
	);
	
	if(
		ret.second == false
	)
		throw exception(
			FCPPT_TEXT("Client object with id already in entity list!")
		);
	
	// FIXME: configure the object here, too!
	//
	return ret.first->first;
}

void
sanguis::client::draw2d::scene::object::client_message(
	client::messages::visible const &m
)
{
	fcppt::dynamic_cast_<
		entities::with_visibility &
	>(
		entity(
			m.id()
		)
	).visible(
		m.get()
	);
}

void
sanguis::client::draw2d::scene::object::draw(
	time_type const delta
)
{
	time_type const real_delta =
		paused_
		? 0
		: delta;
	
	for(
		entity_map::iterator it(
			entities_.begin()
		),
		next(it);
		it != entities_.end();
		it = next
	)
	{
		++next;

		entities::base &e = *it->second;

		e.update(
			real_delta
		);

		if(
			e.may_be_removed()
		)
		{
			e.on_remove();

			entities_.erase(it);
		}
	}

	render_systems();

	hud_.update(
		delta
	);
}

void
sanguis::client::draw2d::scene::object::pause(
	bool const p
)
{
	paused_ = p;
}

void
sanguis::client::draw2d::scene::object::player_id(
	entity_id const nplayer_id_
)
{
	if(
		player_id_ == nplayer_id_
	)
	{
		FCPPT_LOG_WARNING(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("player_id ")
				<< (
					player_id_ == invalid_id
					?
						FCPPT_TEXT("unset")
					:
						FCPPT_TEXT("set")
				)
				<< FCPPT_TEXT(" twice!")
		);
	}

	player_id_ = nplayer_id_;
}

sanguis::client::control::environment &
sanguis::client::draw2d::scene::object::control_environment() const
{
	return *control_environment_;
}

void
sanguis::client::draw2d::scene::object::render_systems()
{
	sge::renderer::state::scoped const state_(
		rend_,
		sge::sprite::render_states()
	);

	client_system_.matrices();

	client_system_.render(
		z_ordering::background,
		sge::sprite::default_equal()
	);
		
	normal_system_.matrices();

	for(
		sprite::order index(
			z_ordering::corpses
		);
		index < z_ordering::healthbar_lower;
		++index
	)
		normal_system_.render(
			index,
			sge::sprite::default_equal()
		);
	
	for(
		sprite::order index(
			z_ordering::healthbar_lower
		);
		index < z_ordering::smoke;
		++index
	)
		colored_system_.render(
			index,
			sge::sprite::default_equal()
		);

	for(
		sprite::order index(
			z_ordering::smoke
		);
		index < z_ordering::cursor;
		++index
	)
		particle_system_.render(
			index,
			sge::sprite::default_equal()
		);

	client_system_.matrices();

	client_system_.render(
		z_ordering::cursor,
		sge::sprite::default_equal()
	);
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::object::insert(
	entities::auto_ptr e,
	entity_id const id
)
{
	std::pair<
		entity_map::iterator,
		bool
	> const ret(
		entities_.insert(
			id,
			e
		)
	);

	if(
		!ret.second
	)
		throw exception(
			(
				fcppt::format(
					FCPPT_TEXT("draw: Failed to insert object with id %1%!")
				)
				% id
			).str()
		);
	
	return *ret.first->second;
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::object::entity(
	entity_id const id
)
{
	entity_map::iterator const it(
		entities_.find(
			id
		)
	);

	if(
		it == entities_.end()
	)
		throw exception(
			(
				fcppt::format(
					FCPPT_TEXT("draw: Object with id %1% not in entity map!")
				)
				% id
			).str()
		);
	return *it->second;
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::object::own_player()
{
	try
	{
		return entity(
			player_id_
		);
	}
	catch(
		fcppt::exception const &e
	)
	{
		FCPPT_LOG_ERROR(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("In own_player: ")
				<< e.string()
		);

		throw;
	}
}

void
sanguis::client::draw2d::scene::object::transform(
	sprite::point const &center_
)
{
#if 0
	vector2 const translation_(
		screen_center(
			center_,
			screen_size()
		)
	);

	sprite::matrix const matrix_(
		fcppt::math::matrix::translation(
			translation_.x(),
			translation_.y(),
			static_cast<sprite::float_unit>(0)
		)
	);

	normal_system_.transform(		
		matrix_
	);

	colored_system_.transform(		
		matrix_
	);

	particle_system_.transform(		
		matrix_
	);
#endif
}

sanguis::client::draw2d::transform_callback const &
sanguis::client::draw2d::scene::object::transform_callback() const
{
	return transform_callback_;	
}

sanguis::client::draw2d::insert_callback const &
sanguis::client::draw2d::scene::object::insert_callback() const
{
	return insert_callback_;
}

sanguis::client::draw2d::sprite::normal::system &
sanguis::client::draw2d::scene::object::normal_system()
{
	return normal_system_;
}

sanguis::client::draw2d::sprite::colored::system &
sanguis::client::draw2d::scene::object::colored_system()
{
	return colored_system_;
}

sanguis::client::draw2d::sprite::client::system &
sanguis::client::draw2d::scene::object::client_system()
{
	return client_system_;
}

sanguis::client::draw2d::sprite::particle::system &
sanguis::client::draw2d::scene::object::particle_system()
{
	return particle_system_;
}

sanguis::load::model::collection const &
sanguis::client::draw2d::scene::object::load_collection() const
{
	return resources_.models()();
}

sanguis::entity_id
sanguis::client::draw2d::scene::object::player_id() const
{
	return player_id_;
}

sge::renderer::screen_size const
sanguis::client::draw2d::scene::object::screen_size() const
{
	return rend_->screen_size();
}
