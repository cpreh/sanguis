#ifndef SANGUIS_SERVER_ENTITIES_WITH_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_HEALTH_HPP_INCLUDED

#include "base.hpp"
#include "property.hpp"
#include "../damage/unit.hpp"
#include "../damage/array.hpp"
#include "../damage/armor.hpp"

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

	property &
	health();

	property &
	regeneration();
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
	bool
	dead() const;

	damage::armor armor_;

	property
		health_,
		health_regeneration_;
};

}
}
}

#endif

