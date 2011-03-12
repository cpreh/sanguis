#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_SENTRY_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_SENTRY_HPP_INCLUDED

#include "model/object.hpp"
#include "model/parameters_fwd.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class sentry
:
	public model::object
{
public:
	explicit sentry(
		model::parameters const &
	);
	
	void
	orientation(
		sprite::rotation_type
	);
private:
	using container::orientation;
};

}
}
}
}

#endif
