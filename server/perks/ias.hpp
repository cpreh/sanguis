#ifndef SANGUIS_SERVER_PERKS_IAS_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_IAS_HPP_INCLUDED

#include "perk.hpp"
#include "../space_unit.hpp"

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
	do_apply(
		entities::base &,
		time_type,
		environment::object_ptr
	);

	bool
	can_raise_level() const;

	space_unit
	factor() const;
};

}
}
}

#endif
