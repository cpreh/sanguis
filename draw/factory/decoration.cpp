#include "decoration.hpp"
#include "../model.hpp"
#include "../z_ordering.hpp"
#include "../../decoration_type.hpp"
#include "../../load/decoration_name.hpp"

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::decoration(
	load::context const &ctx,
	entity_id const id,
	system &sys,
	decoration_type::type const ptype)
{
	return entity_ptr(
		new model(
			ctx,
			id,
			sys,
			load::decoration_name(
				ptype),
			z_ordering::decoration,
			false));
}
