#include <sanguis/client/draw2d/factory/friend.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/sentry.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/load/friend_name.hpp>
#include <sanguis/friend_type.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::client::draw2d::entities::unique_ptr
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
			entities::unique_ptr(
				fcppt::make_unique_ptr<
					entities::model::object
				>(
					fcppt::cref(
						_param
					),
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
			entities::unique_ptr(
				fcppt::make_unique_ptr<
					entities::sentry
				>(
					fcppt::cref(
						_param
					)
				)
			);
	}

	FCPPT_ASSERT_UNREACHABLE
}
