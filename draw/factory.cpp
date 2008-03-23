#include "../messages/add.hpp"
#include "../entity_type.hpp"
#include "factory.hpp"
#include "player.hpp"
#include "sprite.hpp"
#include "resource_factory.hpp"

#include <sge/exception.hpp>
#include <sge/string.hpp>

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::create_entity(const messages::add& m)
{
	// TODO: make this prettier and generate code for it using a template
	switch(m.type()) {
	case entity_type::player:
		return entity_ptr(new player(
			m.id(),
			m.pos(),
			sge::sprite_texture_dim,
			m.angle(),
			m.speed()));
	case entity_type::cursor:
		return entity_ptr(new sprite(
			m.id(),
			m.pos(),
			sge::sprite_texture_dim,
			resource::texture(SGE_TEXT("cursor")),
			m.angle(),
			m.speed()));
	default:
		throw sge::exception(SGE_TEXT("draw::factory: missing loading code!"));
	}
}
