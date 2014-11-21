#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_STATE_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/collide_parameters_fwd.hpp>
#include <sanguis/client/draw2d/optional_speed_fwd.hpp>
#include <sanguis/client/draw2d/optional_translation.hpp>
#include <sanguis/client/draw2d/player_center_fwd.hpp>
#include <sanguis/client/draw2d/z_ordering_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/base_unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/world/batch_grid.hpp>
#include <sanguis/client/draw2d/scene/world/parameters_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/state_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/buffers.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/state.hpp>
#include <sanguis/client/load/tiles/context_fwd.hpp>
#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/name_fwd.hpp>
#include <sanguis/creator/optional_background_tile_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/top_result_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/noncopyable.hpp>


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

class state
{
	FCPPT_NONCOPYABLE(
		state
	);
public:
	state(
		sanguis::random_generator &,
		sge::renderer::device::core &,
		sanguis::client::load::tiles::context &,
		sanguis::client::draw::debug,
		sanguis::client::world_parameters const &,
		sanguis::client::draw2d::optional_translation,
		sanguis::client::draw2d::scene::world::parameters const &
	);

	~state();

	void
	draw(
		sge::renderer::context::core &
	);

	void
	draw_after(
		sge::renderer::context::core &,
		sanguis::client::draw2d::player_center,
		sanguis::client::draw2d::z_ordering
	);

	void
	translation(
		sanguis::client::draw2d::optional_translation
	);

	sanguis::client::draw2d::optional_speed const
	test_collision(
		sanguis::client::draw2d::collide_parameters const &
	) const;

	sanguis::creator::optional_background_tile
	background_tile(
		sanguis::creator::pos
	) const;
private:
	state(
		sanguis::random_generator &,
		sge::renderer::device::core &,
		sanguis::client::load::tiles::context &,
		sanguis::client::draw::debug,
		sanguis::creator::top_result const &,
		sanguis::client::draw2d::optional_translation,
		sanguis::creator::name const &,
		sanguis::client::draw2d::scene::world::parameters const &
	);

	sge::renderer::device::core &renderer_;

	sanguis::client::draw2d::scene::world::sprite::buffers sprite_buffers_;

	sanguis::client::draw2d::scene::world::sprite::state sprite_state_;

	sanguis::creator::grid const grid_;

	sanguis::creator::background_grid const background_grid_;

	sanguis::client::draw2d::scene::world::batch_grid const batches_;

	sanguis::client::draw2d::optional_translation translation_;

	sanguis::client::draw2d::scene::world::base_unique_ptr const effects_;
};

}
}
}
}
}

#endif
