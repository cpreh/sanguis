#include <sanguis/client/draw2d/factory/enemy.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/load/enemy_name.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::enemy(
	entities::model::parameters const &_param,
	enemy_type::type const _etype
)
{
	return
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::model::object
			>(
				fcppt::cref(
					_param
				),
				load::enemy_name(
					_etype
				),
				fcppt::assign::make_container<
					entities::order_vector
				>(
					z_ordering::model_generic
				),
				entities::model::needs_healthbar::no,
				entities::model::decay_option::delayed
			)
		);
}
