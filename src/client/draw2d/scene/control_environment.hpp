#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_CONTROL_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_CONTROL_ENVIRONMENT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "../../control/attack_dest.hpp"
#include "../../control/cursor_position.hpp"
#include "../../control/environment.hpp"
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
	public client::control::environment
{
	FCPPT_NONCOPYABLE(
		control_environment
	);
public:
	explicit control_environment(
		draw2d::scene::object &
	);

	~control_environment();

	client::control::attack_dest const
	translate_attack_dest(
		client::control::cursor_position const &
	) const;
private:
	draw2d::scene::object &object_;
};

}
}
}
}

#endif
