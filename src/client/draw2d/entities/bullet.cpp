#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/speed_is_null.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/bullet.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/needs_healthbar.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/client/draw2d/sprite/index.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sge/sprite/center.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/normalize.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


namespace
{

sanguis::client::draw2d::sprite::index const
	tail(1);

}

sanguis::client::draw2d::entities::bullet::bullet(
	sanguis::client::draw2d::entities::model::parameters const &_param,
	fcppt::string const &_name
)
:
	sanguis::client::draw2d::entities::model::object(
		_param,
		_name,
		sanguis::client::draw2d::entities::order_vector{
			sanguis::client::draw2d::z_ordering::bullet,
			sanguis::client::draw2d::z_ordering::bullet
		},
		sanguis::client::draw2d::entities::model::needs_healthbar::no,
		sanguis::client::draw2d::entities::model::decay_option::immediate
	),
	origin_()
{
	this->at(
		tail
	).w(
		fcppt::literal<
			sanguis::client::draw2d::sprite::unit
		>(
			3
		)
	); // TODO: which value is best here?
}

sanguis::client::draw2d::entities::bullet::~bullet()
{
}

void
sanguis::client::draw2d::entities::bullet::update()
{
	if(
		!origin_
	)
		origin_ = this->center();

	sanguis::client::draw2d::entities::model::object::update();

	sanguis::client::draw2d::funit const
		max_tail_length(
			static_cast<
				draw2d::funit
			>(
				160
			)
		),
		tail_length(
			std::min(
				fcppt::math::vector::length<
					sanguis::client::draw2d::funit
				>(
					(
						*origin_ - this->center()
					).get()
				),
				max_tail_length
			)
		);

	sanguis::client::draw2d::center const cur_center(
		fcppt::math::vector::structure_cast<
			sanguis::client::draw2d::center::value_type
		>(
			this->center().get()
		)
	);

	sanguis::client::draw2d::center const new_center(
		sanguis::client::draw2d::speed_is_null(
			this->speed()
		)
		?
			cur_center
		:
			sanguis::client::draw2d::center(
				cur_center.get()
				-
				fcppt::math::vector::normalize(
					this->speed().get()
				)
				*
				static_cast<
					draw2d::funit
				>(
					0.5
				)
				*
				fcppt::math::vector::length(
					sanguis::client::draw2d::vector2(
						tail_length,
						static_cast<
							sanguis::client::draw2d::funit
						>(
							this->at(
								tail
							).size().h()
						)
					)
				)
			)
	);

	sge::sprite::center(
		this->at(
			tail
		),
		fcppt::math::vector::structure_cast<
			sanguis::client::draw2d::sprite::point
		>(
			new_center.get()
		)
	);

	this->at(
		tail
	).w(
		static_cast<
			sanguis::client::draw2d::sprite::unit
		>(
			tail_length
		)
	);
}
