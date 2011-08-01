#include "create.hpp"
#include "perk.hpp"
#include "choleric.hpp"
#include "health.hpp"
#include "ias.hpp"
#include "ims.hpp"
#include "irs.hpp"
#include "regeneration.hpp"
#include "../../exception.hpp"
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>

sanguis::server::perks::unique_ptr
sanguis::server::perks::create(
	sanguis::diff_clock const &_diff_clock,
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

	throw exception(
		FCPPT_TEXT("Invalid perk type!")
	);

}
