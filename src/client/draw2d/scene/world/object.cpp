#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/draw2d/vector2_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/object.hpp>
#include <sanguis/client/draw2d/scene/world/state.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/dim_fwd.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::world::object::object(
	sge::renderer::device::core &_renderer,
	sanguis::load::resource::textures const &_textures
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
			std::placeholders::_1,
			std::placeholders::_2
		)
	),
	state_()
{
}

sanguis::client::draw2d::scene::world::object::~object()
{
}

void
sanguis::client::draw2d::scene::world::object::draw(
	sge::renderer::context::core &_render_context,
	sanguis::client::draw2d::vector2 const &_translation
)
{
	if(
		state_
	)
		state_->draw(
			_render_context,
			_translation
		);
}

void
sanguis::client::draw2d::scene::world::object::change(
	sanguis::client::world_parameters const &_param
)
{
	state_.take(
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::scene::world::state
		>(
			renderer_,
			tiles_context_,
			_param
		)
	);
}

sanguis::client::draw2d::collide_callback const &
sanguis::client::draw2d::scene::world::object::collide_callback() const
{
	return collide_callback_;
}

bool
sanguis::client::draw2d::scene::world::object::test_collision(
	sanguis::client::draw2d::sprite::center const &_center,
	sanguis::client::draw2d::sprite::dim const &_dim
) const
{
	FCPPT_ASSERT_PRE(
		state_
	);

	return
		state_->test_collision(
			_center,
			_dim
		);
}
