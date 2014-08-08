#include <sanguis/exception.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/random_seed.hpp>
#include <sanguis/update_diff_clock.hpp>
#include <sanguis/client/cursor.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/control/attack_dest.hpp>
#include <sanguis/client/control/cursor_position.hpp>
#include <sanguis/client/control/optional_attack_dest.hpp>
#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/optional_player_center.hpp>
#include <sanguis/client/draw2d/optional_translation.hpp>
#include <sanguis/client/draw2d/player_center.hpp>
#include <sanguis/client/draw2d/player_center_callback.hpp>
#include <sanguis/client/draw2d/translation.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/entities/own_unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/hover/optional_info.hpp>
#include <sanguis/client/draw2d/message/dispatcher.hpp>
#include <sanguis/client/draw2d/scene/object.hpp>
#include <sanguis/client/draw2d/scene/background.hpp>
#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/client/draw2d/scene/control_environment.hpp>
#include <sanguis/client/draw2d/scene/message_environment.hpp>
#include <sanguis/client/draw2d/scene/translation.hpp>
#include <sanguis/client/draw2d/scene/hover/base.hpp>
#include <sanguis/client/draw2d/scene/hover/base_unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/hover/create.hpp>
#include <sanguis/client/draw2d/scene/hover/parameters.hpp>
#include <sanguis/client/draw2d/scene/world/object.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/state.hpp>
#include <sanguis/client/draw2d/sprite/state_choices.hpp>
#include <sanguis/client/draw2d/sprite/client/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/colored/system_decl.hpp>
#include <sanguis/client/load/context.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sanguis/client/load/resource/context.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
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
#include <sanguis/messages/server/call/object.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/sprite/matrix.hpp>
#include <sge/sprite/optional_matrix.hpp>
#include <sge/sprite/projection_matrix.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/scoped.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/format.hpp>
#include <fcppt/make_enum_range_start_end.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/optional_bind.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map_iteration_second.hpp>
#include <fcppt/algorithm/sequence_iteration.hpp>
#include <fcppt/container/find_exn.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/construct.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector30.hpp>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::object::object(
	sanguis::client::load::context const &_resources,
	sanguis::client::load::hud::context &_hud_resources,
	sanguis::client::sound_manager &_sound_manager,
	sanguis::gui::style::base const &_gui_style,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::viewport::manager &_viewport_manager,
	sanguis::client::player_health_callback const &_player_health_callback,
	sanguis::client::cursor &_cursor
)
:
	diff_clock_(),
	random_generator_(
		sanguis::random_seed()
	),
	sound_manager_(
		_sound_manager
	),
	resources_(
		_resources
	),
	hud_resources_(
		_hud_resources
	),
	aura_resources_(
		resources_.resources().textures()
	),
	gui_style_(
		_gui_style
	),
	renderer_(
		_renderer
	),
	font_(
		_font
	),
	cursor_(
		_cursor
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
	player_center_(),
	translation_(),
	player_center_callback_(
		std::bind(
			&sanguis::client::draw2d::scene::object::player_center,
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
			*world_,
			_player_health_callback
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
	background_(
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::scene::background
		>(
			_resources,
			client_system_,
			_viewport_manager
		)
	),
	hovers_(),
	viewport_connection_(
		_viewport_manager.manage_callback(
			std::bind(
				&sanguis::client::draw2d::scene::object::update_translation,
				this
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
	sanguis::messages::server::base const &_message
)
{
	static sanguis::messages::server::call::object<
		boost::mpl::vector22<
			sanguis::messages::server::add_aoe_projectile,
			sanguis::messages::server::add_aura,
			sanguis::messages::server::add_buff,
			sanguis::messages::server::add_destructible,
			sanguis::messages::server::add_enemy,
			sanguis::messages::server::add_friend,
			sanguis::messages::server::add_own_player,
			sanguis::messages::server::add_pickup,
			sanguis::messages::server::add_player,
			sanguis::messages::server::add_projectile,
			sanguis::messages::server::add_weapon_pickup,
			sanguis::messages::server::change_weapon,
			sanguis::messages::server::change_world,
			sanguis::messages::server::die,
			sanguis::messages::server::health,
			sanguis::messages::server::max_health,
			sanguis::messages::server::move,
			sanguis::messages::server::remove,
			sanguis::messages::server::remove_buff,
			sanguis::messages::server::rotate,
			sanguis::messages::server::speed,
			sanguis::messages::server::weapon_status
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

	sanguis::client::control::optional_attack_dest const attack_dest{
		fcppt::optional_bind(
			control_environment_->position(),
			[
				this
			](
				sanguis::client::control::cursor_position const _pos
			)
			{
				return
					control_environment_->translate_attack_dest(
						_pos
					);
			}
		)
	};

	hovers_.clear();

	fcppt::algorithm::map_iteration_second(
		entities_,
		[
			this,
			attack_dest
		](
			sanguis::client::draw2d::entities::unique_ptr const &_entity
		)
		{
			_entity->update();

			if(
				attack_dest
			)
				this->hover_display(
					*_entity,
					*attack_dest
				);

			return
				_entity->may_be_removed();
		}
	);

	fcppt::algorithm::sequence_iteration(
		own_entities_,
		[](
			sanguis::client::draw2d::entities::own_unique_ptr const &_entity
		)
		{
			_entity->update();

			return
				_entity->may_be_removed();
		}
	);
}

void
sanguis::client::draw2d::scene::object::draw(
	sge::renderer::context::ffp &_render_context
)
{
	this->render_systems(
		_render_context
	);
}

void
sanguis::client::draw2d::scene::object::overlay(
	sge::renderer::context::ffp &_render_context
)
{
	cursor_.draw(
		_render_context
	);

	// TODO: Draw additional info
}

void
sanguis::client::draw2d::scene::object::pause(
	bool const _paused
)
{
	paused_ =
		_paused;

	for(
		auto &cur
		:
		entities_
	)
		cur.second->pause(
			_paused
		);

	for(
		auto &cur
		:
		own_entities_
	)
		cur->pause(
			_paused
		);
}

sanguis::client::control::environment &
sanguis::client::draw2d::scene::object::control_environment() const
{
	return
		*control_environment_;
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
		||
		!translation_
	)
	{
		_render_context.clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::color::predef::black()
			)
		);

		return;
	}

	sge::renderer::state::ffp::transform::object_unique_ptr const projection_state(
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

	sge::renderer::state::ffp::transform::object_unique_ptr const transform_state(
		renderer_.create_transform_state(
			sge::renderer::state::ffp::transform::parameters(
				fcppt::math::matrix::translation(
					fcppt::math::vector::construct(
						fcppt::math::vector::structure_cast<
							sanguis::client::draw2d::vector2
						>(
							translation_->get()
						),
						fcppt::literal<
							sanguis::client::draw2d::funit
						>(
							0
						)
					)
				)
			)
		)
	);

	background_->render(
		_render_context,
		*translation_
	);

	sge::renderer::state::ffp::transform::scoped const scoped_transform(
		_render_context,
		sge::renderer::state::ffp::transform::mode::world,
		*transform_state
	);

	world_->draw(
		_render_context
	);

	for(
		auto index
		:
		fcppt::make_enum_range_start_end(
			sanguis::client::draw2d::z_ordering::corpses,
			sanguis::client::draw2d::z_ordering::flare
		)
	)
		normal_system_.render(
			_render_context,
			index
		);

	for(
		auto const index
		:
		fcppt::make_enum_range_start_end(
			sanguis::client::draw2d::z_ordering::healthbar_lower,
			sanguis::client::draw2d::z_ordering::healthbar_upper
		)
	)
		colored_system_.render(
			_render_context,
			index
		);

	for(
		sanguis::client::draw2d::scene::hover::base_unique_ptr const &hover
		:
		hovers_
	)
		hover->draw(
			_render_context
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
		entities_.insert(
			std::make_pair(
				_id,
				std::move(
					_entity
				)
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

	return
		*ret.first->second;
}

sanguis::client::draw2d::entities::own &
sanguis::client::draw2d::scene::object::insert_own(
	sanguis::client::draw2d::entities::own_unique_ptr &&_entity
)
{
	own_entities_.push_back(
		std::move(
			_entity
		)
	);

	return
		*own_entities_.back();
}

void
sanguis::client::draw2d::scene::object::hover_display(
	sanguis::client::draw2d::entities::base const &_entity,
	sanguis::client::control::attack_dest const _pos
)
{
	if(
		_entity.dead()
		||
		!_entity.cursor_collision(
			sanguis::client::draw2d::sprite::center(
				fcppt::math::vector::structure_cast<
					sanguis::client::draw2d::sprite::center::value_type
				>(
					_pos
				)
			)
		)
	)
		return;

	sanguis::client::draw2d::entities::hover::optional_info const info(
		_entity.hover()
	);

	if(
		!info
	)
		return;

	hovers_.push_back(
		sanguis::client::draw2d::scene::hover::create(
			sanguis::client::draw2d::scene::hover::parameters(
				gui_style_,
				renderer_,
				font_,
				hud_resources_,
				_entity.center(),
				_entity.radius()
			),
			*info
		)
	);
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
	return
		*fcppt::container::find_exn(
			entities_,
			_id,
			[
				_id
			]{
				return
					sanguis::exception{
						(
							fcppt::format(
								FCPPT_TEXT("Object with id %1% not in entity map!")
							)
							% _id
						)
						.str()
					};
			}
		);
}

sanguis::client::draw2d::optional_translation const
sanguis::client::draw2d::scene::object::translation() const
{
	return
		translation_;
}

void
sanguis::client::draw2d::scene::object::player_center(
	sanguis::client::draw2d::optional_player_center const _player_center
)
{
	player_center_
		= _player_center;

	this->update_translation();
}

void
sanguis::client::draw2d::scene::object::update_translation()
{
	if(
		!player_center_
	)
		translation_.reset();
	else
		translation_ =
			sanguis::client::draw2d::optional_translation(
				sanguis::client::draw2d::scene::translation(
					*player_center_,
					this->screen_size()
				)
			);

	world_->translation(
		translation_
	);
}

void
sanguis::client::draw2d::scene::object::change_world(
	sanguis::client::world_parameters const &_parameters
)
{
	own_entities_.clear();

	fcppt::algorithm::map_iteration_second(
		entities_,
		[](
			sanguis::client::draw2d::entities::unique_ptr const &_entity
		)
		{
			return
				_entity->dead();
		}
	);

	world_->change(
		_parameters,
		translation_
	);
}

sanguis::diff_clock const &
sanguis::client::draw2d::scene::object::diff_clock() const
{
	return
		diff_clock_;
}

sanguis::random_generator &
sanguis::client::draw2d::scene::object::random_generator()
{
	return
		random_generator_;
}

sanguis::client::sound_manager &
sanguis::client::draw2d::scene::object::sound_manager() const
{
	return
		sound_manager_;
}

sanguis::client::draw2d::player_center_callback const &
sanguis::client::draw2d::scene::object::player_center_callback() const
{
	return
		player_center_callback_;
}

sanguis::client::draw2d::insert_own_callback const &
sanguis::client::draw2d::scene::object::insert_own_callback() const
{
	return
		insert_own_callback_;
}

sanguis::client::draw2d::sprite::normal::system &
sanguis::client::draw2d::scene::object::normal_system()
{
	return
		normal_system_;
}

sanguis::client::draw2d::sprite::colored::system &
sanguis::client::draw2d::scene::object::colored_system()
{
	return
		colored_system_;
}

sanguis::client::draw2d::sprite::client::system &
sanguis::client::draw2d::scene::object::client_system()
{
	return
		client_system_;
}

sanguis::client::load::model::collection const &
sanguis::client::draw2d::scene::object::load_collection() const
{
	return
		resources_.models()();
}

sanguis::client::load::auras::context &
sanguis::client::draw2d::scene::object::aura_resources()
{
	return
		aura_resources_;
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
	return
		renderer_.onscreen_target().viewport();
}
