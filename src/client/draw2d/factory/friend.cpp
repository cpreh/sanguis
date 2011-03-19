#include "friend.hpp"
#include "../entities/model/object.hpp"
#include "../entities/sentry.hpp"
#include "../z_ordering.hpp"
#include "../../../load/friend_name.hpp"
#include "../../../friend_type.hpp"
#include "../../../exception.hpp"
#include <fcppt/text.hpp>

sanguis::client::draw2d::entities::auto_ptr
sanguis::client::draw2d::factory::friend_(
	entities::model::parameters const &_param,
	friend_type::type const _etype
)
{
	switch(
		_etype
	)
	{
	case friend_type::size:
		break;
	case friend_type::spider:
		return
			entities::auto_ptr(
				new entities::model::object(
					_param,
					load::friend_name(
						_etype
					),
					z_ordering::model_generic,
					entities::model::needs_healthbar::yes,
					entities::model::decay_option::delayed
				)
			);
	case friend_type::sentry:
		return
			entities::auto_ptr(
				new entities::sentry(
					_param
				)
			);
	}

	throw sanguis::exception(
		FCPPT_TEXT("Missing factory code in client::draw2d::factory::friend!")
	);
}
