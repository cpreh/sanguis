#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/perks/choleric.hpp>
#include <sanguis/server/perks/create.hpp>
#include <sanguis/server/perks/fire_damage.hpp>
#include <sanguis/server/perks/health.hpp>
#include <sanguis/server/perks/ias.hpp>
#include <sanguis/server/perks/ims.hpp>
#include <sanguis/server/perks/irs.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <sanguis/server/perks/piercing_damage.hpp>
#include <sanguis/server/perks/unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::server::perks::unique_ptr
sanguis::server::perks::create(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::perk_type const _type
)
{
	switch(
		_type
	)
	{
	case sanguis::perk_type::choleric:
		return
			fcppt::make_unique_ptr<
				sanguis::server::perks::choleric
			>(
				_diff_clock,
				_random_generator
			);
	case sanguis::perk_type::health:
		return
			fcppt::make_unique_ptr<
				sanguis::server::perks::health
			>();
	case sanguis::perk_type::fire_damage:
		return
			fcppt::make_unique_ptr<
				sanguis::server::perks::fire_damage
			>();
	case sanguis::perk_type::piercing_damage:
		return
			fcppt::make_unique_ptr<
				sanguis::server::perks::piercing_damage
			>();
	case sanguis::perk_type::ias:
		return
			fcppt::make_unique_ptr<
				sanguis::server::perks::ias
			>();
	case sanguis::perk_type::ims:
		return
			fcppt::make_unique_ptr<
				sanguis::server::perks::ims
			>();
	case sanguis::perk_type::irs:
		return
			fcppt::make_unique_ptr<
				sanguis::server::perks::irs
			>();
	}

	FCPPT_ASSERT_UNREACHABLE;
}
