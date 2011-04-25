#include "bullet.hpp"
#include "../sprite/index.hpp"
#include "../sprite/point.hpp"
#include "../sprite/unit.hpp"
#include "../center.hpp"
#include "../funit.hpp"
#include "../vector2.hpp"
#include "../z_ordering.hpp"
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/center.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/is_null.hpp>
#include <fcppt/math/vector/normalize.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional_impl.hpp>

namespace
{

sanguis::client::draw2d::sprite::index const
	tail(1);

}

sanguis::client::draw2d::entities::bullet::bullet(
	model::parameters const &_param,
	fcppt::string const &_name
)
:
	model::object(
		_param,
		_name,
		z_ordering::bullet,
		model::needs_healthbar::no,
		model::decay_option::immediate
	),
	origin_()
{
	this->at(
		tail
	).w(
		static_cast<sprite::unit>(3)
	); // TODO: which value is best here?
}

sanguis::client::draw2d::entities::bullet::~bullet()
{
}

void
sanguis::client::draw2d::entities::bullet::update(
	sanguis::time_delta const &_time
)
{
	if(
		!origin_
	)
		origin_ = this->center();
	
	model::object::update(
		_time
	);

	draw2d::funit const
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
					funit
				>(
					(
						*origin_ - this->center()
					).get()
				),
				max_tail_length
			)
		);

	draw2d::center const cur_center(
		fcppt::math::vector::structure_cast<
			draw2d::center::value_type
		>(
			this->center().get()
		)
	);
	
	draw2d::center const new_center( 
		fcppt::math::vector::is_null(
			this->speed().get()
		)
		?
			cur_center
		:
			draw2d::center(
				cur_center.get()
				-
				fcppt::math::vector::normalize(
					this->speed().get()
				)
				*
				static_cast<
					funit
				>(
					0.5
				)
				*
				fcppt::math::vector::length(
					draw2d::vector2(
						tail_length,
						static_cast<
							funit
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
			sprite::point
		>(
			new_center.get()
		)
	);

	this->at(
		tail
	).w(
		static_cast<
			sprite::unit
		>(
			tail_length
		)
	);
}
