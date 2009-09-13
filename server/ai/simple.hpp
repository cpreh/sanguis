#ifndef SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED

#include "base.hpp"
#include "../entities/entity_with_weapon_fwd.hpp"
#include "../entities/auto_weak_link.hpp"
#include "../../diff_clock.hpp"
#include <sge/time/timer.hpp>

namespace sanguis
{
namespace server
{
namespace ai
{

class simple : public base {
public:
	explicit simple(
		entities::auto_weak_link owner
			= entities::auto_weak_link()
	);
private:
	void
	bind(
		entities::entity_with_weapon &me
	);
	
	void
	update(
		time_type
	);

	entities::entity_with_weapon *me_;

	entities::auto_weak_link
		target,
		owner_;

	diff_clock diff_clock_;

	sge::time::timer search_new_target_timer;
};

}
}
}

#endif
