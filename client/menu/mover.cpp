#include "mover.hpp"
#include "../../resolution.hpp"
#include "../../random.hpp"
#include <sge/gui/unit.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/dim.hpp>
#include <sge/sprite/object.hpp>
#include <sge/math/constants.hpp>
#include <sge/math/vector/is_null.hpp>
#include <sge/math/vector/normalize.hpp>
#include <sge/math/vector/length.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/dim/arithmetic.hpp>
#include <sge/renderer/color.hpp>
#include <sge/structure_cast.hpp>
#include <sge/assert.hpp>
#include <sge/cerr.hpp>
#include <boost/tr1/random.hpp>
#include <boost/foreach.hpp>
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

sge::gui::point const center_widget(
	sge::gui::widgets::base &w)
{
	return sge::structure_cast<sge::gui::point>(
		sge::structure_cast<sge::gui::dim>(
				sanguis::resolution())/
			static_cast<sge::gui::unit>(2)-
			sge::structure_cast<sge::gui::dim>(
				w.size())/
			static_cast<sge::gui::unit>(2));
}

bool almost_zero(sanguis::client::menu::mover::float_vector const &v)
{
	return 
		std::abs(v.x()) < epsilon && 
		std::abs(v.y()) < epsilon;
}
}

sanguis::client::menu::mover::mover(
	sge::gui::manager &_man,
	sge::gui::widgets::base &_current)
	: man_(_man),
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
	
	current_->relative_pos(
		center_widget(
			*current_));

	current_entry_.current = 
		sge::structure_cast<float_vector>(
			current_->relative_pos());

	current_entry_.target = current_entry_.current;
}

void sanguis::client::menu::mover::update(
	time_type const &t)
{
	float_type const accumulated = 
		static_cast<float_type>(t+remaining_time_);
	
	unsigned iterations = 
		static_cast<unsigned>(
			accumulated/time_step);

	remaining_time_ = 
		static_cast<float_type>(
			accumulated) - 
		static_cast<float_type>(
			iterations)*
		time_step;
	
	for (unsigned i = 0; i < iterations; ++i)
	{
		update_position(
			*current_,
			current_entry_,
			time_step);

		BOOST_FOREACH(container::reference r,to_move_)
		{
			update_position(
				*r.first,
				r.second,
				time_step);
		}
	}

	update_visibility(
		*current_,
		current_entry_);

	BOOST_FOREACH(container::reference r,to_move_)
	{
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
	current_->relative_pos(
		sge::structure_cast<sge::gui::point>(
			current_entry_.current));
	current_entry_.target = 
		sge::structure_cast<float_vector>(
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
	float_vector const 
		diff = e.target - e.current;
	
	if (!almost_zero(diff))
		e.current += 
			static_cast<float_type>(t)*
			speed_*
			sge::math::vector::normalize(diff);

	w.relative_pos(
		sge::structure_cast<sge::gui::point>(
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
				sge::structure_cast<float_vector>(
					diff)))/
			static_cast<float_type>(threshold_);

	sge::renderer::color_channel_8 const max = 
		std::numeric_limits<sge::renderer::color_channel_8>::max();
	
	man_.connected_sprite(w).color(
		sge::renderer::rgba8_color(
				max,
				max,
				max,
				static_cast<sge::renderer::color_channel_8>(
					static_cast<float_type>(
						max)
					*visibility)));
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
