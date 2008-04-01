#include "../messages/add.hpp"
#include "../entity_type.hpp"
#include "bullet.hpp"
#include "factory.hpp"
#include "player.hpp"
#include "sprite.hpp"
#include "healthbar.hpp"
#include "resource_factory.hpp"
#include "coord_transform.hpp"
#include "z_ordering.hpp"

#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/string.hpp>

namespace
{

sanguis::draw::factory::entity_ptr
create_sprite(
	const sanguis::messages::add& m,
	const sge::string& s,
	const sge::screen_size_t& screen_size,
	const sge::space_unit z);

}

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::create_entity(
	const messages::add& m,
	const sge::screen_size_t &screen_size)
{
	// TODO: make this prettier and generate code for it using a template
	switch(m.type()) {
	case entity_type::player:
		return entity_ptr(
			new player(
				m.id(),
				virtual_to_screen(screen_size, m.pos()),
				static_cast<sge::space_unit>(m.angle()),
				// double conversion here (deliberately)
				sge::math::structure_cast<sge::space_unit>(
					virtual_to_screen(
						screen_size,
						m.speed()))
				));
	case entity_type::cursor:
		return create_sprite(
			m,
			SGE_TEXT("cursor"),
			screen_size,
			z_ordering::cursor);
	// TODO: do we have to tile the background?
	case entity_type::background:
		return create_sprite(
			m,
			SGE_TEXT("background"),
			screen_size,
			z_ordering::background);
	case entity_type::healthbar:
		return entity_ptr(
			new healthbar(
				m.id(),
				virtual_to_screen(screen_size, m.pos()),
				sge::sprite::dim(30, 10), // FIXME
				m.health(),
				m.max_health()));
	case entity_type::bullet:
		return entity_ptr(
			new bullet(
				m.id(),
				virtual_to_screen(screen_size, m.pos()),
				static_cast<sge::space_unit>(m.angle()),
				sge::math::structure_cast<sge::space_unit>(
					virtual_to_screen(
						screen_size,
						m.speed()))));
	default:
		throw sge::exception(SGE_TEXT("draw::factory: missing loading code!"));
	}
}

namespace
{

sanguis::draw::factory::entity_ptr
create_sprite(
	const sanguis::messages::add& m,
	const sge::string& s,
	const sge::screen_size_t& screen_size,
	const sge::space_unit z)
{
	return sanguis::draw::factory::entity_ptr(
		new sanguis::draw::sprite(
			m.id(),
			sge::math::structure_cast<sge::space_unit>(
				sanguis::virtual_to_screen(
					screen_size,
					m.speed())),
			sge::sprite::object(
				sanguis::virtual_to_screen(screen_size, m.pos()),
				sanguis::draw::resource::texture(s),
				sge::sprite::texture_dim,
				sge::colors::white,
				z,
				static_cast<sge::space_unit>(m.angle()))));
}

}
