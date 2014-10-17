#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_OBJECT_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/collide_parameters_fwd.hpp>
#include <sanguis/client/draw2d/optional_speed_fwd.hpp>
#include <sanguis/client/draw2d/optional_translation_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/object_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/state_fwd.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/client/load/tiles/context.hpp>
#include <sanguis/creator/optional_background_tile_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


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
		sanguis::random_generator &,
		sge::renderer::device::core &,
		sanguis::client::load::resource::textures const &,
		sanguis::client::draw::debug
	);

	~object();

	void
	draw(
		sge::renderer::context::core &
	);

	void
	translation(
		sanguis::client::draw2d::optional_translation
	);

	void
	change(
		sanguis::client::world_parameters const &,
		sanguis::client::draw2d::optional_translation
	);

	sanguis::client::draw2d::collide_callback const &
	collide_callback() const;

	sanguis::creator::optional_background_tile
	background_tile(
		sanguis::creator::pos
	) const;
private:
	sanguis::client::draw2d::optional_speed const
	test_collision(
		sanguis::client::draw2d::collide_parameters const &
	) const;

	sge::renderer::device::core &renderer_;

	sanguis::client::load::tiles::context tiles_context_;

	sanguis::client::draw2d::collide_callback const collide_callback_;

	sanguis::random_generator &random_generator_;

	sanguis::client::draw::debug const debug_;

	typedef
	std::unique_ptr<
		sanguis::client::draw2d::scene::world::state
	>
	state_unique_ptr;

	state_unique_ptr state_;

};

}
}
}
}
}

#endif
