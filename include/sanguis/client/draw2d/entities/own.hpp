#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/own_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class own
{
	FCPPT_NONCOPYABLE(
		own
	);
protected:
	own();
public:
	virtual void
	update() = 0;

	virtual bool
	may_be_removed() const = 0;

	virtual ~own();
};

}
}
}
}

#endif
