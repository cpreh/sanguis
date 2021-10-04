#ifndef SANGUIS_SERVER_ENTITIES_IFACES_WITH_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_IFACES_WITH_HEALTH_HPP_INCLUDED

#include <sanguis/server/health_fwd.hpp>
#include <sanguis/server/entities/property/changeable_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::entities::ifaces
{

class with_health
{
	FCPPT_NONMOVABLE(
		with_health
	);
protected:
	with_health();
public:
	virtual
	~with_health();

	[[nodiscard]]
	virtual
	sanguis::server::entities::property::changeable &
	health() = 0;

	[[nodiscard]]
	virtual
	sanguis::server::health
	current_health() const = 0;

	[[nodiscard]]
	virtual
	sanguis::server::health
	max_health() const = 0;

	virtual
	void
	kill() = 0;
};

}

#endif
