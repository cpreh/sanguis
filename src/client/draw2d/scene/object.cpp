#include <sanguis/client/draw2d/scene/object.hpp>
#include <sanguis/client/draw2d/scene/background.hpp>
#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/client/draw2d/scene/control_environment.hpp>
#include <sanguis/client/draw2d/scene/foreach_z_ordering.hpp>
#include <sanguis/client/draw2d/scene/hud.hpp>
#include <sanguis/client/draw2d/scene/message_environment.hpp>
#include <sanguis/client/draw2d/scene/screen_center.hpp>
#include <sanguis/client/draw2d/scene/world/object.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/message/dispatcher.hpp>
#include <sanguis/client/draw2d/sprite/order.hpp>
#include <sanguis/client/draw2d/sprite/float_unit.hpp>
#include <sanguis/client/draw2d/sunlight/make_color.hpp>
#include <sanguis/client/draw2d/sunlight/sun_angle.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/load/context.hpp>
#include <sanguis/load/resource/context.hpp>
#include <sanguis/messages/call/object.hpp>
#include <sanguis/exception.hpp>
#include <sge/audio/listener.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/image/colors.hpp>
#include <sge/renderer/ambient_color.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/diffuse_color.hpp>
#include <sge/renderer/emissive_color.hpp>
#include <sge/renderer/material.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/specular_color.hpp>
#include <sge/renderer/shininess.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/projection_matrix.hpp>
#include <sge/sprite/render/states.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/matrix/static.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/format.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector30.hpp>
#include <utility>
#include <ctime>
#include <fcppt/config/external_end.hpp>

sanguis::client::draw2d::scene::object::object(
	load::context const &_resources,
	sge::renderer::device &_rend,
	sge::charconv::system &_charconv_system,
	sge::font::metrics &_font_metrics,
	sge::font::text::drawer &_font_drawer,
	sge::audio::listener &_audio_listener,
	std::tm const &_current_time,
	sge::viewport::manager &_viewport_manager
)
:
	diff_clock_(),
	resources_(
		_resources
	),
	rend_(
		_rend
	),
	normal_system_(
		rend_
	),
	colored_system_(
		rend_
	),
	client_system_(
		rend_
	),
	particle_system_(
		rend_
	),
	hud_(
		fcppt::make_unique_ptr<
			scene::hud
		>(
			fcppt::ref(
				_font_metrics
			),
			fcppt::ref(
				_font_drawer
			),
			_current_time
		)
	),
	world_(
		fcppt::make_unique_ptr<
			scene::world::object
		>(
			fcppt::ref(
				_rend
			),
			fcppt::cref(
				_resources.resources().textures()
			)
		)
	),
	audio_listener_(
		_audio_listener
	),
	paused_(
		false
	),
	player_center_(
		sprite::center::value_type::null()
	),
	transform_callback_(
		std::tr1::bind(
			&object::transform,
			this,
			std::tr1::placeholders::_1
		)
	),
	insert_own_callback_(
		std::tr1::bind(
			&object::insert_own,
			this,
			std::tr1::placeholders::_1
		)
	),
	message_environment_(
		fcppt::make_unique_ptr<
			message_environment
		>(
			fcppt::ref(
				*this
			),
			fcppt::ref(
				*hud_
			),
			fcppt::ref(
				*world_
			)
		)
	),
	control_environment_(
		fcppt::make_unique_ptr<
			scene::control_environment
		>(
			fcppt::ref(
				*this
			)
		)
	),
	message_dispatcher_(
		fcppt::make_unique_ptr<
			message::dispatcher
		>(
			fcppt::ref(
				*message_environment_
			),
			fcppt::ref(
				_charconv_system
			)
		)
	),
	entities_(),
	own_entities_(),
	current_time_(
		_current_time
	),
	default_transform_(
		sge::renderer::matrix4::identity()
	),
	background_(
		fcppt::make_unique_ptr<
			scene::background
		>(
			fcppt::cref(
				_resources
			),
			fcppt::ref(
				client_system_
			),
			fcppt::ref(
				_viewport_manager
			)
		)
	)
{
	rend_.material(
		sge::renderer::material(
			sge::renderer::diffuse_color(
				sge::image::colors::black()
			),
			sge::renderer::ambient_color(
				sge::image::colors::white()
			),
			sge::renderer::specular_color(
				sge::image::colors::black()
			),
			sge::renderer::emissive_color(
				sge::image::colors::black()
			),
			sge::renderer::shininess(
				0.f
			)
		)
	);
}

sanguis::client::draw2d::scene::object::~object()
{
}

void
sanguis::client::draw2d::scene::object::process_message(
	sanguis::messages::base const &_message
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
			sanguis::messages::change_world,
			sanguis::messages::die,
			sanguis::messages::experience,
			sanguis::messages::health,
			sanguis::messages::level_up,
			sanguis::messages::max_health,
			sanguis::messages::move,
			sanguis::messages::remove,
			sanguis::messages::rotate,
			sanguis::messages::start_attacking,
			sanguis::messages::stop_attacking,
			sanguis::messages::start_reloading,
			sanguis::messages::stop_reloading,
			sanguis::messages::speed
		>,
		sanguis::client::draw2d::message::dispatcher
	>::type dispatcher;

	dispatcher(
		_message,
		*message_dispatcher_,
		std::tr1::bind(
			&message::dispatcher::process_default_msg,
			message_dispatcher_.get(),
			std::tr1::placeholders::_1
		)
	);
}

