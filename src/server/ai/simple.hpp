#ifndef SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED

#include "base.hpp"
#include "entity_map.hpp"
#include "../entities/auto_weak_link.hpp"
#include "../entities/with_ai_fwd.hpp"
#include "../entities/with_body_fwd.hpp"
#include "../../diff_clock_fwd.hpp"
#include "../../diff_timer.hpp"
#include <fcppt/container/map_decl.hpp>
#include <fcppt/noncopyable.hpp>

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
	FCPPT_NONCOPYABLE(
		simple
	);
public:
	simple(
		sanguis::diff_clock const &,
		entities::with_ai &me,
		entities::auto_weak_link owner
	);

	~simple();
private:
	void
	update();

	void
	target_enters(
		entities::with_body &
	);

	void
	target_leaves(
		entities::with_body &
	);

	sanguis::diff_timer pos_timer_;

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
