#ifndef SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED

#include <sanguis/server/buffs/buff_fwd.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_buffs_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_wrapper_decl.hpp>
#include <fcppt/reference_wrapper_std_hash.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <unordered_set>
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
		sanguis::server::buffs::buff &
	);

	void
	remove_buff(
		sanguis::server::buffs::buff &
	);

	void
	claim_buff(
		sanguis::server::buffs::unique_ptr &&
	);
protected:
	with_buffs();

	~with_buffs();

	void
	update()
	override;
private:
	typedef
	fcppt::reference_wrapper<
		sanguis::server::buffs::buff
	>
	buff_reference;

	typedef
	std::unordered_set<
		buff_reference
	>
	buff_set;

	buff_set buffs_;

	typedef
	boost::ptr_list<
		sanguis::server::buffs::buff
	>
	buff_container;

	buff_container owned_buffs_;
};

}
}
}

#endif
