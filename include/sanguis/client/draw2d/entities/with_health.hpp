#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_HEALTH_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_HEALTH_HPP_INCLUDED

#include <sanguis/client/health.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class with_health
{
	FCPPT_NONCOPYABLE(
		with_health
	);
protected:
	with_health();

	virtual ~with_health();
public:
	virtual void
	health(
		client::health
	) = 0;

	virtual void
	max_health(
		client::health
	) = 0;

	virtual client::health const
	health() const = 0;

	virtual client::health const
	max_health() const = 0;
};

}
}
}
}

#endif
