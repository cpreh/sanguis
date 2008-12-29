#include "decoration.hpp"
#include "../model.hpp"
#include "../object.hpp"
#include "../z_ordering.hpp"
#include "../../decoration_type.hpp"
#include "../../load/decoration_name.hpp"

sanguis::draw::entity_auto_ptr
sanguis::draw::factory::decoration(
	environment const &env,
	entity_id const id,
	decoration_type::type const ptype)
{
	return entity_auto_ptr(
		new model(
			env,
			id,
			load::decoration_name(
				ptype),
			z_ordering::decoration,
			false));
}
