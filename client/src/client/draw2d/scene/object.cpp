#include <sanguis/entity_id.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/optional_entity_id.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/random_seed.hpp>
#include <sanguis/update_diff_clock.hpp>
#include <sanguis/client/cursor.hpp>
#include <sanguis/client/health.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/slowed_duration.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/weapon_description_from_message.hpp>
#include <sanguis/client/world_parameters.hpp>
#include <sanguis/client/control/attack_dest.hpp>
#include <sanguis/client/control/cursor_position.hpp>
#include <sanguis/client/control/optional_attack_dest.hpp>
#include <sanguis/client/control/optional_cursor_position.hpp>
#include <sanguis/client/draw/base.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/log.hpp>
#include <sanguis/client/draw2d/optional_player_center.hpp>
#include <sanguis/client/draw2d/optional_translation.hpp>
#include <sanguis/client/draw2d/player_center.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/create_parameters.hpp>
#include <sanguis/client/draw2d/entities/load_parameters.hpp>
#include <sanguis/client/draw2d/entities/name.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/entities/own_unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/hover/info.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_auras.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_buffs.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_center.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_health.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_orientation.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_speed.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_weapon.hpp>
#include <sanguis/client/draw2d/factory/aoe_projectile.hpp>
#include <sanguis/client/draw2d/factory/destructible.hpp>
#include <sanguis/client/draw2d/factory/doodad.hpp>
#include <sanguis/client/draw2d/factory/enemy.hpp>
#include <sanguis/client/draw2d/factory/friend.hpp>
#include <sanguis/client/draw2d/factory/own_player.hpp>
#include <sanguis/client/draw2d/factory/pickup.hpp>
#include <sanguis/client/draw2d/factory/player.hpp>
#include <sanguis/client/draw2d/factory/projectile.hpp>
#include <sanguis/client/draw2d/factory/text.hpp>
#include <sanguis/client/draw2d/factory/weapon_pickup.hpp>
#include <sanguis/client/draw2d/scene/background.hpp>
#include <sanguis/client/draw2d/scene/camera.hpp>
#include <sanguis/client/draw2d/scene/object.hpp>
#include <sanguis/client/draw2d/scene/translation_matrix.hpp>
#include <sanguis/client/draw2d/scene/hover/base.hpp>
#include <sanguis/client/draw2d/scene/hover/base_unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/hover/create.hpp>
#include <sanguis/client/draw2d/scene/hover/parameters.hpp>
#include <sanguis/client/draw2d/scene/state/base.hpp>
#include <sanguis/client/draw2d/scene/state/create.hpp>
#include <sanguis/client/draw2d/scene/state/optional_scoped_unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/state/scoped.hpp>
#include <sanguis/client/draw2d/scene/world/center_to_grid_pos.hpp>
#include <sanguis/client/draw2d/scene/world/object.hpp>
#include <sanguis/client/draw2d/scene/world/parameters.hpp>
#include <sanguis/client/draw2d/scene/world/render_parameters.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/state.hpp>
#include <sanguis/client/draw2d/sprite/state_choices.hpp>
#include <sanguis/client/draw2d/sprite/client/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/white.hpp>
#include <sanguis/client/draw2d/translate/center.hpp>
#include <sanguis/client/draw2d/translate/health_pair.hpp>
#include <sanguis/client/draw2d/translate/rotation.hpp>
#include <sanguis/client/draw2d/translate/scalar_to_client.hpp>
#include <sanguis/client/draw2d/translate/speed.hpp>
#include <sanguis/client/draw2d/translate/vector_from_client.hpp>
#include <sanguis/client/load/context.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sanguis/client/load/model/context.hpp>
#include <sanguis/client/load/resource/context.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/opening_count_array.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <sanguis/messages/roles/aoe.hpp>
#include <sanguis/messages/roles/aoe_projectile_type.hpp>
#include <sanguis/messages/roles/aura_type.hpp>
#include <sanguis/messages/roles/aura_type_container.hpp>
#include <sanguis/messages/roles/buff_type.hpp>
#include <sanguis/messages/roles/buff_type_container.hpp>
#include <sanguis/messages/roles/created.hpp>
#include <sanguis/messages/roles/destructible_type.hpp>
#include <sanguis/messages/roles/doodad_type.hpp>
#include <sanguis/messages/roles/enemy_kind.hpp>
#include <sanguis/messages/roles/enemy_type.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/roles/friend_type.hpp>
#include <sanguis/messages/roles/health.hpp>
#include <sanguis/messages/roles/is_primary_weapon.hpp>
#include <sanguis/messages/roles/level.hpp>
#include <sanguis/messages/roles/max_health.hpp>
#include <sanguis/messages/roles/name.hpp>
#include <sanguis/messages/roles/opening_count.hpp>
#include <sanguis/messages/roles/pickup_type.hpp>
#include <sanguis/messages/roles/primary_weapon.hpp>
#include <sanguis/messages/roles/projectile_type.hpp>
#include <sanguis/messages/roles/seed.hpp>
#include <sanguis/messages/roles/spawn_boss.hpp>
#include <sanguis/messages/roles/weapon_status.hpp>
#include <sanguis/messages/roles/world_id.hpp>
#include <sanguis/messages/server/add_aoe_projectile.hpp>
#include <sanguis/messages/server/add_aura.hpp>
#include <sanguis/messages/server/add_buff.hpp>
#include <sanguis/messages/server/add_destructible.hpp>
#include <sanguis/messages/server/add_doodad.hpp>
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
#include <sanguis/messages/server/give_weapon.hpp>
#include <sanguis/messages/server/health.hpp>
#include <sanguis/messages/server/level_up.hpp>
#include <sanguis/messages/server/max_health.hpp>
#include <sanguis/messages/server/move.hpp>
#include <sanguis/messages/server/remove.hpp>
#include <sanguis/messages/server/remove_buff.hpp>
#include <sanguis/messages/server/remove_weapon.hpp>
#include <sanguis/messages/server/rotate.hpp>
#include <sanguis/messages/server/speed.hpp>
#include <sanguis/messages/server/weapon_status.hpp>
#include <sanguis/messages/server/call/object.hpp>
#include <sanguis/messages/types/level.hpp>
#include <alda/serialization/load/optional.hpp>
#include <alda/serialization/load/static_size.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/gui/renderer/create_stateless.hpp>
#include <sge/gui/style/base_fwd.hpp>
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
#include <sge/sprite/projection_matrix.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/scoped.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <majutsu/get.hpp>
#include <majutsu/init_types.hpp>
#include <fcppt/format.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_enum_range.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/maybe_multi.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/optional_bind.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/optional_comparison.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/optional_to_exception.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/algorithm/enum_array_fold_static.hpp>
#include <fcppt/algorithm/map_iteration_second.hpp>
#include <fcppt/algorithm/sequence_iteration.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/cast/float_to_int_fun.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector30.hpp>
#include <functional>
#include <typeinfo>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::object::object(
	sanguis::client::load::context const &_resources,
	sanguis::client::load::hud::context &_hud_resources,
	sanguis::client::sound_manager &_sound_manager,
	sge::gui::style::base const &_gui_style,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::viewport::manager &_viewport_manager,
	sanguis::client::player_health_callback const &_player_health_callback,
	sanguis::client::cursor &_cursor,
	sanguis::client::draw::debug const _debug
)
:
	sanguis::client::draw::base(),
	diff_clock_(),
	random_generator_(
		sanguis::random_seed()
	),
	sound_manager_(
		_sound_manager
	),
	model_collection_(
		_resources.models()()
	),
	hud_resources_(
		_hud_resources
	),
	aura_resources_(
		_resources.resources().textures()
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
	gui_renderer_(
		sge::gui::renderer::create_stateless(
			_renderer
		)
	),
	player_health_callback_(
		_player_health_callback
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
	client_system_(
		renderer_,
		sprite_states_
	),
	world_(
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::scene::world::object
		>(
			random_generator_,
			renderer_,
			_resources.resources().textures(),
			sanguis::client::draw2d::scene::world::parameters{
				_resources,
				client_system_,
				_viewport_manager
			},
			_debug
		)
	),
	paused_{
		false
	},
	player_id_(),
	camera_(
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::scene::camera
		>(
			_renderer
		)
	),
	player_weapons_(),
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
	hover_(),
	render_states_(
		sanguis::client::draw2d::scene::state::create(
			renderer_
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
	// TODO: Use client::dispatch?
	typedef
	sanguis::messages::server::call::object<
		boost::mpl::vector26<
			sanguis::messages::server::add_aoe_projectile,
			sanguis::messages::server::add_aura,
			sanguis::messages::server::add_buff,
			sanguis::messages::server::add_destructible,
			sanguis::messages::server::add_doodad,
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
			sanguis::messages::server::give_weapon,
			sanguis::messages::server::health,
			sanguis::messages::server::level_up,
			sanguis::messages::server::max_health,
			sanguis::messages::server::move,
			sanguis::messages::server::remove,
			sanguis::messages::server::remove_buff,
			sanguis::messages::server::remove_weapon,
			sanguis::messages::server::rotate,
			sanguis::messages::server::speed,
			sanguis::messages::server::weapon_status
		>,
		sanguis::client::draw2d::scene::object
	>
	dispatcher_type;

	static
	dispatcher_type dispatcher;

	dispatcher(
		_message,
		*this,
		dispatcher_type::default_callback{
			std::bind(
				&sanguis::client::draw2d::scene::object::process_default_msg,
				this,
				std::placeholders::_1
			)
		}
	);
}

void
sanguis::client::draw2d::scene::object::update(
	sanguis::client::slowed_duration const _delta,
	sanguis::client::control::optional_cursor_position const &_cursor_position
)
{
	if(
		!paused_
	)
	{
		sanguis::update_diff_clock(
			diff_clock_,
			_delta.get()
		);

		world_->update(
			_delta
		);
	}

	camera_->update(
		_delta,
		this->player_center()
	);

	sanguis::client::control::optional_attack_dest const attack_dest{
		fcppt::optional_bind(
			_cursor_position,
			[
				this
			](
				sanguis::client::control::cursor_position const _pos
			)
			{
				return
					this->translate_attack_dest(
						_pos
					);
			}
		)
	};

	hover_ =
		sanguis::client::draw2d::scene::object::optional_hover_unique_ptr();

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

			fcppt::maybe_void(
				attack_dest,
				[
					this,
					&_entity
				](
					sanguis::client::control::attack_dest const _attack_dest
				)
				{
					this->hover_display(
						*_entity,
						_attack_dest
					);
				}
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
	fcppt::maybe_multi(
		[
			&_render_context
		]{
			_render_context.clear(
				sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::color::predef::black()
				)
			);
		},
		[
			&_render_context,
			this
		](
			sge::sprite::matrix const &_projection_matrix,
			sanguis::client::draw2d::translation const _translation
		)
		{
			sge::renderer::state::ffp::transform::object_unique_ptr const projection_state(
				renderer_.create_transform_state(
					sge::renderer::state::ffp::transform::parameters(
						_projection_matrix
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

			background_->render(
				_render_context,
				_translation
			);

			sge::renderer::state::ffp::transform::object_unique_ptr const transform_state(
				renderer_.create_transform_state(
					sge::renderer::state::ffp::transform::parameters(
						sanguis::client::draw2d::scene::translation_matrix(
							_translation
						)
					)
				)
			);

			sge::renderer::state::ffp::transform::scoped const scoped_transform(
				_render_context,
				sge::renderer::state::ffp::transform::mode::world,
				*transform_state
			);

			world_->draw(
				_render_context,
				_translation
			);

			fcppt::maybe_void(
				this->player_center(),
				[
					&_render_context,
					_translation,
					this
				](
					sanguis::client::draw2d::player_center const _player_center
				)
				{
					for(
						auto const index
						:
						fcppt::make_enum_range<
							sanguis::client::draw2d::z_ordering
						>()
					)
					{
						sanguis::client::draw2d::scene::state::optional_scoped_unique_ptr const state(
							render_states_[
								index
							]->create_scoped(
								_render_context
							)
						);

						normal_system_.render(
							_render_context,
							index
						);

						world_->draw_after(
							sanguis::client::draw2d::scene::world::render_parameters{
								_render_context,
								_player_center,
								_translation,
								index
							}
						);
					}
				}
			);

			fcppt::maybe_void(
				hover_,
				[
					&_render_context
				](
					sanguis::client::draw2d::scene::hover::base_unique_ptr const &_hover
				)
				{
					_hover->draw(
						_render_context
					);
				}
			);
		},
		sge::sprite::projection_matrix(
			renderer_.onscreen_target().viewport()
		),
		camera_->translation()
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

sanguis::client::control::optional_attack_dest const
sanguis::client::draw2d::scene::object::translate_attack_dest(
	sanguis::client::control::cursor_position const _cursor_position
) const
{
	return
		camera_->translate_attack_dest(
			_cursor_position
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
		throw
			sanguis::exception{
				(
					fcppt::format(
						FCPPT_TEXT("draw: Tried to insert object with id %1% twice!")
					)
					% _id
				).str()
			};

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
					sanguis::client::draw2d::sprite::center::value_type,
					fcppt::cast::float_to_int_fun
				>(
					_pos
				)
			)
		)
	)
		return;

	fcppt::maybe_void(
		_entity.hover(),
		[
			&_entity,
			this
		](
			sanguis::client::draw2d::entities::hover::info const &_info
		)
		{
			hover_ =
				optional_hover_unique_ptr{
					sanguis::client::draw2d::scene::hover::create(
						sanguis::client::draw2d::scene::hover::parameters(
							gui_style_,
							*gui_renderer_,
							renderer_,
							font_,
							hud_resources_,
							player_weapons_,
							_entity.center(),
							_entity.radius()
						),
						_info
					)
				};
		}
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

	if(
		sanguis::optional_entity_id(
			_id
		)
		==
		player_id_
	)
		player_id_ =
			sanguis::optional_entity_id();
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::object::entity(
	sanguis::entity_id const _id
) const
{
	return
		*fcppt::optional_to_exception(
			fcppt::container::find_opt_mapped(
				entities_,
				_id
			),
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

sanguis::client::draw2d::optional_player_center const
sanguis::client::draw2d::scene::object::player_center() const
{
	return
		fcppt::optional_bind_construct(
			player_id_,
			[
				this
			](
				sanguis::entity_id const _player_id
			)
			{
				return
					sanguis::client::draw2d::player_center{
						this->entity(
							_player_id
						).center()
					};
			}
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
		_parameters
	);
}

sanguis::client::draw2d::entities::load_parameters const
sanguis::client::draw2d::scene::object::load_parameters()
{
	return
		sanguis::client::draw2d::entities::load_parameters{
			diff_clock_,
			random_generator_,
			sound_manager_,
			normal_system_,
			model_collection_
		};
}

sanguis::client::draw2d::insert_own_callback
sanguis::client::draw2d::scene::object::insert_own_callback()
{
	return
		sanguis::client::draw2d::insert_own_callback(
			std::bind(
				&sanguis::client::draw2d::scene::object::insert_own,
				this,
				std::placeholders::_1
			)
		);
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::add_aoe_projectile const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::aoe_projectile(
			this->load_parameters(),
			this->insert_own_callback(),
			_message.get<
				sanguis::messages::roles::aoe_projectile_type
			>(),
			sanguis::client::draw2d::translate::speed(
				_message
			),
			sanguis::client::draw2d::translate::center(
				_message
			),
			sanguis::client::draw2d::translate::rotation(
				_message
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

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::add_aura const &_message
)
{
	fcppt::cast::dynamic<
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

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::add_buff const &_message
)
{
	fcppt::cast::dynamic<
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

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::add_destructible const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::destructible(
			this->load_parameters(),
			sanguis::client::draw2d::translate::center(
				_message
			),
			sanguis::client::draw2d::translate::rotation(
				_message
			),
			_message.get<
				sanguis::messages::roles::destructible_type
			>()
		),
		_message
	);
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::add_doodad const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::doodad(
			this->load_parameters(),
			sanguis::client::draw2d::translate::center(
				_message
			),
			sanguis::client::draw2d::translate::rotation(
				_message
			),
			_message.get<
				sanguis::messages::roles::doodad_type
			>()
		),
		_message
	);
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::add_enemy const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::enemy(
			this->load_parameters(),
			aura_resources_,
			_message.get<
				sanguis::messages::roles::enemy_type
			>(),
			_message.get<
				sanguis::messages::roles::enemy_kind
			>(),
			_message.get<
				sanguis::messages::roles::primary_weapon
			>(),
			_message.get<
				sanguis::messages::roles::weapon_status
			>(),
			sanguis::client::draw2d::translate::speed(
				_message
			),
			sanguis::client::draw2d::translate::center(
				_message
			),
			sanguis::client::draw2d::translate::rotation(
				_message
			),
			_message.get<
				sanguis::messages::roles::aura_type_container
			>(),
			_message.get<
				sanguis::messages::roles::buff_type_container
			>(),
			sanguis::client::draw2d::entities::name(
				sge::charconv::utf8_string_to_fcppt(
					_message.get<
						sanguis::messages::roles::name
					>()
				)
			),
			sanguis::client::draw2d::translate::health_pair(
				_message
			)
		),
		_message
	);
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::add_friend const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::friend_(
			this->load_parameters(),
			aura_resources_,
			_message.get<
				sanguis::messages::roles::friend_type
			>(),
			_message.get<
				sanguis::messages::roles::primary_weapon
			>(),
			_message.get<
				sanguis::messages::roles::weapon_status
			>(),
			sanguis::client::draw2d::translate::speed(
				_message
			),
			sanguis::client::draw2d::translate::center(
				_message
			),
			sanguis::client::draw2d::translate::rotation(
				_message
			),
			_message.get<
				sanguis::messages::roles::aura_type_container
			>(),
			_message.get<
				sanguis::messages::roles::buff_type_container
			>(),
			sanguis::client::draw2d::translate::health_pair(
				_message
			)
		),
		_message
	);
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::add_own_player const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::own_player(
			aura_resources_,
			this->load_parameters(),
			world_->collide_callback(),
			player_health_callback_,
			_message.get<
				sanguis::messages::roles::primary_weapon
			>(),
			_message.get<
				sanguis::messages::roles::weapon_status
			>(),
			sanguis::client::draw2d::translate::speed(
				_message
			),
			sanguis::client::draw2d::translate::center(
				_message
			),
			sanguis::client::draw2d::translate::rotation(
				_message
			),
			_message.get<
				sanguis::messages::roles::aura_type_container
			>(),
			_message.get<
				sanguis::messages::roles::buff_type_container
			>(),
			sanguis::client::draw2d::translate::health_pair(
				_message
			)
		),
		_message
	);

	player_id_ =
		sanguis::optional_entity_id(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		);
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::add_pickup const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::pickup(
			this->load_parameters(),
			_message.get<
				sanguis::messages::roles::pickup_type
			>(),
			sanguis::client::draw2d::translate::center(
				_message
			),
			sanguis::client::draw2d::translate::rotation(
				_message
			)
		),
		_message
	);
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::add_player const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::player(
			aura_resources_,
			this->load_parameters(),
			_message.get<
				sanguis::messages::roles::primary_weapon
			>(),
			_message.get<
				sanguis::messages::roles::weapon_status
			>(),
			sanguis::client::draw2d::translate::speed(
				_message
			),
			sanguis::client::draw2d::translate::center(
				_message
			),
			sanguis::client::draw2d::translate::rotation(
				_message
			),
			_message.get<
				sanguis::messages::roles::aura_type_container
			>(),
			_message.get<
				sanguis::messages::roles::buff_type_container
			>(),
			sanguis::client::draw2d::translate::health_pair(
				_message
			),
			sanguis::client::draw2d::entities::name(
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

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::add_projectile const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::projectile(
			this->load_parameters(),
			_message.get<
				sanguis::messages::roles::projectile_type
			>(),
			sanguis::client::draw2d::translate::speed(
				_message
			),
			sanguis::client::draw2d::translate::center(
				_message
			),
			sanguis::client::draw2d::translate::rotation(
				_message
			)
		),
		_message
	);
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::add_weapon_pickup const &_message
)
{
	this->configure_new_object(
		sanguis::client::draw2d::factory::weapon_pickup(
			this->load_parameters(),
			sanguis::client::draw2d::translate::center(
				_message
			),
			sanguis::client::draw2d::translate::rotation(
				_message
			),
			sanguis::client::weapon_description_from_message(
				_message
			)
		),
		_message
	);
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::change_weapon const &_message
)
{
	fcppt::cast::dynamic<
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

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::change_world const &_message
)
{
	camera_->reset_translation();

	this->change_world(
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
				fcppt::algorithm::enum_array_fold_static<
					sanguis::creator::opening_count_array
				>(
					[
						&_message
					](
						sanguis::creator::opening_type const _opening_type
					)
					{
						return
							sanguis::creator::opening_count(
								_message.get<
									sanguis::messages::roles::opening_count
								>()[
									_opening_type
								]
							);
					}
				),
				sanguis::creator::spawn_boss{
					_message.get<
						sanguis::messages::roles::spawn_boss
					>()
				}
			)
		)
	);
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::die const &_message
)
{
	this->entity(
		_message.get<
			sanguis::messages::roles::entity_id
		>()
	).die();
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::give_weapon const &_message
)
{
	player_weapons_.add(
		sanguis::client::weapon_description_from_message(
			_message
		)
	);
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::health const &_message
)
{
	fcppt::cast::dynamic<
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

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::level_up const &_message
)
{
	if(
		_message.get<
			sanguis::messages::roles::level
		>()
		>
		fcppt::literal<
			sanguis::messages::types::level
		>(
			0
		)
	)
		fcppt::maybe_void(
			this->player_center(),
			[
				this
			](
				sanguis::client::draw2d::player_center const _center
			)
			{
				this->insert_own(
					sanguis::client::draw2d::factory::text(
						diff_clock_,
						normal_system_,
						font_,
						SGE_FONT_LIT("Level up"),
						_center.get(),
						sanguis::client::draw2d::sprite::normal::white()
					)
				);
			}
		);
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::max_health const &_message
)
{
	fcppt::cast::dynamic<
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

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::move const &_message
)
{
	fcppt::cast::dynamic<
		sanguis::client::draw2d::entities::ifaces::with_center &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).center(
		sanguis::client::draw2d::translate::center(
			_message
		)
	);
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::remove const &_message
)
{
	this->remove(
		_message.get<
			sanguis::messages::roles::entity_id
		>()
	);
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::remove_buff const &_message
)
{
	fcppt::cast::dynamic<
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

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::remove_weapon const &_message
)
{
	player_weapons_.remove(
		_message.get<
			sanguis::messages::roles::is_primary_weapon
		>()
	);
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::rotate const &_message
)
{
	fcppt::cast::dynamic<
		sanguis::client::draw2d::entities::ifaces::with_orientation &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).orientation(
		sanguis::client::draw2d::translate::rotation(
			_message
		)
	);
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::speed const &_message
)
{
	fcppt::cast::dynamic<
		sanguis::client::draw2d::entities::ifaces::with_speed &
	>(
		this->entity(
			_message.get<
				sanguis::messages::roles::entity_id
			>()
		)
	).speed(
		sanguis::client::draw2d::translate::speed(
			_message
		)
	);
}

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::operator()(
	sanguis::messages::server::weapon_status const &_message
)
{
	fcppt::cast::dynamic<
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

sanguis::client::draw2d::scene::object::result_type
sanguis::client::draw2d::scene::object::process_default_msg(
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
	typename Message
>
void
sanguis::client::draw2d::scene::object::configure_new_object(
	sanguis::client::draw2d::entities::unique_ptr &&_ptr,
	Message const &_message
)
{
	sanguis::client::draw2d::entities::base &inserted(
		this->insert(
			std::move(
				_ptr
			),
			majutsu::get<
				sanguis::messages::roles::entity_id
			>(
				_message
			)
		)
	);

	if(
		majutsu::get<
			sanguis::messages::roles::created
		>(
			_message
		)
	)
		inserted.on_create(
			sanguis::client::draw2d::entities::create_parameters{
				this->insert_own_callback(),
				this->load_parameters(),
				world_->background_tile(
					sanguis::client::draw2d::scene::world::center_to_grid_pos(
						inserted.center()
					)
				)
			}
		);
}
