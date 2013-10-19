#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/transform_callback.hpp>
#include <sanguis/client/draw2d/entities/own_player.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/factory/own_player.hpp>
#include <sanguis/load/auras/context_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::own_player(
	sanguis::load::auras::context &_auras_load_context,
	sanguis::client::draw2d::entities::model::load_parameters const &_parameters,
	sanguis::client::draw2d::transform_callback const &_transform,
	sanguis::client::draw2d::collide_callback const &_collide,
	sanguis::aura_type_vector const &_auras,
	sanguis::buff_type_vector const &_buffs
)
{
	return
		sanguis::client::draw2d::entities::unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::entities::own_player
			>(
				_auras_load_context,
				_parameters,
				_transform,
				_collide,
				_auras,
				_buffs
			)
		);
}
