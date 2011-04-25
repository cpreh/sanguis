#ifndef SANGUIS_SERVER_ENTITIES_WITH_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_HEALTH_HPP_INCLUDED

#include "with_health_fwd.hpp"
#include "base.hpp"
#include "property/changeable.hpp"
#include "property/always_max.hpp"
#include "property/value.hpp"
#include "../health.hpp"
#include "../damage/unit.hpp"
#include "../damage/array.hpp"
#include "../damage/armor.hpp"
#include "../../time_delta_fwd.hpp"
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class with_health
:
	public virtual base 
{
	FCPPT_NONCOPYABLE(
		with_health
	);
public:
	void
	damage(
		damage::unit,
		damage::array const &
	);

	void
	kill();

	property::changeable &
	health();

	property::always_max &
	regeneration();

	server::health const
	current_health() const;

	server::health const
	max_health() const;
protected:
	with_health(
		server::health max,
		damage::armor const &
	);

	~with_health();

	void
	on_update(
		sanguis::time_delta const &
	);
private:
	bool
	dead() const;

	void
	max_health_change(
		property::value
	);

	damage::armor armor_;

	property::changeable health_;

	property::always_max regeneration_;
	
	fcppt::signal::scoped_connection const max_health_change_;
};

}
}
}

#endif

