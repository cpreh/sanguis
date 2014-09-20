#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/factory/destructible.hpp>
#include <sanguis/client/draw2d/sprite/normal/white.hpp>
#include <sanguis/creator/destructible_type.hpp>
#include <sanguis/load/model/destructible_path.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::destructible(
	sanguis::client::draw2d::entities::model::load_parameters const &_parameters,
	sanguis::creator::destructible_type const _destructible_type
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::entities::model::object
		>(
			sanguis::client::draw2d::entities::model::parameters(
				_parameters,
				sanguis::load::model::destructible_path(
					_destructible_type
				),
				sanguis::client::draw2d::entities::order_vector{
					sanguis::client::draw2d::z_ordering::destructible
				},
				sanguis::client::optional_health_pair(),
				sanguis::client::draw2d::entities::model::decay_option::delayed,
				sanguis::client::draw2d::sprite::normal::white()
			)
		);
}
