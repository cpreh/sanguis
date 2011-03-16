#ifndef SANGUIS_SERVER_PERKS_CHOLERIC_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_CHOLERIC_HPP_INCLUDED

#include "perk.hpp"
#include "level_diff.hpp"
#include "level_type.hpp"
#include "../space_unit.hpp"
#include "../../diff_clock.hpp"
#include <sge/time/timer.hpp>
#include <fcppt/random/uniform.hpp>
#include <fcppt/noncopyable.hpp>

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
	FCPPT_NONCOPYABLE(
		choleric
	);
public:
	choleric();

	~choleric();
private:
	void
	update(
		entities::base &,
		time_type,
		environment::object_ptr
	);

	level_type
	max_level() const;

	void
	change(
		entities::base &,
		level_diff
	);

	diff_clock clock_;

	sge::time::timer shoot_timer_;

	fcppt::random::uniform<space_unit> rand_;
};

}
}
}

#endif
