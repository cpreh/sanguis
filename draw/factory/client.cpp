#include "client.hpp"
#include "simple_sprite.hpp"
#include "../z_ordering.hpp"
#include "../../client_messages/add.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::client(
	load::context const &ctx,
	client_messages::add const &m,
	system &sys,
	sge::renderer::screen_size_t const &screen_size)
{
	switch(m.type()) {
	case client_entity_type::cursor:
		return simple_sprite(
			ctx,
			m.id(),
			sys,
			z_ordering::cursor,
			SGE_TEXT("cursor"));
	// TODO: do we have to tile the background?
	case client_entity_type::background:
		return simple_sprite(
			ctx,
			m.id(),
			sys,
			z_ordering::background,
			SGE_TEXT("background"));
	default:
		throw exception(
			SGE_TEXT("draw::factory::client: missing loading code!"));
	}
}
