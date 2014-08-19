#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/client/health_pair_fwd.hpp>
#include <sanguis/client/draw2d/entities/other_player.hpp>
#include <sanguis/client/draw2d/entities/player.hpp>
#include <sanguis/client/draw2d/entities/hover/name.hpp>
#include <sanguis/client/draw2d/entities/hover/name_and_health.hpp>
#include <sanguis/client/draw2d/entities/hover/info.hpp>
#include <sanguis/client/draw2d/entities/hover/optional_info.hpp>
#include <sanguis/client/draw2d/entities/hover/optional_name.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>


sanguis::client::draw2d::entities::other_player::other_player(
	sanguis::client::load::auras::context &_aura_context,
	sanguis::client::draw2d::entities::model::load_parameters const &_load_parameters,
	sanguis::aura_type_vector const &_auras,
	sanguis::buff_type_vector const &_buffers,
	sanguis::client::health_pair const _health,
	sanguis::client::draw2d::entities::hover::name const &_name
)
:
	sanguis::client::draw2d::entities::other_player::player(
		_aura_context,
		_load_parameters,
		_auras,
		_buffers,
		_health
	),
	name_(
		_name
	)
{
}

sanguis::client::draw2d::entities::other_player::~other_player()
{
}

sanguis::client::draw2d::entities::hover::optional_info
sanguis::client::draw2d::entities::other_player::hover() const
{
	return
		sanguis::client::draw2d::entities::hover::optional_info(
			sanguis::client::draw2d::entities::hover::info(
				sanguis::client::draw2d::entities::hover::name_and_health(
					sanguis::client::draw2d::entities::hover::optional_name(
						name_
					),
					this->health_pair()
				)
			)
		);
}