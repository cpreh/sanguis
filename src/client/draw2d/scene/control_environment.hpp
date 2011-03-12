#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_CONTROL_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_CONTROL_ENVIRONMENT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "../../control/environment.hpp"
#include "../../control/direction_vector.hpp"
#include "../../control/key_scale.hpp"
#include "../../cursor/object_ptr.hpp"
#include <fcppt/math/vector/basic_decl.hpp>
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
		object &,
		client::cursor::object_ptr
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

	void
	update_direction(
		client::control::key_scale &ref,
		client::control::key_scale diff
	);

	scene::object &object_;

	client::cursor::object_ptr const cursor_;

	client::control::direction_vector direction_;
};

}
}
}
}

#endif
