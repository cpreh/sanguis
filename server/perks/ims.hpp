#ifndef SANGUIS_SERVER_PERKS_IMS_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_IMS_HPP_INCLUDED

#include "perk.hpp"
#include "../space_unit.hpp"

namespace sanguis
{
namespace server
{
namespace perks
{

class ims
:
	public perk
{
public:
	ims();
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
