#ifndef SANGUIS_SERVER_PERKS_CHOLERIC_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_CHOLERIC_HPP_INCLUDED

#include "perk.hpp"
#include "level_diff.hpp"
#include "../space_unit.hpp"
#include "../environment/object_fwd.hpp"
#include "../entities/base_fwd.hpp"
#include "../../diff_clock_fwd.hpp"
#include "../../diff_timer.hpp"
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
	explicit choleric(
		sanguis::diff_clock const &
	);

	~choleric();
private:
	void
	update(
		entities::base &,
		environment::object &
	);

	void
	change(
		entities::base &,
		perks::level_diff
	);

	sanguis::diff_clock const &diff_clock_;

	sanguis::diff_timer shoot_timer_;

	fcppt::random::uniform<
		server::space_unit
	> rand_;
};

}
}
}

#endif
