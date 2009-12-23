#ifndef SANGUIS_SERVER_ENTITIES_WITH_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_HEALTH_HPP_INCLUDED

#include "with_health_fwd.hpp"
#include "base.hpp"
#include "property/changeable.hpp"
#include "property/always_max.hpp"
#include "property/value.hpp"
#include "health_type.hpp"
#include "../health_type.hpp"
#include "../damage/unit.hpp"
#include "../damage/array.hpp"
#include "../damage/armor.hpp"
#include <fcppt/signal/scoped_connection.hpp>

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
public:
	void
	damage(
		damage::unit,
		damage::array const &
	);

	property::changeable &
	health();

	property::always_max &
	regeneration();

	server::health_type
	current_health() const;

	server::health_type
	max_health() const;
protected:
	with_health(
		entities::health_type max_health,
		damage::armor const &
	);

	void
	on_update(
		time_type
	);
private:
	bool
	dead() const;

	bool
	invulnerable() const;

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

