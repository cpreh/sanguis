#ifndef SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED

#include "base.hpp"
#include "../buffs/buff_fwd.hpp"
#include "../buffs/auto_ptr.hpp"
#include "../../time_type.hpp"
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
public:
	void
	add_buff(
		buffs::auto_ptr
	);
protected:
	with_buffs();

	~with_buffs();
private:
	void
	on_update(
		time_type
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
