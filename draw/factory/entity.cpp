#include "entity.hpp"
#include "../player.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>

sanguis::draw::entity_auto_ptr
sanguis::draw::factory::entity(
	environment const &env,
	entity_id const id,
	entity_type::type const type)
{
	// TODO: make this prettier and generate code for it using a template
	switch(type) {
	case entity_type::player:
		return entity_auto_ptr(
			new player(
				env,
				id));
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
