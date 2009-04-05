#include "from_perk_type.hpp"
#include <sge/text.hpp>
#include <sge/exception.hpp>

sge::string const
sanguis::client::from_perk_type(
	perk_type::type const s)
{
	switch (s)
	{
		case perk_type::choleric:
			return SGE_TEXT("choleric");
		case perk_type::ias:
			return SGE_TEXT("ias");
		case perk_type::ims:
			return SGE_TEXT("ims");
		case perk_type::size:
			throw sge::exception(
				SGE_TEXT("invalid perk type"));
	}
}
