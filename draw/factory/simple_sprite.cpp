#include "simple_sprite.hpp"
#include "../simple_sprite.hpp"
#include "../../load/resource/factory.hpp"

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::simple_sprite(
	entity_id const id,
	z_ordering::type const z,
	sge::string const &texture_name)
{
	return entity_ptr(
		new draw::simple_sprite(
			id,
			z,
			load::resource::texture(
				texture_name)));
}
