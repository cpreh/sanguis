#include "bullet.hpp"
#include "factory.hpp"
#include "player.hpp"
#include "simple_creep.hpp"
#include "resource_factory.hpp"
#include "coord_transform.hpp"
#include "z_ordering.hpp"
#include "animation_pack.hpp"
#include "../messages/add.hpp"
#include "../entity_type.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>

namespace
{

sge::string const get_animations(sanguis::entity_type::type);

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
	case entity_type::wolf_white:
	case entity_type::wolf_black:
		return entity_ptr(
			new simple_creep(
				m.id(),
				virtual_to_screen(screen_size, m.pos()),
				sge::math::structure_cast<sge::space_unit>(
					virtual_to_screen(
						screen_size,
						m.speed())),
				static_cast<sge::space_unit>(m.angle()),
				animation_pack(get_animations(m.type())),
				m.health(),
				m.max_health()));
	default:
		throw sge::exception(SGE_TEXT("draw::factory: missing loading code!"));
	}
}

namespace
{

sge::string const get_animations(sanguis::entity_type::type const type)
{
	switch(type) {
	case sanguis::entity_type::wolf_white:
		return SGE_TEXT("wolf_white");
	case sanguis::entity_type::wolf_black:
		return SGE_TEXT("wolf_black");
	default:
		throw sge::exception(SGE_TEXT("No textures for a specific creep available!"));
	}
}

}
