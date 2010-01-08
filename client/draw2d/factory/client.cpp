#include "client.hpp"
#include "simple_sprite.hpp"
#include "../z_ordering.hpp"
#include "../../client_messages/add.hpp"
#include "../../exception.hpp"
#include <fcppt/text.hpp>

sanguis::client::draw2d::entities::auto_ptr
sanguis::client::draw2d::factory::client(
	sprite::client::system &client_system_,
	load::resource::textures const &textures_,
	entity_type::type const type_,
	sge::renderer::screen_size const &screen_size
)
{
	switch(
		type_
	)
	{
	case entity_type::cursor:
		return simple_sprite(
			client_system_,
			textures_,
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
			client_system_,
			textures_,
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
