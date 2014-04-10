#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_CONTROL_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_CONTROL_ENVIRONMENT_HPP_INCLUDED

#include <sanguis/client/control/cursor_position_fwd.hpp>
#include <sanguis/client/control/environment.hpp>
#include <sanguis/client/control/optional_attack_dest_fwd.hpp>
#include <sanguis/client/control/optional_cursor_position.hpp>
#include <sanguis/client/draw2d/scene/control_environment_fwd.hpp>
#include <sanguis/client/draw2d/scene/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{

class control_environment
:
	public sanguis::client::control::environment
{
	FCPPT_NONCOPYABLE(
		control_environment
	);
public:
	explicit
	control_environment(
		sanguis::client::draw2d::scene::object &
	);

	~control_environment();
private:
	sanguis::client::control::optional_attack_dest const
	translate_attack_dest(
		sanguis::client::control::cursor_position const &
	) const
	override;

	sanguis::client::control::optional_cursor_position const
	position() const;

	void
	update_position(
		sanguis::client::control::optional_cursor_position const &
	)
	override;

	sanguis::client::draw2d::scene::object &object_;

	sanguis::client::control::optional_cursor_position position_;
};

}
}
}
}

#endif
