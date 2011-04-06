#ifndef SANGUIS_SERVER_ENTITIES_WITH_GHOSTS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_GHOSTS_HPP_INCLUDED

#include "base.hpp"
#include "transfer_parameters_fwd.hpp"
#include "../collision/ghost_fwd.hpp"
#include "../collision/ghost_unique_ptr.hpp"
#include "../collision/global_groups_fwd.hpp"
#include "../center.hpp"
#include <sge/projectile/ghost/scoped_fwd.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_list.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class with_ghosts
:
	public virtual entities::base
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
		collision::ghost_unique_ptr
	);

	void
	on_transfer(
		entities::transfer_parameters const &
	);

	void
	update_center(
		server::center const &
	);
private:
	void
	insert_ghost(
		collision::ghost &,
		sge::projectile::world &,
		collision::global_groups const &
	);

	typedef boost::ptr_list<
		collision::ghost
	> ghost_list;

	ghost_list ghosts_;

	typedef boost::ptr_list<
		sge::projectile::ghost::scoped
	> scoped_ghost_list;

	scoped_ghost_list scoped_ghosts_;
};

}
}
}

#endif
