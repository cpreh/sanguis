#include "object.hpp"
#include "z_ordering.hpp"
#include "../sprite/particle/parameters.hpp"
#include "../sprite/particle/texture_animation.hpp"
#include "../sprite/point.hpp"
#include "../sprite/dim.hpp"
#include "../../../load/model/animation_context.hpp"
#include <sge/sprite/animation/texture_impl.hpp>
#include <sge/sprite/intrusive/system_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/center.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init.hpp>
#include <fcppt/math/point_rotate.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>
#include <algorithm>

sanguis::client::draw2d::particle::object::object(
	particle::particle_type::type const _type,
	draw2d::aoe const _aoe,
	load::model::animation_context_ptr _animation_context,
	object::optional_time const _fade_total,
	sprite::particle::system &_particle_system
)
:
	particle::base(
		draw2d::center(
			draw2d::center::value_type::null()
		),
		draw2d::speed(
			draw2d::speed::value_type::null()
		),
		particle::depth(
			0
		),
		particle::rotation(
			0
		),
		particle::rotation_speed(
			0
		)
	),
	sprite_(
		sprite::particle::parameters()
		.system(
			&_particle_system
		)
		.order(
			particle::z_ordering(
				_type
			)
		)
		.size(
			fcppt::math::dim::fill<
				sprite::dim::dim_wrapper::value
			>(
				2
			)
			*
			static_cast<
				sprite::unit
			>(
				_aoe.get()
			)
		)
		.color(
			sge::image::color::rgba8(
				(sge::image::color::init::red %= 1.0)
				(sge::image::color::init::green %= 1.0)
				(sge::image::color::init::blue %= 1.0)
				(sge::image::color::init::alpha %= 1.0)
			)
		)
		.elements()
	),
	animation_context_(
		move(
			_animation_context
		)
	),
	animation_(),
	fade_total_(
		_fade_total
	),
	fade_remaining_(
		fade_total_
		?
			*fade_total_
		:
			static_cast<time_type>(0)
	)
{
}

sanguis::client::draw2d::particle::object::~object()
{
}

bool
sanguis::client::draw2d::particle::object::update(
	sanguis::time_type const _delta,
	draw2d::center const &_center,
	particle::rotation const _rot,
	particle::depth const _depth 
)
{
	animation_context_->update();

	if(
		!animation_
	)
	{
		if(
			!animation_context_->is_finished()
		)
			return false;

		animation_.take(
			fcppt::make_unique_ptr<
				sprite::particle::texture_animation
			>(
				animation_context_->result(),
				fade_total_ 
				?
					sge::sprite::animation::loop_method::repeat
				:
					sge::sprite::animation::loop_method::stop_at_end,
				fcppt::ref(
					sprite_
				),
				clock_.callback()
			)
		);
	}

	base::update(
		_delta,
		_center,
		_rot,
		_depth
	);

	sprite_.z(
		(_depth + base::depth()).get()
	);

	sprite_.rotation(
		(base::rot() + _rot).get()
	);

	sge::sprite::center( 
		sprite_,
		fcppt::math::vector::structure_cast<
			sprite::point
		>(
			fcppt::math::point_rotate(
				(_center + base::center()).get(),
				_center.get(),
				(_rot + base::rot()).get()
			)
		)
	);

	clock_.update(
		_delta
	);

	bool const ret(
		animation_->process()
	);

	if(
		!fade_total_
	)
		return ret;
	
	fade_remaining_ -= _delta;

	funit const ratio(
		static_cast<
			funit
		>(
			fade_remaining_
		)
		/
		static_cast<
			funit
		>(
			*fade_total_
		)
	);

	sprite_.color(
		sge::image::color::rgba8(
			(sge::image::color::init::red %= 1.0)
			(sge::image::color::init::green %= 1.0)
			(sge::image::color::init::blue %= 1.0)
			(sge::image::color::init::alpha %=
				std::max(
					static_cast<funit>(0),
					ratio
				)
			)
		)
	);

	return
		fade_remaining_
		<
		static_cast<
			sanguis::time_type
		>(
			0
		);
}
