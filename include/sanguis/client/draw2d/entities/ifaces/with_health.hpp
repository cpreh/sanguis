#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_HEALTH_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_HEALTH_HPP_INCLUDED

#include <sanguis/client/health.hpp>
#include <sanguis/client/max_health.hpp>
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

class with_health
{
	FCPPT_NONCOPYABLE(
		with_health
	);
protected:
	with_health();

	virtual
	~with_health() = 0;
public:
	virtual
	void
	health(
		sanguis::client::health
	) = 0;

	virtual
	void
	max_health(
		sanguis::client::max_health
	) = 0;

	virtual
	sanguis::client::health const
	health() const = 0;

	virtual
	sanguis::client::max_health const
	max_health() const = 0;
};

}
}
}
}
}

#endif
