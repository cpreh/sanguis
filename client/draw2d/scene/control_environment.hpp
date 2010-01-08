#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_CONTROL_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_CONTROL_ENVIRONMENT_HPP_INCLUDED

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
	FCPPT_NONCOPYABLE(control_environment)
public:
	control_environment(
	);

	~control_environment();
private:
	client::control::direction_vector const 
	direction() const;

	client::control::direction_vector const
	attack_dest() const;

	client::control::key_scale
	rotation() const;

	void
	direction_x(
		client::control::key_scale
	); 

	void
	direction_y(
		client::control::key_scale
	);

	client::control::direction_vector direction_;
};

}
}
}
}

#endif

