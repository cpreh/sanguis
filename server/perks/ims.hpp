#ifndef SANGUIS_SERVER_PERKS_IMS_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_IMS_HPP_INCLUDED

#include "perk.hpp"
#include "level_diff.hpp"
#include "level_type.hpp"
#include "../entities/base_fwd.hpp"

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
	change(
		entities::base &,
		level_diff
	);
	
	level_type
	max_level() const;
};

}
}
}

#endif
