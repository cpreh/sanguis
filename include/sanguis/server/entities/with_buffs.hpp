#ifndef SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED

#include <sanguis/server/entities/with_buffs_fwd.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/buffs/list.hpp>
#include <sanguis/server/buffs/buff.hpp> // for buffs::list
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <fcppt/config/external_end.hpp>

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
	FCPPT_NONCOPYABLE(
		with_buffs
	);
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
	on_update();
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
