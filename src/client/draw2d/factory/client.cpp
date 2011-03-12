#include "client.hpp"
#include "simple_sprite.hpp"
#include "../entities/base.hpp"
#include "../z_ordering.hpp"
#include "../../../exception.hpp"
#include <fcppt/text.hpp>

sanguis::client::draw2d::entities::auto_ptr
sanguis::client::draw2d::factory::client(
	sprite::client::system &_client_system,
	load::resource::textures const &_textures,
	entity_type::type const _type,
	sge::renderer::screen_size const &_screen_size
)
{
	switch(
		_type
	)
	{
	case entity_type::size:
		break;
	case entity_type::cursor:
		return simple_sprite(
			_client_system,
			_textures,
			z_ordering::cursor,
			FCPPT_TEXT("cursor"),
			static_cast<
				sprite::client::repetition_type
			>(
				1
			)
		);
	// TODO: do we have to tile the background?
	case entity_type::background:
		return simple_sprite(
			_client_system,
			_textures,
			z_ordering::background,
			FCPPT_TEXT("background"),
			static_cast<
				sprite::client::repetition_type
			>(
				1
			)
		);
	}

	throw exception(
		FCPPT_TEXT("draw::factory::client: missing loading code!")
	);
}
