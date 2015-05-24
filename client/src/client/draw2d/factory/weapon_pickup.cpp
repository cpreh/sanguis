#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/weapon_pickup.hpp>
#include <sanguis/client/draw2d/factory/weapon_pickup.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::weapon_pickup(
	sanguis::client::draw2d::entities::load_parameters const &_parameters,
	sanguis::weapon_description const &_weapon_description
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::client::draw2d::entities::base
		>(
			fcppt::make_unique_ptr_fcppt<
				sanguis::client::draw2d::entities::weapon_pickup
			>(
				_parameters,
				_weapon_description
			)
		);
}
