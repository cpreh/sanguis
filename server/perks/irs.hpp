#ifndef SANGUIS_SERVER_PERKS_IRS_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_IRS_HPP_INCLUDED

#include "perk.hpp"

namespace sanguis
{
namespace server
{
namespace perks
{

class irs
:
	public perk
{
public:
	irs();
private:
	void
	do_apply(
		entities::base &,
		time_type,
		environment::object_ptr
	);

	bool
	can_raise_level() const;
};

}
}
}

#endif
