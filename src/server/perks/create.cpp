#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/perks/create.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <sanguis/server/perks/choleric.hpp>
#include <sanguis/server/perks/health.hpp>
#include <sanguis/server/perks/ias.hpp>
#include <sanguis/server/perks/ims.hpp>
#include <sanguis/server/perks/irs.hpp>
#include <sanguis/server/perks/regeneration.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::server::perks::unique_ptr
sanguis::server::perks::create(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	perk_type::type const _type
)
{
	switch(
		_type
	)
	{
	case perk_type::choleric:
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					choleric
				>(
					fcppt::cref(
						_diff_clock
					),
					fcppt::ref(
						_random_generator
					)
				)
			);
	case perk_type::health:
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					health
				>()
			);
	case perk_type::ias:
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					ias
				>()
			);
	case perk_type::ims:
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					ims
				>()
			);
	case perk_type::irs:
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					irs
				>()
			);
	case perk_type::regeneration:
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					regeneration
				>()
			);
	case perk_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
