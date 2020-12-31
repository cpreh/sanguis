#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_CAMERA_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_CAMERA_HPP_INCLUDED

#include <sanguis/client/slowed_duration_fwd.hpp>
#include <sanguis/client/control/cursor_position_fwd.hpp>
#include <sanguis/client/control/optional_attack_dest_fwd.hpp>
#include <sanguis/client/draw2d/optional_player_center_fwd.hpp>
#include <sanguis/client/draw2d/optional_translation.hpp>
#include <sanguis/client/draw2d/optional_vector2.hpp>
#include <sanguis/client/draw2d/scene/camera_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <fcppt/nonmovable.hpp>


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
	FCPPT_NONMOVABLE(
		camera
	);
public:
	explicit
	camera(
		sge::renderer::device::core_ref
	);

	~camera(); // NOLINT(performance-trivially-destructible)

	void
	update(
		sanguis::client::slowed_duration,
		sanguis::client::draw2d::optional_player_center const &
	);

	void
	reset_translation();

	[[nodiscard]]
	sanguis::client::draw2d::optional_translation
	translation() const;

	[[nodiscard]]
	sanguis::client::control::optional_attack_dest
	translate_attack_dest(
		sanguis::client::control::cursor_position const &
	) const;
private:
	sge::renderer::device::core_ref const renderer_;

	sanguis::client::draw2d::optional_translation desired_translation_;

	sanguis::client::draw2d::optional_vector2 translation_;
};

}
}
}
}

#endif
