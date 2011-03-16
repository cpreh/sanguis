#include "bullet.hpp"
#include "../sprite/unit.hpp"
#include "../sprite/index.hpp"
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
	time_type const _time
)
{
	if(
		!origin_
	)
		origin_ = this->center();
	
	model::object::update(
		_time
	);

	funit const
		max_tail_length(
			static_cast<
				funit
			>(
				160
			)
		),
		tail_length(
			std::min(
				fcppt::math::vector::length<
					funit
				>(
					*origin_ - this->center()
				),
				max_tail_length
			)
		);

	vector2 const
		newsize(
			tail_length,
			static_cast<
				funit
			>(
				this->at(
					tail
				).size().h()
			)
		),
		cur_pos(
			fcppt::math::vector::structure_cast<
				vector2
			>(
				this->center()
			)
		),
		newpos( 
			fcppt::math::vector::is_null(
				this->speed()
			)
			?
				cur_pos
			:
				cur_pos
				-
				fcppt::math::vector::normalize(
					this->speed()
				)
				*
				static_cast<
					funit
				>(0.5)
				*
				fcppt::math::vector::length(
				 	newsize
				)
		);

	sge::sprite::center(
		this->at(
			tail
		),
		fcppt::math::vector::structure_cast<
			sprite::point
		>(
			newpos
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
