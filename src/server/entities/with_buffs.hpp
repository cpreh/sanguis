#ifndef SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED

#include "with_buffs_fwd.hpp"
#include "base.hpp"
#include "../buffs/list.hpp"
#include "../buffs/buff.hpp" // for buffs::list
#include "../buffs/unique_ptr.hpp"
#include "../../time_type.hpp"
#include <fcppt/noncopyable.hpp>
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
	FCPPT_NONCOPYABLE(with_buffs)
public:
	void
	add_buff(
		buffs::buff &
	);

	void
	claim_buff(
		buffs::unique_ptr
	);
protected:
	with_buffs();

	~with_buffs();

	void
	on_update(
		time_type
	);
private:
	buffs::list buffs_;

	typedef boost::ptr_list<
		buffs::buff
	> buff_container;

	buff_container owned_buffs_;
};

}
}
}

#endif
