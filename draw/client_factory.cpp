#include "client_factory.hpp"
#include "coord_transform.hpp"
#include "simple_sprite.hpp"
#include "z_ordering.hpp"
#include "../load/resource/factory.hpp"
#include "../client_messages/add.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <sge/su.hpp>

namespace
{

sanguis::draw::client_factory::entity_ptr
create_sprite(
	const sanguis::client_messages::add& m,
	const sge::string& s,
	const sge::renderer::screen_size_t& screen_size,
	const sge::space_unit z);

}


sanguis::draw::client_factory::entity_ptr
sanguis::draw::client_factory::create_entity(
	const client_messages::add &m,
	const sge::renderer::screen_size_t &screen_size)
{

	switch(m.type()) {
	case client_entity_type::cursor:
		return create_sprite(
			m,
			SGE_TEXT("cursor"),
			screen_size,
			z_ordering::cursor);
	// TODO: do we have to tile the background?
	case client_entity_type::background:
		return create_sprite(
			m,
			SGE_TEXT("background"),
			screen_size,
			z_ordering::background);
	default:
		throw sge::exception(SGE_TEXT("draw::client_factory: missing loading code!"));
	}
}

namespace
{

sanguis::draw::client_factory::entity_ptr
create_sprite(
	const sanguis::client_messages::add& m,
	const sge::string& s,
	const sge::renderer::screen_size_t& screen_size,
	const sge::space_unit z)
{
	return sanguis::draw::client_factory::entity_ptr(
		new sanguis::draw::simple_sprite(
			m.id(),
			sge::sprite::point(0,0), //FIXME
			sge::sprite::texture_dim,
			z,
			//sanguis::virtual_to_screen(screen_size, m.pos()),
			sge::su(0),
			sanguis::load::resource::texture(s)));
}

}
