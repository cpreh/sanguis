#ifndef SANGUIS_CLIENT_CONTROL_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ENVIRONMENT_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "direction_vector.hpp"
#include "key_scale.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace control
{

class environment
{
	FCPPT_NONCOPYABLE(
		environment
	);
protected:
	environment();
public:
	virtual direction_vector const 
	direction() const = 0;

	virtual direction_vector const
	attack_dest() const = 0;

	virtual key_scale
	rotation() const = 0;

	virtual void
	direction_x(
		key_scale
	) = 0;

	virtual void
	direction_y(
		key_scale
	) = 0;

	virtual ~environment();
};

}
}
}

#endif
