#include "friend.hpp"
#include "../model.hpp"
#include "../sentry.hpp"
#include "../z_ordering.hpp"
#include "../../load/friend_name.hpp"
#include "../../friend_type.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>

sanguis::draw::entity_auto_ptr
sanguis::draw::factory::friend_(
	environment const &env,
	entity_id const id,
	friend_type::type const etype)
{
	switch(etype) {
	case friend_type::spider:
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
	case friend_type::sentry:
		return entity_auto_ptr(
			new sentry(
				env,
				id
			)
		);
	default:
		throw exception(
			SGE_TEXT("Missing factory code in draw::factory::friend!")
		);
	}
}
