#include "simple_sprite.hpp"
#include "../entities/simple_sprite.hpp"
#include "../../../load/resource/textures.hpp"

sanguis::client::draw2d::entities::auto_ptr
sanguis::client::draw2d::factory::simple_sprite(
	sprite::client::system &_system,
	load::resource::textures const &_textures,
	z_ordering::type const _order,
	fcppt::string const &_texture_name,
	sprite::client::repetition_type const _repeat
)
{
	return
		entities::auto_ptr(
			new entities::simple_sprite(
				_system,
				_order,
				_textures.load(
					_texture_name
				),
				_repeat
			)
		);
}