void
sanguis::client::draw2d::scene::object::update(
	sanguis::duration const &_delta
)
{
	if(
		!paused_
	)
		diff_clock_.update(
			_delta
		);

	for(
		entity_map::iterator it(
			entities_.begin()
		),
		next(
			it
		);
		it != entities_.end();
		it = next
	)
	{
		++next;

		entities::base &cur_entity(
			*it->second
		);

		cur_entity.update();

		if(
			cur_entity.may_be_removed()
		)
			entities_.erase(
				it
			);
	}

	for(
		own_entity_list::iterator it(
			own_entities_.begin()
		);
		it != own_entities_.end();
	)
	{
		it->update();

		if(
			it->may_be_removed()
		)
			it =
				own_entities_.erase(
					it
				);
		else
			++it;
	}
}

void
sanguis::client::draw2d::scene::object::draw()
{
	this->render_systems();

	hud_->draw();
}

void
sanguis::client::draw2d::scene::object::pause(
	bool const _paused
)
{
	paused_ = _paused;
}

void
sanguis::client::draw2d::scene::object::set_time(
	std::tm const &_current_time
)
{
	current_time_ = _current_time;

	hud_->time(
		current_time_
	);
}

sanguis::client::control::environment &
sanguis::client::draw2d::scene::object::control_environment() const
{
	return *control_environment_;
}

void
sanguis::client::draw2d::scene::object::render_systems()
{
	sge::renderer::state::scoped const state(
		rend_,
		sge::sprite::render::states<
			client::draw2d::sprite::normal::choices
		>()
	);

	rend_.transform(
		sge::renderer::matrix_mode::projection,
		sge::sprite::projection_matrix(
			this->viewport()
		)
	);

	rend_.transform(
		sge::renderer::matrix_mode::world,
		default_transform_
	);

	this->render_lighting();

	SANGUIS_CLIENT_DRAW2D_SCENE_FOREACH_Z_ORDERING(
		index,
		z_ordering::smoke,
		z_ordering::rubble
	)
		particle_system_.render(
			index
		);

	SANGUIS_CLIENT_DRAW2D_SCENE_FOREACH_Z_ORDERING(
		index,
		z_ordering::healthbar_lower,
		z_ordering::healthbar_upper
	)
		colored_system_.render(
			index
		);

	rend_.transform(
		sge::renderer::matrix_mode::world,
		default_transform_
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

	draw2d::vector2 const translation(
		scene::screen_center(
			player_center_,
			this->screen_size()
		)
	);

	background_->render(
		translation
	);

	rend_.transform(
		sge::renderer::matrix_mode::world,
		default_transform_
		*
		fcppt::math::matrix::translation(
			translation.x(),
			translation.y(),
			static_cast<
				sprite::float_unit
			>(
				0
			)
		)
	);

	world_->draw(
		translation
	);

	SANGUIS_CLIENT_DRAW2D_SCENE_FOREACH_Z_ORDERING(
		index,
		z_ordering::corpses,
		z_ordering::player_upper
	)
		normal_system_.render(
			index
		);
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::object::insert(
	entities::unique_ptr _entity,
	entity_id const _id
)
{
	typedef std::pair<
		entity_map::iterator,
		bool
	> ret_type;

	ret_type const ret(
		fcppt::container::ptr::insert_unique_ptr_map(
			entities_,
			_id,
			move(
				_entity
			)
		)
	);

	if(
		!ret.second
	)
		throw sanguis::exception(
			(
				fcppt::format(
					FCPPT_TEXT("draw: Tried to insert object with id %1% twice!")
				)
				% _id
			).str()
		);

	return *ret.first->second;
}

sanguis::client::draw2d::entities::own &
sanguis::client::draw2d::scene::object::insert_own(
	entities::own_auto_ptr _entity
)
{
	own_entities_.push_back(
		_entity
	);

	return own_entities_.back();
}

void
sanguis::client::draw2d::scene::object::remove(
	entity_id const _id
)
{
	if(
		!entities_.erase(
			_id
		)
	)
		throw sanguis::exception(
			(
				fcppt::format(
					FCPPT_TEXT("Object with id %1% cannot be removed!")
				)
				% _id
			).str()
		);
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::object::entity(
	entity_id const _id
)
{
	entity_map::iterator const it(
		entities_.find(
			_id
		)
	);

	if(
		it == entities_.end()
	)
		throw sanguis::exception(
			(
				fcppt::format(
					FCPPT_TEXT("Object with id %1% not in entity map!")
				)
				% _id
			).str()
		);

	return *it->second;
}

sanguis::client::draw2d::sprite::center const
sanguis::client::draw2d::scene::object::player_center() const
{
	return player_center_;
}

void
sanguis::client::draw2d::scene::object::transform(
	sprite::center const &_player_center
)
{
	player_center_ = _player_center;

	// TODO: abstract this, and why (x,z)?
	audio_listener_.position(
		sge::audio::vector(
			static_cast<
				sge::audio::scalar
			>(
				player_center_.get().x()
			),
			static_cast<
				sge::audio::scalar
			>(
				0
			),
			static_cast<
				sge::audio::scalar
			>(
				player_center_.get().y()
			)
		)
	);
}

sanguis::diff_clock const &
sanguis::client::draw2d::scene::object::diff_clock() const
{
	return diff_clock_;
}

sanguis::client::draw2d::transform_callback const &
sanguis::client::draw2d::scene::object::transform_callback() const
{
	return transform_callback_;
}

sanguis::client::draw2d::insert_own_callback const &
sanguis::client::draw2d::scene::object::insert_own_callback() const
{
	return insert_own_callback_;
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
	return
		scene::background_dim(
			rend_
		);
}

sge::renderer::viewport const
sanguis::client::draw2d::scene::object::viewport() const
{
	return rend_.onscreen_target().viewport();
}
