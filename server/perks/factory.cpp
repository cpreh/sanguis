#include "factory.hpp"
#include "perk.hpp"
#include "choleric.hpp"
#include "health.hpp"
#include "ias.hpp"
#include "ims.hpp"
#include "irs.hpp"
#include "regeneration.hpp"
#include "../../exception.hpp"
#include <fcppt/text.hpp>

sanguis::server::perks::auto_ptr
sanguis::server::perks::create(
	perk_type::type const pt)
{
	switch(pt) {
	case perk_type::choleric:
		return auto_ptr(
			new choleric()
		);
	case perk_type::health:
		return auto_ptr(
			new health()
		);
	case perk_type::ias:
		return auto_ptr(
			new ias()
		);
	case perk_type::ims:
		return auto_ptr(
			new ims()
		);
	case perk_type::irs:
		return auto_ptr(
			new irs()
		);
	case perk_type::regeneration:
		return auto_ptr(
			new regeneration()
		);
	default:
		throw exception(
			FCPPT_TEXT("Invalid perk type!")
		);
	}
}
