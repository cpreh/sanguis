#ifndef SANGUIS_SERVER_ENTITIES_WITH_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_HEALTH_HPP_INCLUDED

#include "with_health_fwd.hpp"
#include "base.hpp"
#include "property.hpp"
#include "../damage/unit.hpp"
#include "../damage/array.hpp"
#include "../damage/armor.hpp"
#include "../health_type.hpp"

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

	void
	die();

	property &
	health();

	property &
	regeneration();

	health_type
	current_health() const;

	health_type
	max_health() const;
protected:
	with_health(
		health_type max_health,
		damage::armor const &
	);

	void
	on_update(
		time_type
	);
private:
	virtual void
	on_die();

	bool
	dead() const;

	bool
	invulnerable() const;

	void
	max_health_change(
		property::value_type
	);

	damage::armor armor_;

	property
		health_,
		health_regeneration_;
};

}
}
}

#endif

