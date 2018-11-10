#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_ORIENTATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_ORIENTATION_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/rotation_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace ifaces
{

class with_orientation
{
	FCPPT_NONCOPYABLE(
		with_orientation
	);
protected:
	with_orientation();

	virtual
	~with_orientation();
public:
	virtual
	void
	orientation(
		sanguis::client::draw2d::sprite::rotation
	) = 0;

	virtual
	sanguis::client::draw2d::sprite::rotation
	orientation() const = 0;
};

}
}
}
}
}

#endif
