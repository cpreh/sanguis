#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_CAMERA_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_CAMERA_HPP_INCLUDED

#include <sanguis/client/slowed_duration_fwd.hpp>
#include <sanguis/client/control/cursor_position_fwd.hpp>
#include <sanguis/client/control/optional_attack_dest_fwd.hpp>
#include <sanguis/client/draw2d/optional_player_center_fwd.hpp>
#include <sanguis/client/draw2d/optional_translation.hpp>
#include <sanguis/client/draw2d/optional_vector2.hpp>
#include <sanguis/client/draw2d/scene/camera_fwd.hpp>
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

class camera
{
	FCPPT_NONCOPYABLE(
		camera
	);
public:
	explicit
	camera(
		sge::renderer::device::core &
	);

	~camera();

	void
	update(
		sanguis::client::slowed_duration,
		sanguis::client::draw2d::optional_player_center
	);

	void
	reset_translation();

	sanguis::client::draw2d::optional_translation const
	translation() const;

	sanguis::client::control::optional_attack_dest const
	translate_attack_dest(
		sanguis::client::control::cursor_position
	);
private:
	sge::renderer::device::core &renderer_;

	sanguis::client::draw2d::optional_translation desired_translation_;

	sanguis::client::draw2d::optional_vector2 translation_;
};

}
}
}
}

#endif
