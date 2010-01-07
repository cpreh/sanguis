#ifndef SANGUIS_CLIENT_DRAW2D_WITH_SPEED_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_WITH_SPEED_HPP_INCLUDED

#include "base.hpp"
#include "../vector2.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class with_speed
:
	public virtual base
{
protected:
	with_speed();

	virtual ~with_speed();
public:
	virtual void
	speed(
		vector2 const &
	) = 0;

	virtual vector2 const 
	speed() const = 0;
};

}
}
}
}

#endif
