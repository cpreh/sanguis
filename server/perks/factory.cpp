#include "factory.hpp"
#include "perk.hpp"
#include "choleric.hpp"
#include "ias.hpp"
#include "ims.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sanguis::server::perks::auto_ptr
sanguis::server::perks::create(
	perk_type::type const pt)
{
	switch(pt) {
	case perk_type::choleric:
		return auto_ptr(
			new choleric()
		);
	case perk_type::ias:
		return auto_ptr(
			new ias()
		);
	case perk_type::ims:
		return auto_ptr(
			new ims()
		);
	default:
		throw sge::exception(
			SGE_TEXT("Invalid perk type!")
		);
	}
}
