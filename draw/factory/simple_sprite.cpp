#include "simple_sprite.hpp"
#include "../simple_sprite.hpp"
#include "../../load/context.hpp"
#include "../../load/resource/context.hpp"
#include "../../load/resource/textures.hpp"

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::simple_sprite(
	load::context const &ctx,
	entity_id const id,
	system &sys,
	z_ordering::type const z,
	sge::string const &texture_name)
{
	return entity_ptr(
		new draw::simple_sprite(
			id,
			sys,
			z,
			ctx.resources().textures().load(
				texture_name)));
}
