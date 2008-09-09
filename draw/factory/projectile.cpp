#include "projectile.hpp"
#include "../bullet.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::projectile(
	entity_id const id,
	system &sys,
	projectile_type::type const ptype)
{
	switch(ptype) {
	case projectile_type::simple_bullet:
		return entity_ptr(
			new bullet(
				id,
				sys));
	case projectile_type::rocket:
		return entity_ptr( // FIXME
			new bullet(
				id,
				sys));
	default:
		throw sge::exception(
			SGE_TEXT("draw::factory::projectile: missing loading code!"));
	}
}
