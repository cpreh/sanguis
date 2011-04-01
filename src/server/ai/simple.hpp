#ifndef SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED

#include "base.hpp"
#include "entity_map.hpp"
#include "../entities/auto_weak_link.hpp"
#include "../entities/with_ai_fwd.hpp"
#include "../entities/with_body_fwd.hpp"
#include "../../diff_clock.hpp"
#include "../../time_type.hpp"
#include <sge/time/timer.hpp>
#include <fcppt/container/map_decl.hpp>

namespace sanguis
{
namespace server
{
namespace ai
{

class simple
:
	public ai::base 
{
public:
	simple(
		entities::with_ai &me,
		entities::auto_weak_link owner
	);

	~simple();
private:
	void
	update(
		time_type
	);

	void
	target_enters(
		entities::with_body &
	);

	void
	target_leaves(
		entities::with_body &
	);

	diff_clock diff_clock_;

	sge::time::timer pos_timer_;

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
