#ifndef SANGUIS_SERVER_PERKS_CHOLERIC_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_CHOLERIC_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <fcppt/random/variate_decl.hpp>
#include <fcppt/random/distribution/uniform_real_decl.hpp>
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
	choleric(
		sanguis::diff_clock const &,
		sanguis::random_generator &
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

	typedef fcppt::random::distribution::uniform_real<
		server::space_unit
	> distribution;

	fcppt::random::variate<
		sanguis::random_generator,
		distribution
	> rand_;
};

}
}
}

#endif
