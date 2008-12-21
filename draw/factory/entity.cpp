#include "entity.hpp"
#include "../player.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::entity(
	load::context const &ctx,
	entity_id const id,
	system &sys,
	entity_type::type const type)
{
	// TODO: make this prettier and generate code for it using a template
	switch(type) {
	case entity_type::player:
		return entity_ptr(
			new player(
				ctx,
				id,
				sys));
	case entity_type::enemy:
		throw exception(
			SGE_TEXT("entity_type::enemy cannot be created using entity!"));
	case entity_type::projectile:
		throw exception(
			SGE_TEXT("entity_type::projectile cannot be created using entity!"));
	default:
		throw exception(
			SGE_TEXT("draw::factory::entity: missing loading code!"));
	}
}
