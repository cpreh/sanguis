#ifndef SANGUIS_SERVER_ENTITIES_WITH_GHOSTS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_GHOSTS_HPP_INCLUDED

#include <sanguis/collision/world/object_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/collision/ghost_fwd.hpp>
#include <sanguis/server/collision/ghost_unique_ptr.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
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

class with_ghosts
:
	public virtual sanguis::server::entities::base
{
	FCPPT_NONCOPYABLE(
		with_ghosts
	);
public:
	with_ghosts();

	~with_ghosts();
protected:
	void
	add_ghost(
		sanguis::server::collision::ghost_unique_ptr &&
	);

	virtual
	bool
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	)
	override;

	virtual
	void
	on_destroy()
	override;

	void
	update_center(
		sanguis::server::center const &
	);
private:
	void
	insert_ghost(
		sanguis::server::collision::ghost &,
		sanguis::collision::world::object &
	);

	typedef boost::ptr_list<
		sanguis::server::collision::ghost
	> ghost_list;

	ghost_list ghosts_;
};

}
}
}

#endif
