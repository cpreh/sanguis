#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
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
#include <sanguis/client/draw2d/entities/own_unique_ptr.hpp>
#include <sanguis/client/draw2d/message/dispatcher.hpp>
#include <sanguis/client/draw2d/sprite/float_unit.hpp>
#include <sanguis/client/draw2d/sprite/state_choices.hpp>
#include <sanguis/client/draw2d/sunlight/make_color.hpp>
#include <sanguis/client/draw2d/sunlight/sun_angle.hpp>
#include <sanguis/load/context.hpp>
#include <sanguis/load/resource/context.hpp>
#include <sanguis/messages/call/object.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/random_seed.hpp>
#include <sanguis/update_diff_clock.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/state/ffp/lighting/ambient_color.hpp>
#include <sge/renderer/state/ffp/lighting/diffuse_color.hpp>
#include <sge/renderer/state/ffp/lighting/specular_color.hpp>
#include <sge/renderer/state/ffp/lighting/object.hpp>
#include <sge/renderer/state/ffp/lighting/object_scoped_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/parameters.hpp>
#include <sge/renderer/state/ffp/lighting/scoped.hpp>
#include <sge/renderer/state/ffp/lighting/material/emissive_color.hpp>
#include <sge/renderer/state/ffp/lighting/material/object.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters.hpp>
#include <sge/renderer/state/ffp/lighting/material/scoped.hpp>
#include <sge/renderer/state/ffp/lighting/material/shininess.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_scoped_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/sprite/matrix.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/optional_matrix.hpp>
#include <sge/sprite/projection_matrix.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/scoped.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/format.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector30.hpp>
#include <ctime>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::object::object(
	sanguis::load::context const &_resources,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font_object,
	std::tm const &_current_time,
	sge::viewport::manager &_viewport_manager
)
:
	diff_clock_(),
	random_generator_(
		sanguis::random_seed()
	),
	resources_(
		_resources
	),
	renderer_(
		_renderer
	),
	sprite_states_(
		renderer_,
		sge::sprite::state::parameters<
			sanguis::client::draw2d::sprite::state_choices
		>()
	),
	normal_system_(
		renderer_,
		sprite_states_
	),
	colored_system_(
		renderer_,
		sprite_states_
	),
	client_system_(
		renderer_,
		sprite_states_
	),
	hud_(
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::scene::hud
		>(
			_font_object,
			renderer_,
			_current_time
		)
	),
	world_(
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::scene::world::object
		>(
			renderer_,
			_resources.resources().textures()
		)
	),
	paused_(
		false
	),
	player_center_(
		sanguis::client::draw2d::sprite::center::value_type::null()
	),
	transform_callback_(
		std::bind(
			&sanguis::client::draw2d::scene::object::transform,
			this,
			std::placeholders::_1
		)
	),
	insert_own_callback_(
		std::bind(
			&sanguis::client::draw2d::scene::object::insert_own,
			this,
			std::placeholders::_1
		)
	),
	message_environment_(
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::scene::message_environment
		>(
			*this,
			*hud_,
			*world_
		)
	),
	control_environment_(
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::scene::control_environment
		>(
			*this
		)
	),
	message_dispatcher_(
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::message::dispatcher
		>(
			*message_environment_
		)
	),
	entities_(),
	own_entities_(),
	current_time_(
		_current_time
	),
	background_(
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::scene::background
		>(
			_resources,
			client_system_,
			_viewport_manager
		)
	),
	material_state_(
		renderer_.create_material_state(
			sge::renderer::state::ffp::lighting::material::parameters(
				sge::renderer::state::ffp::lighting::diffuse_color(
					sge::image::color::predef::black()
				),
				sge::renderer::state::ffp::lighting::ambient_color(
					sge::image::color::predef::white()
				),
				sge::renderer::state::ffp::lighting::specular_color(
					sge::image::color::predef::black()
				),
				sge::renderer::state::ffp::lighting::material::emissive_color(
					sge::image::color::predef::black()
				),
				sge::renderer::state::ffp::lighting::material::shininess(
					0.f
				)
			)
		)
	)
{
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
	> dispatcher;

	dispatcher(
		_message,
		*message_dispatcher_,
		std::bind(
			&sanguis::client::draw2d::message::dispatcher::process_default_msg,
			message_dispatcher_.get(),
			std::placeholders::_1
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
		sanguis::update_diff_clock(
			diff_clock_,
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

		sanguis::client::draw2d::entities::base &cur_entity(
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
sanguis::client::draw2d::scene::object::draw(
	sge::renderer::context::ffp &_render_context
)
{
	this->render_systems(
		_render_context
	);

	hud_->draw(
		_render_context
	);
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
sanguis::client::draw2d::scene::object::render_systems(
	sge::renderer::context::ffp &_render_context
)
{
	sge::sprite::optional_matrix const projection_matrix(
		sge::sprite::projection_matrix(
			this->viewport()
		)
	);

	if(
		!projection_matrix
	)
		return;

	sge::renderer::state::ffp::transform::object_scoped_ptr const projection_state(
		renderer_.create_transform_state(
			sge::renderer::state::ffp::transform::parameters(
				*projection_matrix
			)
		)
	);

	sge::renderer::state::ffp::transform::scoped const scoped_projection(
		_render_context,
		sge::renderer::state::ffp::transform::mode::projection,
		*projection_state
	);

	sge::sprite::state::scoped<
		sanguis::client::draw2d::sprite::state_choices
	> const scoped_state(
		renderer_,
		_render_context,
		sge::sprite::state::default_options<
			sanguis::client::draw2d::sprite::state_choices
		>(),
		sprite_states_
	);

	sanguis::client::draw2d::vector2 const translation(
		sanguis::client::draw2d::scene::screen_center(
			player_center_,
			this->screen_size()
		)
	);

	sge::renderer::state::ffp::transform::object_scoped_ptr const transform_state(
		renderer_.create_transform_state(
			sge::renderer::state::ffp::transform::parameters(
				fcppt::math::matrix::translation(
					translation.x(),
					translation.y(),
					static_cast<
						sanguis::client::draw2d::sprite::float_unit
					>(
						0
					)
				)
			)
		)
	);

	{
		sge::renderer::state::ffp::lighting::material::scoped const scoped_material(
			_render_context,
			*material_state_
		);

		sge::renderer::state::ffp::lighting::object_scoped_ptr const lighting_state(
			renderer_.create_lighting_state(
				sge::renderer::state::ffp::lighting::parameters(
					sge::renderer::state::ffp::lighting::enabled(
						sge::renderer::state::ffp::lighting::ambient_color(
							sanguis::client::draw2d::sunlight::make_color(
								sanguis::client::draw2d::sunlight::sun_angle(
									current_time_
								)
							)
						)
					)
				)
			)
		);

		sge::renderer::state::ffp::lighting::scoped const scoped_lighting(
			_render_context,
			*lighting_state
		);

		background_->render(
			_render_context,
			translation
		);

		// TODO: scope this using a scoped_ptr!
		sge::renderer::state::ffp::transform::scoped const scoped_transform(
			_render_context,
			sge::renderer::state::ffp::transform::mode::world,
			*transform_state
		);

		world_->draw(
			_render_context,
			translation
		);

		SANGUIS_CLIENT_DRAW2D_SCENE_FOREACH_Z_ORDERING(
			index,
			sanguis::client::draw2d::z_ordering::corpses,
			sanguis::client::draw2d::z_ordering::player_upper
		)
			normal_system_.render(
				_render_context,
				index
			);
	}

	sge::renderer::state::ffp::transform::scoped const scoped_transform(
		_render_context,
		sge::renderer::state::ffp::transform::mode::world,
		*transform_state
	);

	SANGUIS_CLIENT_DRAW2D_SCENE_FOREACH_Z_ORDERING(
		index,
		sanguis::client::draw2d::z_ordering::healthbar_lower,
		sanguis::client::draw2d::z_ordering::healthbar_upper
	)
		colored_system_.render(
			_render_context,
			index
		);
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::object::insert(
	sanguis::client::draw2d::entities::unique_ptr &&_entity,
	sanguis::entity_id const _id
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
			std::move(
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
	sanguis::client::draw2d::entities::own_unique_ptr &&_entity
)
{
	fcppt::container::ptr::push_back_unique_ptr(
		own_entities_,
		std::move(
			_entity
		)
	);

	return
		own_entities_.back();
}

void
sanguis::client::draw2d::scene::object::remove(
	sanguis::entity_id const _id
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
	sanguis::entity_id const _id
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
	sanguis::client::draw2d::sprite::center const &_player_center
)
{
	player_center_ = _player_center;
}

void
sanguis::client::draw2d::scene::object::change_world(
	sanguis::client::world_parameters const &_parameters
)
{
	own_entities_.clear();

/*
	// TODO: We should have a generic algorithm for iterations like these
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

		if(
			it->second->is_decayed()
		)
			entities_.erase(
				it
			);
	}
*/
	world_->change(
		_parameters
	);
}

sanguis::diff_clock const &
sanguis::client::draw2d::scene::object::diff_clock() const
{
	return diff_clock_;
}

sanguis::random_generator &
sanguis::client::draw2d::scene::object::random_generator()
{
	return random_generator_;
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

sanguis::load::model::collection const &
sanguis::client::draw2d::scene::object::load_collection() const
{
	return resources_.models()();
}

sge::renderer::screen_size const
sanguis::client::draw2d::scene::object::screen_size() const
{
	return
		sanguis::client::draw2d::scene::background_dim(
			renderer_
		);
}

sge::renderer::target::viewport const
sanguis::client::draw2d::scene::object::viewport() const
{
	return renderer_.onscreen_target().viewport();
}
