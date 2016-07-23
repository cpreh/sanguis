#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_OBJECT_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/slowed_duration_fwd.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/collide_parameters_fwd.hpp>
#include <sanguis/client/draw2d/optional_speed_fwd.hpp>
#include <sanguis/client/draw2d/translation_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/object_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/parameters.hpp>
#include <sanguis/client/draw2d/scene/world/render_parameters_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/state_fwd.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/client/load/tiles/context.hpp>
#include <sanguis/creator/optional_background_tile_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace world
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		fcppt::log::context &,
		sanguis::random_generator &,
		sge::renderer::device::core &,
		sanguis::client::load::resource::textures const &,
		sanguis::client::draw2d::scene::world::parameters const &,
		sanguis::client::draw::debug
	);

	~object();

	void
	update(
		sanguis::client::slowed_duration
	);

	void
	draw(
		sge::renderer::context::core &,
		sanguis::client::draw2d::translation
	);

	void
	draw_after(
		sanguis::client::draw2d::scene::world::render_parameters const &
	);

	void
	change(
		sanguis::client::world_parameters const &
	);

	sanguis::client::draw2d::collide_callback const &
	collide_callback() const;

	sanguis::creator::optional_background_tile
	background_tile(
		sanguis::creator::pos
	) const;
private:
	sanguis::client::draw2d::optional_speed
	test_collision(
		sanguis::client::draw2d::collide_parameters const &
	) const;

	fcppt::log::context &log_context_;

	sge::renderer::device::core &renderer_;

	sanguis::client::load::tiles::context tiles_context_;

	sanguis::client::draw2d::collide_callback const collide_callback_;

	sanguis::random_generator &random_generator_;

	sanguis::client::draw2d::scene::world::parameters const parameters_;

	sanguis::client::draw::debug const debug_;

	typedef
	fcppt::unique_ptr<
		sanguis::client::draw2d::scene::world::state
	>
	state_unique_ptr;

	typedef
	fcppt::optional::object<
		state_unique_ptr
	>
	optional_state_unique_ptr;

	optional_state_unique_ptr state_;
};

}
}
}
}
}

#endif
