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
	fcppt::string const &texture_name,
	sprite::client::repetition_type const repeat
)
{
	return entity_auto_ptr(
		new draw::simple_sprite(
			env,
			id,
			z,
			env.context().resources().textures().load(
				texture_name
			),
			repeat
		)
	);
}
