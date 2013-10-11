#ifndef SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED

#include <sanguis/server/buffs/buff_fwd.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_buffs_fwd.hpp>
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
	public virtual sanguis::server::entities::base
{
	FCPPT_NONCOPYABLE(
		with_buffs
	);
public:
	void
	add_buff(
		sanguis::server::buffs::unique_ptr &&
	);

	void
	remove_buff(
		sanguis::server::buffs::buff &
	);
protected:
	with_buffs();

	~with_buffs();

	void
	update()
	override;
private:
	typedef
	boost::ptr_list<
		sanguis::server::buffs::buff
	>
	buff_set;

	buff_set buffs_;
};

}
}
}

#endif
