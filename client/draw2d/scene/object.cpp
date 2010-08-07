#include "object.hpp"
#include "message_environment.hpp"
#include "control_environment.hpp"
#include "screen_center.hpp"
#include "background_dim.hpp"
#include "../message/dispatcher.hpp"
#include "../factory/client.hpp"
#include "../sprite/order.hpp"
#include "../sprite/matrix.hpp"
#include "../entities/with_visibility.hpp"
#include "../sunlight/make_color.hpp"
#include "../sunlight/sun_angle.hpp"
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
#include <sge/renderer/material.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/sprite/default_equal.hpp>
#include <sge/sprite/intrusive/system_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/image/colors.hpp>

#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/construct.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/dynamic_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/format.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/assert.hpp>

#include <boost/foreach.hpp>

#include <utility>

sanguis::client::draw2d::scene::object::object(
	load::context const &_resources,
	sge::renderer::device_ptr const _rend,
	sge::font::metrics_ptr const _font_metrics,
	sge::font::drawer_ptr const _font_drawer,
	client::cursor::object_ptr const _cursor,
	std::tm const &_current_time
)
:
	resources_(_resources),
	rend_(_rend),
	normal_system_(rend_),
	colored_system_(rend_),
	client_system_(rend_),
	particle_system_(rend_),
	hud_(
		_font_metrics,
		_font_drawer
	),
	paused_(false),
	background_id_(invalid_id),
	player_center_(
		sprite::point::null()
	),
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
			_cursor
		)
	),
	message_dispatcher_(
		new message::dispatcher(
			*message_environment_
		)
	),
	entities_(),
	current_time_(
		_current_time
	)
{}

sanguis::client::draw2d::scene::object::~object()
{}

void
sanguis::client::draw2d::scene::object::process_message(
	sanguis::messages::base const &m
)
{
	static sanguis::messages::call::object<
		boost::mpl::vector23<
			sanguis::messages::add_aoe_projectile,
			sanguis::messages::add_enemy,
			sanguis::messages::add_friend,
			sanguis::messages::add_own_player,
			sanguis::messages::add_pickup,
			sanguis::messages::add_player,
			sanguis::messages::add_projectile,
			sanguis::messages::add_weapon_pickup,
			sanguis::messages::change_weapon,
			sanguis::messages::die,
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
	
	entity_id const id(
		ret.first->first
	);

	if(
		m.type() == client::entity_type::background
	)
		background_id_ = id;

	// FIXME: configure the object here, too!
	//
	return id;
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
			entities_.erase(
				it
			);
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
sanguis::client::draw2d::scene::object::set_time(
		std::tm const &new_time_
)
{
	current_time_ = new_time_;
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

	// TODO: the sprite systems should not hold their matrices!

	FCPPT_ASSERT(
		background_id_ != invalid_id
	);


	render_lighting();

	for(
		sprite::order index(
			z_ordering::smoke
		);
		index <= z_ordering::rubble;
		++index
	)
		particle_system_.render(
			index,
			sge::sprite::default_equal()
		);

	for(
		sprite::order index(
			z_ordering::healthbar_lower
		);
		index <= z_ordering::healthbar_upper;
		++index
	)
		colored_system_.render(
			index,
			sge::sprite::default_equal()
		);

	client_system_.matrices();

	client_system_.render(
		z_ordering::cursor,
		sge::sprite::default_equal()
	);
}

void
sanguis::client::draw2d::scene::object::render_lighting()
{
	sge::renderer::state::scoped const state(
		rend_,
		sge::renderer::state::list
		(
			sge::renderer::state::bool_::enable_lighting = true
		)
		(
			sge::renderer::state::color::ambient_light_color
				= sunlight::make_color(
					sunlight::sun_angle(
						current_time_
					)
				)
		)
	);

	rend_->material(
		sge::renderer::material(
			sge::image::colors::black(),
			sge::image::colors::white(),
			sge::image::colors::black(),
			sge::image::colors::black(),
			0.
		)
	);

	client_system_.matrices();

	vector2 const translation_(
		screen_center(
			player_center_,
			screen_size()
		)
	);

	rend_->transform(
		sge::renderer::matrix_mode::texture,
		fcppt::math::matrix::translation(
			fcppt::math::vector::construct(
				-translation_
				/
				// TODO: HACK, HACK
				background_dim(
					entity(
						background_id_
					)
				),
				0.f
			)
		)
	);

	client_system_.render(
		z_ordering::background,
		sge::sprite::default_equal()
	);

	client_system_.renderer()->transform(
		sge::renderer::matrix_mode::texture,
		sprite::client::system::matrix::identity()
	);

	normal_system_.transform(		
		fcppt::math::matrix::translation(
			translation_.x(),
			translation_.y(),
			static_cast<sprite::float_unit>(0)
		)
	);
	
	normal_system_.matrices();

	for(
		sprite::order index(
			z_ordering::corpses
		);
		index <= z_ordering::player_upper;
		++index
	)
		normal_system_.render(
			index,
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
	{
		FCPPT_LOG_ERROR(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("Tried to insert object with id ")
				<< id
				<< FCPPT_TEXT(" twice!")
		);

		// FIXME: why does this still happen?
#if 0
		throw exception(
			(
				fcppt::format(
					FCPPT_TEXT("draw: Tried to insert object with id %1% twice!")
				)
				% id
			).str()
		);
#endif
	}
	
	return *ret.first->second;
}

void
sanguis::client::draw2d::scene::object::remove(
	entity_id const id
)
{
	if(
		!entities_.erase(
			id
		)
	)
		throw exception(
			(
				fcppt::format(
					FCPPT_TEXT("Object with id %1% cannot be removed!")
				)
				% id
			).str()
		);
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
					FCPPT_TEXT("Object with id %1% not in entity map!")
				)
				% id
			).str()
		);
	return *it->second;
}

sanguis::client::draw2d::sprite::point const
sanguis::client::draw2d::scene::object::player_center() const
{
	return player_center_;
}

void
sanguis::client::draw2d::scene::object::transform(
	sprite::point const &center_
)
{
	player_center_ = center_;
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

sge::renderer::screen_size const
sanguis::client::draw2d::scene::object::screen_size() const
{
	return rend_->screen_size();
}
