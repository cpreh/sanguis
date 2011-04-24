#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_SENTRY_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_SENTRY_HPP_INCLUDED

#include "model/object.hpp"
#include "model/parameters_fwd.hpp"
#include "../sprite/rotation.hpp"
#include <fcppt/noncopyable.hpp>

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
	FCPPT_NONCOPYABLE(
		sentry
	);
public:
	explicit sentry(
		model::parameters const &
	);

	~sentry();
	
	void
	orientation(
		sprite::rotation
	);
private:
	using container::orientation;
};

}
}
}
}

#endif
