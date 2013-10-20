#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/player.hpp>
#include <sanguis/client/draw2d/entities/with_auras_model_parameters.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model_parameters.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/name.hpp>
#include <sanguis/client/draw2d/entities/model/needs_healthbar.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/index.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/load/auras/context_fwd.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/point_rotate.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/signed_angle_between_cast.hpp>


namespace
{

sanguis::client::draw2d::sprite::point const
	player_body_center(25,32),
	player_leg_center(32,32);

sanguis::client::draw2d::sprite::index const
	top(1),
	bottom(0);

}

sanguis::client::draw2d::entities::player::player(
	sanguis::load::auras::context &_auras_load_context,
	sanguis::client::draw2d::entities::model::load_parameters const &_load_parameters,
	sanguis::aura_type_vector const &_auras,
	sanguis::buff_type_vector const &_buffs
)
:
	sanguis::client::draw2d::entities::with_buffs_auras_model(
		sanguis::client::draw2d::entities::with_buffs_auras_model_parameters(
			_load_parameters.diff_clock(),
			_load_parameters.normal_system(),
			_load_parameters.collection(),
			_buffs,
			sanguis::client::draw2d::entities::with_auras_model_parameters(
				_load_parameters.diff_clock(),
				_auras_load_context,
				_load_parameters.normal_system(),
				_auras,
				sanguis::client::draw2d::entities::model::parameters(
					_load_parameters,
					sanguis::client::draw2d::entities::model::name(
						FCPPT_TEXT("player")
					),
					sanguis::client::draw2d::entities::order_vector{
						sanguis::client::draw2d::z_ordering::player_lower,
						sanguis::client::draw2d::z_ordering::player_upper
					},
					sanguis::client::draw2d::entities::model::needs_healthbar::yes,
					sanguis::client::draw2d::entities::model::decay_option::delayed
				)
			)
		)
	)
{
}

sanguis::client::draw2d::entities::player::~player()
{
}

void
sanguis::client::draw2d::entities::player::speed(
	sanguis::client::draw2d::speed const &_speed
)
{
	sanguis::client::draw2d::entities::model::object::speed(
		_speed
	);

	if(
		this->walking()
	)
		sanguis::client::draw2d::entities::model::object::orientation(
			fcppt::math::vector::signed_angle_between_cast<
				sanguis::client::draw2d::funit
			>(
				sanguis::client::draw2d::vector2::null(),
				_speed.get()
			),
			bottom
		);
}

void
sanguis::client::draw2d::entities::player::orientation(
	sanguis::client::draw2d::sprite::rotation const _orientation
)
{
	sanguis::client::draw2d::entities::model::object::orientation(
		_orientation,
		top // TODO
	); // TODO: better interface for this in model
}

void
sanguis::client::draw2d::entities::player::update()
{
	sanguis::client::draw2d::entities::with_buffs_auras_model::update();

	sanguis::client::draw2d::vector2 const
		leg_center(
			fcppt::math::vector::structure_cast<
				sanguis::client::draw2d::vector2
			>(
				player_leg_center
			)
		),
		body_center(
			fcppt::math::vector::structure_cast<
				sanguis::client::draw2d::vector2
			>(
				player_body_center
			)
		);

	sanguis::client::draw2d::sprite::rotation const sprite_rotation(
		this->at(
			bottom
		).rotation()
	);

	sanguis::client::draw2d::vector2 const new_rotation(
		fcppt::math::point_rotate(
			leg_center,
			fcppt::math::dim::structure_cast<
				sanguis::client::draw2d::vector2
			>(
				this->at(
					bottom
				).size()
				/
				fcppt::literal<
					sanguis::client::draw2d::sprite::unit
				>(
					2
				)
			),
			sprite_rotation
		)
	);

	sanguis::client::draw2d::vector2 const
		rot_abs(
			fcppt::math::vector::structure_cast<
				sanguis::client::draw2d::vector2
			>(
				this->at(
					bottom
				).pos()
			)
			+
			new_rotation
		),
		top_pos(
			rot_abs - body_center
		);

	this->at(
		top
	).pos(
		fcppt::math::vector::structure_cast<
			sanguis::client::draw2d::sprite::point
		>(
			top_pos
		)
	);
}

sanguis::client::draw2d::sprite::dim const
sanguis::client::draw2d::entities::player::bounding_dim() const
{
	return
		this->at(
			top
		).size();
}
