#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_CENTER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_CENTER_HPP_INCLUDED

#include "../sprite/center.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class with_center
{
	FCPPT_NONCOPYABLE(
		with_center
	);
protected:
	with_center();

	virtual ~with_center();
public:
	virtual void
	center(
		sprite::center const &
	) = 0;

	virtual sprite::center const
	center() const = 0;
};

}
}
}
}

#endif
