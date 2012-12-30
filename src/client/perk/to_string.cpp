#include <sanguis/perk_type.hpp>
#include <sanguis/client/perk/to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string const
sanguis::client::perk::to_string(
	sanguis::perk_type const _type
)
{
	switch(
		_type
	)
	{
	case sanguis::perk_type::choleric:
		return FCPPT_TEXT("choleric");
	case sanguis::perk_type::health:
		return FCPPT_TEXT("health");
	case sanguis::perk_type::ias:
		return FCPPT_TEXT("ias");
	case sanguis::perk_type::ims:
		return FCPPT_TEXT("ims");
	case sanguis::perk_type::irs:
		return FCPPT_TEXT("irs");
	case sanguis::perk_type::regeneration:
		return FCPPT_TEXT("regeneration");
	case sanguis::perk_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
