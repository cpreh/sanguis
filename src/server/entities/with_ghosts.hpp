#ifndef SANGUIS_SERVER_ENTITIES_WITH_GHOSTS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_GHOSTS_HPP_INCLUDED

#include "../collision/ghost_fwd.hpp"
#include <boost/ptr_container/ptr_list.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class with_ghosts
:
	public entities::base
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
		collision::global_groups const &,
		collision::create_parameters const &
	);

	collision::ghost_list &
	ghosts();
private:
	virtual void
	recreate_ghosts(
		collision::global_groups const &_groups,
		collision::create_parameters const &_params
	) = 0;

	collision::ghost_list ghosts_;
};

}
}
}

#endif
