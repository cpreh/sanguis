#include "simple_sprite.hpp"
#include "../entities/simple_sprite.hpp"
#include "../../../load/resource/textures.hpp"

sanguis::client::draw2d::entities::auto_ptr
sanguis::client::draw2d::factory::simple_sprite(
	sprite::client::system &system_,
	load::resource::textures const &textures_,
	z_ordering::type const order_,
	fcppt::string const &texture_name,
	sprite::client::repetition_type const repeat
)
{
	return entities::auto_ptr(
		new entities::simple_sprite(
			system_,
			order_,
			textures_.load(
				texture_name
			),
			repeat
		)
	);
}
