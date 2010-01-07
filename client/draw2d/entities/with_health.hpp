#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_HEALTH_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_HEALTH_HPP_INCLUDED

#include "base.hpp"
#include "../../health_type.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class with_health
:
	public virtual base
{
protected:
	with_health();

	virtual ~with_health();
public:
	virtual void
	health(
		health_type
	) = 0;

	virtual void
	max_health(
		health_type
	) = 0;

	virtual health_type 
	health() const = 0;

	virtual health_type 
	max_health() const = 0;
};

}
}
}
}

#endif
