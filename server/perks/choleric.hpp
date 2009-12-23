#ifndef SANGUIS_SERVER_PERKS_CHOLERIC_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_CHOLERIC_HPP_INCLUDED

#include "perk.hpp"
#include "../space_unit.hpp"
#include "../../diff_clock.hpp"
#include <sge/time/timer.hpp>
#include <fcppt/random/uniform.hpp>

namespace sanguis
{
namespace server
{
namespace perks
{

class choleric
:
	public perk
{
public:
	choleric();
private:
	void
	update(
		entities::base &,
		time_type,
		environment::object_ptr
	);

	bool
	can_raise_level() const;

	void
	apply(
		entities::base &
	);

	void
	unapply(
		entities::base &
	);

	diff_clock       clock_;
	sge::time::timer shoot_timer;
	fcppt::random::uniform<space_unit> rand;
};

}
}
}

#endif
