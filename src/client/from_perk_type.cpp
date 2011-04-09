#include "from_perk_type.hpp"
#include "../exception.hpp"
#include <fcppt/text.hpp>

fcppt::string const
sanguis::client::from_perk_type(
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

	throw sanguis::exception(
		FCPPT_TEXT("invalid perk type in from_perk_type!")
	);
}
