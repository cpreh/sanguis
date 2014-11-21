#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/collide_parameters_fwd.hpp>
#include <sanguis/client/draw2d/optional_speed.hpp>
#include <sanguis/client/draw2d/optional_translation.hpp>
#include <sanguis/client/draw2d/player_center.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/scene/world/object.hpp>
#include <sanguis/client/draw2d/scene/world/parameters.hpp>
#include <sanguis/client/draw2d/scene/world/state.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/creator/optional_background_tile.hpp>
#include <sanguis/creator/pos.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::world::object::object(
	sanguis::random_generator &_random_generator,
	sge::renderer::device::core &_renderer,
	sanguis::client::load::resource::textures const &_textures,
	sanguis::client::draw2d::scene::world::parameters const &_parameters,
	sanguis::client::draw::debug const _debug
)
:
	renderer_(
		_renderer
	),
	tiles_context_(
		_textures
	),
	collide_callback_(
		std::bind(
			&sanguis::client::draw2d::scene::world::object::test_collision,
			this,
			std::placeholders::_1
		)
	),
	random_generator_(
		_random_generator
	),
	parameters_(
		_parameters
	),
	debug_{
		_debug
	},
	state_()
{
}

sanguis::client::draw2d::scene::world::object::~object()
{
}

void
sanguis::client::draw2d::scene::world::object::draw(
	sge::renderer::context::core &_render_context
)
{
	if(
		state_
	)
		state_->draw(
			_render_context
		);
}

void
sanguis::client::draw2d::scene::world::object::draw_after(
	sge::renderer::context::core &_render_context,
	sanguis::client::draw2d::player_center const _player_center,
	sanguis::client::draw2d::z_ordering const _z_ordering
)
{
	if(
		state_
	)
		state_->draw_after(
			_render_context,
			_player_center,
			_z_ordering
		);
}

void
sanguis::client::draw2d::scene::world::object::translation(
	sanguis::client::draw2d::optional_translation const _translation
)
{
	if(
		state_
	)
		state_->translation(
			_translation
		);
}

void
sanguis::client::draw2d::scene::world::object::change(
	sanguis::client::world_parameters const &_parameters,
	sanguis::client::draw2d::optional_translation const _translation
)
{
	state_ =
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::scene::world::state
		>(
			random_generator_,
			renderer_,
			tiles_context_,
			debug_,
			_parameters,
			_translation,
			parameters_
		);
}

sanguis::client::draw2d::collide_callback const &
sanguis::client::draw2d::scene::world::object::collide_callback() const
{
	return
		collide_callback_;
}

sanguis::creator::optional_background_tile
sanguis::client::draw2d::scene::world::object::background_tile(
	sanguis::creator::pos const _pos
) const
{
	FCPPT_ASSERT_PRE(
		state_
	);

	return
		state_->background_tile(
			_pos
		);
}

sanguis::client::draw2d::optional_speed const
sanguis::client::draw2d::scene::world::object::test_collision(
	sanguis::client::draw2d::collide_parameters const &_parameters
) const
{
	FCPPT_ASSERT_PRE(
		state_
	);

	return
		state_->test_collision(
			_parameters
		);
}
