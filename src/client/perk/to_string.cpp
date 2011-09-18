#include <sanguis/client/perk/to_string.hpp>
#include <sanguis/perk_type.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

fcppt::string const
sanguis::client::perk::to_string(
	perk_type::type const _type
)
{
	switch(
		_type
	)
	{
	case perk_type::choleric:
		return FCPPT_TEXT("choleric");
	case perk_type::health:
		return FCPPT_TEXT("health");
	case perk_type::ias:
		return FCPPT_TEXT("ias");
	case perk_type::ims:
		return FCPPT_TEXT("ims");
	case perk_type::irs:
		return FCPPT_TEXT("irs");
	case perk_type::regeneration:
		return FCPPT_TEXT("regeneration");
	case perk_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE
}
