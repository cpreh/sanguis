#ifndef SANGUIS_CLIENT_DRAW2D_WITH_ORIENTATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_WITH_ORIENTATION_HPP_INCLUDED

#include "entity.hpp"
#include "sprite/rotation_type.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{

class with_orientation
:
	public virtual entity
{
protected:
	with_orientation();

	virtual ~with_orientation();
public:
	virtual void
	orientation(
		sprite::rotation_type
	) = 0;
};

}
}
}

#endif

