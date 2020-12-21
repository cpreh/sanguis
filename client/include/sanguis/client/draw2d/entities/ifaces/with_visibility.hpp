#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_VISIBILITY_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_VISIBILITY_HPP_INCLUDED

#include <fcppt/nonmovable.hpp>


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

class with_visibility
{
	FCPPT_NONMOVABLE(
		with_visibility
	);
protected:
	with_visibility();

	virtual
	~with_visibility();
public:
	virtual
	void
	visible(
		bool
	) = 0;
};

}
}
}
}
}

#endif
