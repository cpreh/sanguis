#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/slowed_duration.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/collide_parameters_fwd.hpp>
#include <sanguis/client/draw2d/optional_speed.hpp>
#include <sanguis/client/draw2d/translation.hpp>
#include <sanguis/client/draw2d/scene/world/object.hpp>
#include <sanguis/client/draw2d/scene/world/parameters.hpp>
#include <sanguis/client/draw2d/scene/world/render_parameters_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/state.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/creator/optional_background_tile.hpp>
#include <sanguis/creator/pos.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::client::draw2d::scene::world::object::object(
	fcppt::log::context_reference const _log_context,
	sanguis::random_generator &_random_generator,
	sge::renderer::device::core &_renderer,
	sanguis::client::load::resource::textures const &_textures,
	sanguis::client::draw2d::scene::world::parameters const &_parameters,
	sanguis::client::draw::debug const _debug
)
:
	log_context_{
		_log_context
	},
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

FCPPT_PP_POP_WARNING

sanguis::client::draw2d::scene::world::object::~object()
{
}

void
sanguis::client::draw2d::scene::world::object::update(
	sanguis::client::slowed_duration const _slowed_duration
)
{
	fcppt::optional::maybe_void(
		state_,
		[
			_slowed_duration
		](
			state_unique_ptr const &_state
		)
		{
			_state->update(
				_slowed_duration
			);
		}
	);
}

void
sanguis::client::draw2d::scene::world::object::draw(
	sge::renderer::context::core &_render_context,
	sanguis::client::draw2d::translation const _translation
)
{
	fcppt::optional::maybe_void(
		state_,
		[
			&_render_context,
			_translation
		](
			state_unique_ptr const &_state
		)
		{
			_state->draw(
				_render_context,
				_translation
			);
		}
	);
}

void
sanguis::client::draw2d::scene::world::object::draw_after(
	sanguis::client::draw2d::scene::world::render_parameters const &_render_parameters
)
{
	fcppt::optional::maybe_void(
		state_,
		[
			&_render_parameters
		](
			state_unique_ptr const &_state
		)
		{
			_state->draw_after(
				_render_parameters
			);
		}
	);
}

void
sanguis::client::draw2d::scene::world::object::change(
	sanguis::client::world_parameters const &_parameters
)
{
	state_ =
		optional_state_unique_ptr();

	state_ =
		optional_state_unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::scene::world::state
			>(
				log_context_,
				random_generator_,
				renderer_,
				tiles_context_,
				debug_,
				_parameters,
				parameters_
			)
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
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			state_
		)->background_tile(
			_pos
		);
}

sanguis::client::draw2d::optional_speed
sanguis::client::draw2d::scene::world::object::test_collision(
	sanguis::client::draw2d::collide_parameters const &_parameters
) const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			state_
		)->test_collision(
			_parameters
		);
}
