#include "../messages/add.hpp"
#include "../entity_type.hpp"
#include "factory.hpp"
#include "player.hpp"
#include "sprite.hpp"
#include "resource_factory.hpp"
#include "coord_transform.hpp"

#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/string.hpp>

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::create_entity(const messages::add& m,const sge::screen_size_t &screen_size)
{
	// TODO: make this prettier and generate code for it using a template
	switch(m.type()) {
	case entity_type::player:
		return entity_ptr(new player(
			m.id(),
			virtual_to_screen(screen_size,m.pos()),
			sge::sprite_texture_dim,
			static_cast<sge::space_unit>(m.angle()),
			// double conversion here (deliberately)
			sge::math::structure_cast<sge::space_unit>(virtual_to_screen(screen_size,m.speed()))));
	case entity_type::cursor:
		return entity_ptr(new sprite(
			m.id(),
			virtual_to_screen(screen_size,m.pos()),
			sge::sprite_texture_dim,
			resource::texture(SGE_TEXT("cursor")),
			static_cast<sge::space_unit>(m.angle()),
			// double conversion here (deliberately)
			sge::math::structure_cast<sge::space_unit>(virtual_to_screen(screen_size,m.speed()))));
	default:
		throw sge::exception(SGE_TEXT("draw::factory: missing loading code!"));
	}
}
