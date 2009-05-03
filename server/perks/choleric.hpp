#ifndef SANGUIS_SERVER_PERKS_CHOLERIC_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_CHOLERIC_HPP_INCLUDED

#include "perk.hpp"
#include "../space_unit.hpp"
#include "../../diff_clock.hpp"
#include <sge/time/timer.hpp>
#include <sge/random/uniform.hpp>

namespace sanguis
{
namespace server
{
namespace perks
{

class choleric : public perk {
public:
	choleric();
private:
	void do_apply(
		entities::entity &,
		time_type,
		environment const &);
	bool can_raise_level() const;

	diff_clock       clock_;
	sge::time::timer shoot_timer;
	sge::random::uniform<space_unit> rand;
};

}
}
}

#endif
