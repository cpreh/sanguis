#ifndef SANGUIS_SERVER_ENTITIES_WITH_GHOSTS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_GHOSTS_HPP_INCLUDED

#include "base.hpp"
#include "ghost_parameters_fwd.hpp"
#include "../collision/ghost_fwd.hpp"
#include "../collision/ghost_unique_ptr.hpp"
#include "../center.hpp"
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
		collision::create_parameters const &
	);

	void
	update_center(
		server::center const &
	);
private:
	virtual void
	recreate_ghosts(
		entities::ghost_parameters const &
	);

	typedef boost::ptr_list<
		collision::ghost
	> ghost_list;

	ghost_list ghosts_;
};

}
}
}

#endif
