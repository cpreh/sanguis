#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_VISIBILITY_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_VISIBILITY_HPP_INCLUDED

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class with_visibility
{
protected:
	with_visibility();

	virtual ~with_visibility();
public:
	virtual void
	visible(
		bool
	) = 0;
};

}
}
}
}

#endif
