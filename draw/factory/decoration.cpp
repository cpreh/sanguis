#include "decoration.hpp"
#include "../model.hpp"
#include "../z_ordering.hpp"
#include "../../decoration_type.hpp"
#include "../../load/decoration_name.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

namespace
{

sge::string const get_texture(
	sanguis::decoration_type::type);

}

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::decoration(
	entity_id const id,
	system &sys,
	decoration_type::type const ptype)
{
	return entity_ptr(
		new model(
			id,
			sys,
			get_texture(
				ptype),
			z_ordering::decoration,
			false));
}

namespace
{

sge::string const get_texture(
	sanguis::decoration_type::type const ptype)
{
	return sanguis::load::decoration_name(ptype);
}

}
