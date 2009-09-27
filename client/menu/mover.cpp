#include "mover.hpp"
#include "../../resolution.hpp"
#include "../../random.hpp"
#include <sge/gui/unit.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/dim.hpp>
#include <sge/sprite/object.hpp>
#include <sge/math/pi.hpp>
#include <sge/math/vector/is_null.hpp>
#include <sge/math/vector/normalize.hpp>
#include <sge/math/vector/length.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <sge/math/dim/arithmetic.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init.hpp>
#include <sge/assert.hpp>
#include <boost/foreach.hpp>
#include <tr1/random>
#include <algorithm>
#include <limits>
#include <cmath>

namespace
{
sanguis::client::menu::mover::float_type const 
	time_step = 
		static_cast<sanguis::client::menu::mover::float_type>(0.001),
	epsilon = 
		static_cast<sanguis::client::menu::mover::float_type>(3.0);

sge::gui::point const center(
	sge::gui::dim const &d)
{
	return sge::math::dim::structure_cast<
		sge::gui::point
	>(
		sge::math::dim::structure_cast<
			sge::gui::dim
		>(
			sanguis::resolution()
		)/
		static_cast<sge::gui::unit>(2) -
		d /
		static_cast<sge::gui::unit>(2)
	);
}

sge::gui::point const center_widget(
	sge::gui::widgets::base &w)
{
	return center(w.size());
}
}

sanguis::client::menu::mover::mover(
	sge::gui::manager &_man,
	sge::gui::widgets::base &_current)
:
	man_(_man),
	current_(&_current),
	current_entry_(),
	to_move_(),
	speed_(
		static_cast<float_type>(500)),
	push_distance_(
		static_cast<float_type>(200)),
	threshold_(
		static_cast<float_type>(50)),
	remaining_time_(
		static_cast<float_type>(0))
{
	SGE_ASSERT(!_current.has_parent());
	SGE_ASSERT(_current.activation() == sge::gui::activation_state::inactive);

	current_->activation(
		sge::gui::activation_state::active);
	
	/*
	current_->pos_hint(
		center_widget_hinted(
			*current_));
			*/
	current_->pos_hint(
		center(
			*current_->size_hint()));

	current_entry_.current = 
		sge::math::vector::structure_cast<float_vector>(
			current_->relative_pos());

	current_entry_.target = current_entry_.current;
}

void sanguis::client::menu::mover::update(
	time_type const &t)
{
	update_position(
		*current_,
		current_entry_,
		t);

	update_visibility(
		*current_,
		current_entry_);

	BOOST_FOREACH(container::reference r,to_move_)
	{
		update_position(
			*r.first,
			r.second,
			t);

		update_visibility(
			*r.first,
			r.second);
	}
}

void sanguis::client::menu::mover::reset(
	sge::gui::widgets::base &w)
{
	SGE_ASSERT(to_move_.find(current_) == to_move_.end());

	to_move_[current_].current = current_entry_.current;
	to_move_[current_].target = random_pos();

	current_->activation(
		sge::gui::activation_state::inactive);
	man_.connected_sprite(*current_).visible(true);

	to_move_.erase(&w);

	current_ = &w;
	current_entry_.current = random_pos();
	current_->pos_hint(
		sge::math::vector::structure_cast<sge::gui::point>(
			current_entry_.current));
	current_entry_.target = 
		sge::math::vector::structure_cast<float_vector>(
			center_widget(
				w));
	current_->activation(
		sge::gui::activation_state::active);
}

void sanguis::client::menu::mover::update_position(
	sge::gui::widgets::base &w,
	entry &e,
	time_type const &t)
{
	float_vector const diff = 
		e.target - e.current,
		normdiff = sge::math::vector::normalize(
			diff),
		projected = 
			normdiff * 
			static_cast<float_type>(t) * 
			speed_;
	
	if (sge::math::vector::is_null(diff) || sge::math::vector::is_null(projected))
		return;

	e.current += 
		normdiff * 
		std::min(
			sge::math::vector::length(diff),
			sge::math::vector::length(projected));

	w.pos_hint(
		sge::math::vector::structure_cast<sge::gui::point>(
			e.current));
}

void sanguis::client::menu::mover::update_visibility(
	sge::gui::widgets::base &w,
	entry const &e)
{
	float_vector const diff = 
		current_entry_.target - e.current;

	float_type const visibility = 
		static_cast<float_type>(1)-
		std::min(
			static_cast<float_type>(
				threshold_),
			sge::math::vector::length(
				sge::math::vector::structure_cast<float_vector>(
					diff)))/
			static_cast<float_type>(threshold_);

	man_.connected_sprite(w).color(
		sge::image::color::rgba8(
			sge::image::color::init::red %= 1.0,
			sge::image::color::init::green %= 1.0,
			sge::image::color::init::blue %= 1.0,
			sge::image::color::init::alpha =
			static_cast<
				sge::image::color::channel8
			>(
				static_cast<float_type>(
					sge::image::color::rgba8::format::channel_max<
						mizuiro::color::channel::alpha
					>()
				)
				* visibility
			)
		)
	);
}

sanguis::client::menu::mover::float_vector const sanguis::client::menu::mover::random_pos() const
{
	typedef std::tr1::uniform_real<
		float_type
	> uniform_float;

	typedef std::tr1::variate_generator<
		rand_gen_type,
		uniform_float
	> rng_type;

	static rng_type angle(
		create_seeded_randgen(),
		uniform_float(
			static_cast<float_type>(0),
			static_cast<float_type>(2)*sge::math::pi<float_type>()
		));
	
	float_type const new_angle = 
		angle();
	
	float_vector const addition = float_vector(
		push_distance_*
		std::cos(new_angle),
		push_distance_*
		std::sin(new_angle));
	
	return addition;
}
