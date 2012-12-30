#include <sanguis/friend_type.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/sentry.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/needs_healthbar.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/client/draw2d/factory/friend.hpp>
#include <sanguis/load/friend_name.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::friend_(
	sanguis::client::draw2d::entities::model::parameters const &_param,
	sanguis::friend_type const _etype
)
{
	switch(
		_etype
	)
	{
	case sanguis::friend_type::size:
		break;
	case sanguis::friend_type::spider:
		return
			sanguis::client::draw2d::entities::unique_ptr(
				fcppt::make_unique_ptr<
					sanguis::client::draw2d::entities::model::object
				>(
					_param,
					sanguis::load::friend_name(
						_etype
					),
					fcppt::assign::make_container<
						sanguis::client::draw2d::entities::order_vector
					>(
						sanguis::client::draw2d::z_ordering::model_generic
					),
					sanguis::client::draw2d::entities::model::needs_healthbar::yes,
					sanguis::client::draw2d::entities::model::decay_option::delayed
				)
			);
	case sanguis::friend_type::sentry:
		return
			sanguis::client::draw2d::entities::unique_ptr(
				fcppt::make_unique_ptr<
					sanguis::client::draw2d::entities::sentry
				>(
					_param
				)
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
