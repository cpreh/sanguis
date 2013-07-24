#include <sanguis/enemy_type.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/needs_healthbar.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/client/draw2d/factory/enemy.hpp>
#include <sanguis/load/enemy_name.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::enemy(
	sanguis::client::draw2d::entities::model::parameters const &_param,
	sanguis::enemy_type const _etype
)
{
	return
		sanguis::client::draw2d::entities::unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::entities::model::object
			>(
				_param,
				sanguis::load::enemy_name(
					_etype
				),
				sanguis::client::draw2d::entities::order_vector{
					sanguis::client::draw2d::z_ordering::model_generic
				},
				sanguis::client::draw2d::entities::model::needs_healthbar::no,
				sanguis::client::draw2d::entities::model::decay_option::delayed
			)
		);
}
