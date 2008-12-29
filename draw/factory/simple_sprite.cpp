#include "simple_sprite.hpp"
#include "../simple_sprite.hpp"
#include "../environment.hpp"
#include "../../load/context.hpp"
#include "../../load/resource/context.hpp"
#include "../../load/resource/textures.hpp"

sanguis::draw::entity_auto_ptr
sanguis::draw::factory::simple_sprite(
	environment const &env,
	entity_id const id,
	z_ordering::type const z,
	sge::string const &texture_name)
{
	return entity_auto_ptr(
		new draw::simple_sprite(
			env,
			id,
			z,
			env.context().resources().textures().load(
				texture_name)));
}
