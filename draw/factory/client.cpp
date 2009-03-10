#include "client.hpp"
#include "simple_sprite.hpp"
#include "../z_ordering.hpp"
#include "../../client_messages/add.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>

sanguis::draw::entity_auto_ptr
sanguis::draw::factory::client(
	environment const &env,
	client_messages::add const &m,
	sge::renderer::screen_size const &screen_size)
{
	switch(m.type()) {
	case client_entity_type::cursor:
		return simple_sprite(
			env,
			m.id(),
			z_ordering::cursor,
			SGE_TEXT("cursor"));
	// TODO: do we have to tile the background?
	case client_entity_type::background:
		return simple_sprite(
			env,
			m.id(),
			z_ordering::background,
			SGE_TEXT("background"));
	default:
		throw exception(
			SGE_TEXT("draw::factory::client: missing loading code!"));
	}
}
