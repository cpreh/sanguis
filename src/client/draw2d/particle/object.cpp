#include <sanguis/client/draw2d/particle/object.hpp>
#include <sanguis/client/draw2d/particle/z_ordering.hpp>
#include <sanguis/client/draw2d/sprite/animation/texture_impl.hpp>
#include <sanguis/client/draw2d/sprite/particle/parameters.hpp>
#include <sanguis/client/draw2d/sprite/particle/texture_animation.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/system_decl.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/load/model/animation/context.hpp>
#include <sanguis/duration_second.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init.hpp>
#include <sge/sprite/intrusive/connection.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/center.hpp>
#include <sge/timer/remaining_fractional.hpp>
#include <fcppt/chrono/duration_arithmetic.hpp>
#include <fcppt/chrono/duration_comparison.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/math/point_rotate.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>

sanguis::client::draw2d::particle::object::object(
	sanguis::diff_clock const &_diff_clock,
	particle::particle_type::type const _type,
	draw2d::aoe const _aoe,
	load::model::animation::context_ptr _animation_context,
	object::optional_time const _fade_total,
	sprite::particle::system &_particle_system
)
:
	particle::base(
		_diff_clock,
		draw2d::center(
			draw2d::center::value_type::null()
		),
		draw2d::speed(
			draw2d::speed::value_type::null()
		),
		particle::depth(
			0.f
		),
		particle::rotation(
			0.f
		),
		particle::rotation_speed(
			0.f
		)
	),
	diff_clock_(
		_diff_clock
	),
	sprite_(
		sprite::particle::parameters()
		.connection(
			_particle_system.connection(
				particle::z_ordering(
					_type
				)
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
				(sge::image::color::init::red() %= 1.0)
				(sge::image::color::init::green() %= 1.0)
				(sge::image::color::init::blue() %= 1.0)
				(sge::image::color::init::alpha() %= 1.0)
			)
		)
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
	fade_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			fade_total_
			?
				*fade_total_
			:
				sanguis::duration_second(
					0
				)
		)
	)
{
}

sanguis::client::draw2d::particle::object::~object()
{
}

bool
sanguis::client::draw2d::particle::object::update(
	draw2d::center const &_center,
	particle::rotation const _rot,
	particle::depth const _depth
)
{
	if(
		!animation_
	)
	{
		animation_context_->update();

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
					sprite::animation::loop_method::repeat
				:
					sprite::animation::loop_method::stop_at_end,
				fcppt::ref(
					sprite_
				),
				fcppt::cref(
					diff_clock_
				)
			)
		);
	}

	base::update(
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

	bool const ret(
		animation_->process()
	);

	if(
		!fade_total_
	)
		return ret;

	sprite_.color(
		sge::image::color::rgba8(
			(sge::image::color::init::red() %= 1.0)
			(sge::image::color::init::green() %= 1.0)
			(sge::image::color::init::blue() %= 1.0)
			(sge::image::color::init::alpha() %=
				sge::timer::remaining_fractional<
					draw2d::funit
				>(
					fade_timer_
				)
			)
		)
	);

	return
		fade_timer_.expired();
}
