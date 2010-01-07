#include "friend.hpp"
#include "../model.hpp"
#include "../sentry.hpp"
#include "../z_ordering.hpp"
#include "../../load/friend_name.hpp"
#include "../../friend_type.hpp"
#include "../../exception.hpp"
#include <fcppt/text.hpp>

sanguis::client::draw2d::entities::auto_ptr
sanguis::client::draw2d::factory::friend_(
	entities::model::parameters const &param,
	friend_type::type const etype
)
{
	switch(etype)
	{
	case friend_type::spider:
		return entities::auto_ptr(
			new model(
				param,
				load::friend_name(
					etype
				),
				z_ordering::model_generic,
				true,
				remove_action::render_dead
			)
		);
	case friend_type::sentry:
		return entities::auto_ptr(
			new sentry(
				param
			)
		);
	}

	throw exception(
		FCPPT_TEXT("Missing factory code in client::draw2d::factory::friend!")
	);
}
