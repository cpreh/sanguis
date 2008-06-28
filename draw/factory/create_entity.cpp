#include "create_entity.hpp"
#include "../bullet.hpp"
#include "../player.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::create_entity(
	const entity_id id,
	const entity_type::type type)
{
	// TODO: make this prettier and generate code for it using a template
	switch(type) {
	case entity_type::player:
		return entity_ptr(
			new player(id));
	case entity_type::bullet:
		return entity_ptr(
			new bullet(id));
	case entity_type::enemy:
		throw sge::exception(
			SGE_TEXT("entity_type::enemy cannot be created using create_entity!"));
	default:
		throw sge::exception(
			SGE_TEXT("draw::factory::create_entity: missing loading code!"));
	}
}
