#include "friend.hpp"
#include "../model.hpp"
#include "../z_ordering.hpp"
#include "../../load/friend_name.hpp"
#include "../../friend_type.hpp"

sanguis::draw::entity_auto_ptr
sanguis::draw::factory::friend_(
	environment const &env,
	entity_id const id,
	friend_type::type const etype)
{
	return entity_auto_ptr(
		new model(
			env,
			id,
			load::friend_name(
				etype
			),
			z_ordering::model_generic,
			true,
			remove_action::render_dead
		)
	);
}
