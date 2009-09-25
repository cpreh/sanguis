#ifndef SANGUIS_SERVER_ENTITIES_WITH_PERKS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_PERKS_HPP_INCLUDED

#include "base.hpp"
#include "base_parameters_fwd.hpp"
#include "../perks/perk.hpp"
#include "../../perk_type.hpp"
#include <boost/ptr_container/ptr_map.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class with_perks
:
	public virtual base
{
protected:
	explicit with_perks(
		base_parameters const &
	);
private:
	typedef boost::ptr_map<
		perk_type::type,
		perks::perk
	> perk_container;

	perk_container perks_;
};

}
}
}

#endif
