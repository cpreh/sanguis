#ifndef SANGUIS_CLIENT_DRAW2D_WITH_ORIENTATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_WITH_ORIENTATION_HPP_INCLUDED

#include "base.hpp"
#include "../sprite/rotation_type.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class with_orientation
:
	public virtual base
{
protected:
	with_orientation();

	virtual ~with_orientation();
public:
	virtual void
	orientation(
		sprite::rotation_type
	) = 0;

	virtual sprite::rotation_type
	orientation() const = 0;
};

}
}
}
}

#endif
