#include <sanguis/friend_type.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/sentry.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/name.hpp>
#include <sanguis/client/draw2d/entities/model/needs_healthbar.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/factory/friend.hpp>
#include <sanguis/load/friend_name.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::friend_(
	sanguis::client::draw2d::entities::model::load_parameters const &_parameters,
	sanguis::friend_type const _enemy_type
)
{
	switch(
		_enemy_type
	)
	{
	case sanguis::friend_type::spider:
		return
			sanguis::client::draw2d::entities::unique_ptr(
				// TODO: Own class!
				fcppt::make_unique_ptr<
					sanguis::client::draw2d::entities::model::object
				>(
					sanguis::client::draw2d::entities::model::parameters(
						_parameters,
						sanguis::client::draw2d::entities::model::name(
							sanguis::load::friend_name(
								_enemy_type
							)
						),
						sanguis::client::draw2d::entities::order_vector{
							sanguis::client::draw2d::z_ordering::model_generic
						},
						sanguis::client::draw2d::entities::model::needs_healthbar::yes,
						sanguis::client::draw2d::entities::model::decay_option::delayed
					)
				)
			);
	case sanguis::friend_type::sentry:
		return
			sanguis::client::draw2d::entities::unique_ptr(
				fcppt::make_unique_ptr<
					sanguis::client::draw2d::entities::sentry
				>(
					_parameters
				)
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
