#include <sanguis/doodad_type.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/constant_order.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/factory/doodad.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/white.hpp>
#include <sanguis/load/model/doodad_path.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::doodad(
	sanguis::client::draw2d::entities::load_parameters const &_parameters,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::client::draw2d::sprite::rotation const _rotation,
	sanguis::doodad_type const _doodad_type
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::client::draw2d::entities::base
		>(
			fcppt::make_unique_ptr_fcppt<
				sanguis::client::draw2d::entities::model::object
			>(
				sanguis::client::draw2d::entities::model::parameters(
					_parameters,
					sanguis::load::model::doodad_path(
						_doodad_type
					),
					sanguis::client::draw2d::entities::constant_order(
						sanguis::client::draw2d::z_ordering::ground
					),
					sanguis::client::optional_health_pair(),
					sanguis::client::draw2d::entities::model::decay_option::immediate,
					sanguis::optional_primary_weapon_type(),
					sanguis::weapon_status::nothing,
					sanguis::client::draw2d::speed{
						sanguis::client::draw2d::speed::value_type::null()
					},
					_center,
					_rotation,
					sanguis::client::draw2d::sprite::normal::white()
				)
			)
		);
}
