#ifndef SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED

#include "base.hpp"
#include "base_parameters_fwd.hpp"
#include "../buffs/buff.hpp"
#include "../damage/array.hpp"
#include "../space_unit.hpp"
#include <boost/ptr_container/ptr_list.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class with_buffs
:
	public virtual base
{
protected:
	explicit with_buffs(
		base_parameters const &
	);
private:
	void
	damage(
		space_unit,
		damage::array const &
	);

	typedef boost::ptr_list<
		buffs::buff
	> buff_container;

	buff_container buffs_;
};

}
}
}

#endif
