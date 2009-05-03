#include "from_perk_type.hpp"
#include "../exception.hpp"
#include <sge/text.hpp>

sge::string const
sanguis::client::from_perk_type(
	perk_type::type const s)
{
	switch (s)
	{
		case perk_type::choleric:
			return SGE_TEXT("choleric");
		case perk_type::health:
			return SGE_TEXT("health");
		case perk_type::ias:
			return SGE_TEXT("ias");
		case perk_type::ims:
			return SGE_TEXT("ims");
		case perk_type::irs:
			return SGE_TEXT("irs");
		case perk_type::regeneration:
			return SGE_TEXT("regeneration");
		case perk_type::size:
			break;
	}

	throw exception(
		SGE_TEXT("invalid perk type in from_perk_type!")
	);
}
