#ifndef SANGUIS_SERVER_PERKS_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_HEALTH_HPP_INCLUDED

#include "perk.hpp"
#include "level_type.hpp"
#include "level_diff.hpp"
#include "../entities/base_fwd.hpp"
#include "../entities/property/value.hpp"

namespace sanguis
{
namespace server
{
namespace perks
{

class health
:
	public perk
{
public:
	health();
private:
	void
	change(
		entities::base &,
		level_diff
	);

	bool
	can_raise_level() const;

	static
	entities::property::value const
	factor(
		level_type
	);
};

}
}
}

#endif
