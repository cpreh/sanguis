#ifndef SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED

#include "base.hpp"
#include "entity_map.hpp"
#include "../entities/with_weapon_fwd.hpp"
#include "../entities/auto_weak_link.hpp"
#include <sge/container/map_decl.hpp>

namespace sanguis
{
namespace server
{
namespace ai
{

class simple
:
	public base 
{
public:
	explicit simple(
		entities::auto_weak_link owner
			= entities::auto_weak_link()
	);
private:
	void
	bind(
		entities::with_weapon &me
	);
	
	void
	update(
		time_type
	);

	void
	target_enters(
		entities::base &
	);

	void
	target_leaves(
		entities::base &
	);

	entities::with_weapon *me_;

	entities::auto_weak_link
		target_,
		owner_;

	entity_map potential_targets_;
};

}
}
}

#endif
