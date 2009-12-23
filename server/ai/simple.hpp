#ifndef SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED

#include "base.hpp"
#include "entity_map.hpp"
#include "../entities/with_ai_fwd.hpp"
#include "../entities/auto_weak_link.hpp"
#include <fcppt/container/map_decl.hpp>

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
	simple(
		entities::with_ai &me,
		entities::auto_weak_link owner
	);
private:
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

	entities::with_ai &me_;

	entities::auto_weak_link
		target_,
		owner_;

	entity_map potential_targets_;
};

}
}
}

#endif
