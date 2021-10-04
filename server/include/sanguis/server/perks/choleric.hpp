#ifndef SANGUIS_SERVER_PERKS_CHOLERIC_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_CHOLERIC_HPP_INCLUDED

#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/random_variate_decl.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/entities/with_perks_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/random/distribution/basic_decl.hpp>
#include <fcppt/random/distribution/parameters/uniform_real_decl.hpp>


namespace sanguis::server::perks
{

class choleric
:
	public sanguis::server::perks::perk
{
	FCPPT_NONMOVABLE(
		choleric
	);
public:
	choleric(
		sanguis::diff_clock_cref,
		sanguis::random_generator_ref
	);

	~choleric()
	override;
private:
	void
	update(
		sanguis::server::entities::with_perks &, // NOLINT(google-runtime-references)
		sanguis::server::environment::object & // NOLINT(google-runtime-references)
	) // NOLINT(google-runtime-references)
	override;

	void
	change(
		sanguis::server::entities::with_perks &, // NOLINT(google-runtime-references)
		sanguis::server::perks::level_diff
	)
	override;

	sanguis::diff_timer shoot_timer_;

	using
	distribution
	=
	fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_real<
			sanguis::server::space_unit
		>
	>;

	sanguis::random_variate<
		distribution
	> rand_;
};

}

#endif
