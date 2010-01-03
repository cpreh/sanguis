#include "client.hpp"
#include "simple_sprite.hpp"
#include "../z_ordering.hpp"
#include "../../client_messages/add.hpp"
#include "../../exception.hpp"
#include <fcppt/text.hpp>

sanguis::draw::entity_auto_ptr
sanguis::draw::factory::client(
	environment const &env,
	client_messages::add const &m,
	sge::renderer::screen_size const &screen_size
)
{
	switch(m.type()) {
	case client_entity_type::cursor:
		return simple_sprite(
			env,
			m.id(),
			z_ordering::cursor,
			FCPPT_TEXT("cursor"),
			static_cast<
				sprite::client::repetition_type
			>(1)
		);
	// TODO: do we have to tile the background?
	case client_entity_type::background:
		return simple_sprite(
			env,
			m.id(),
			z_ordering::background,
			FCPPT_TEXT("background"),
			static_cast<
				sprite::client::repetition_type
			>(
				1
			)
		);
	default:
		throw exception(
			FCPPT_TEXT("draw::factory::client: missing loading code!"));
	}
}
