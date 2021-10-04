#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_VISIBILITY_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_VISIBILITY_HPP_INCLUDED

#include <fcppt/nonmovable.hpp>


namespace sanguis::client::draw2d::entities::ifaces
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

#endif
