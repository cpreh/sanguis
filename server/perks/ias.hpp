#ifndef SANGUIS_SERVER_PERKS_IAS_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_IAS_HPP_INCLUDED

#include "perk.hpp"
#include "../entities/base_fwd.hpp"
#include "../entities/property/value.hpp"

namespace sanguis
{
namespace server
{
namespace perks
{

class ias
:
	public perk
{
public:
	ias();
private:
	void
	apply(
		entities::base &
	);

	void
	unapply(
		entities::base &
	);

	bool
	can_raise_level() const;

	entities::property::value const
	factor() const;
};

}
}
}

#endif
