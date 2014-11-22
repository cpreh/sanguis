#ifndef SANGUIS_SERVER_ENTITIES_IFACES_WITH_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_IFACES_WITH_HEALTH_HPP_INCLUDED

#include <sanguis/server/health_fwd.hpp>
#include <sanguis/server/entities/property/changeable_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
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
public:
	virtual
	~with_health() = 0;

	virtual
	sanguis::server::entities::property::changeable &
	health() = 0;

	virtual
	sanguis::server::health const
	current_health() const = 0;

	virtual
	sanguis::server::health const
	max_health() const = 0;

	virtual
	void
	kill() = 0;
};

}
}
}
}

#endif
