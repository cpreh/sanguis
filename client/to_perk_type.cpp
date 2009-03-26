#include "to_perk_type.hpp"
#include <sge/text.hpp>

sanguis::perk_type::type
sanguis::client::to_perk_type(
	sge::string const &s)
{
	if(s == SGE_TEXT("choleric"))
		return perk_type::choleric;
	if(s == SGE_TEXT("ias"))
		return perk_type::ias;
	if(s == SGE_TEXT("ims"))
		return perk_type::ims;
	return perk_type::size;
}
