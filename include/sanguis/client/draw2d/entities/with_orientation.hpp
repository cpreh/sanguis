#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_ORIENTATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_ORIENTATION_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class with_orientation
{
	FCPPT_NONCOPYABLE(
		with_orientation
	);
protected:
	with_orientation();

	virtual ~with_orientation();
public:
	virtual void
	orientation(
		sprite::rotation
	) = 0;

	virtual sprite::rotation
	orientation() const = 0;
};

}
}
}
}

#endif
