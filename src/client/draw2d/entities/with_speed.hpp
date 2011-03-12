#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_SPEED_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_SPEED_HPP_INCLUDED

#include "../vector2.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class with_speed
{
	FCPPT_NONCOPYABLE(
		with_speed
	);
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
