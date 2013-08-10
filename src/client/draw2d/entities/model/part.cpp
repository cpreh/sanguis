#include <sanguis/animation_type.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/entities/model/part.hpp>
#include <sanguis/client/draw2d/entities/model/clamp_orientation.hpp>
#include <sanguis/client/draw2d/entities/model/loop_method.hpp>
#include <sanguis/client/draw2d/entities/model/orientation.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/animation/texture_impl.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/texture_animation.hpp>
#include <sanguis/load/model/animation.hpp>
#include <sanguis/load/model/base_animation_not_found.hpp>
#include <sanguis/load/model/part.hpp>
#include <sanguis/load/model/weapon_category.hpp>
#include <sanguis/load/resource/animation/series.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/timer/elapsed_fractional_and_reset.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/diff.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::entities::model::part::part(
	sanguis::diff_clock const &_diff_clock,
	sanguis::load::model::part const& _load_part,
	sanguis::client::draw2d::sprite::normal::object &_ref
)
:
	diff_clock_(
		_diff_clock
	),
	rotation_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			boost::chrono::seconds(
				1
			)
		)
	),
	desired_orientation_(),
	load_part_(
		_load_part
	),
	ref_(
		_ref
	),
	animation_type_(
		sanguis::animation_type::size
	),
	weapon_(),
	animation_(),
	animation_ended_(
		false
	)
{
	ref_.size(
		sprite::dim::null()
	);
}

sanguis::client::draw2d::entities::model::part::~part()
{
}

bool
sanguis::client::draw2d::entities::model::part::try_animation(
	sanguis::animation_type const _atype
)
{
	if(
		animation_type_ == _atype
	)
		return true;

	if(
		!load_part_[
			weapon_
		].has_animation(
			_atype
		)
	)
		return false;

	this->load_animation(
		_atype
	);

	animation_type_ = _atype;

	return true;
}

void
sanguis::client::draw2d::entities::model::part::weapon(
	sanguis::optional_primary_weapon_type const _weapon
)
{
	// we lose the animation here
	// which model has to reset
	weapon_ = _weapon;

	animation_type_ = sanguis::animation_type::size;
}

void
sanguis::client::draw2d::entities::model::part::update()
{
	if(
		animation_
	)
		animation_ended_ = animation_->process() || animation_ended_;

	if(
		!desired_orientation_
	)
		return;

	if(
		fcppt::math::diff(
			this->orientation(),
			*desired_orientation_
		)
		<
		static_cast<
			sanguis::client::draw2d::sprite::rotation
		>(
			0.001
		)
	)
		return;

	this->update_orientation(
		sanguis::client::draw2d::entities::model::orientation(
			sge::timer::elapsed_fractional_and_reset<
				sanguis::client::draw2d::funit
			>(
				rotation_timer_
			),
			this->orientation(),
			*desired_orientation_
		)
	);
}

void
sanguis::client::draw2d::entities::model::part::orientation(
	sanguis::client::draw2d::sprite::rotation _rot
)
{
	_rot =
		sanguis::client::draw2d::entities::model::clamp_orientation(
			_rot
		);

	if(
		!desired_orientation_
	)
		this->update_orientation(
			_rot
		);

	desired_orientation_ = _rot;
}

bool
sanguis::client::draw2d::entities::model::part::ended() const
{
	return animation_ended_;
}

sanguis::client::draw2d::sprite::normal::object &
sanguis::client::draw2d::entities::model::part::object()
{
	return ref_;
}

sanguis::client::draw2d::sprite::normal::object const &
sanguis::client::draw2d::entities::model::part::object() const
{
	return ref_;
}

void
sanguis::client::draw2d::entities::model::part::load_animation(
	sanguis::animation_type const _atype
)
{
	sanguis::load::resource::animation::series const &series(
		load_part_[
			weapon_
		][
			_atype
		].series()
	);

	FCPPT_ASSERT_ERROR(
		!series.empty()
	);

	animation_.take(
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::sprite::normal::texture_animation
		>(
			series,
			sanguis::client::draw2d::entities::model::loop_method(
				_atype
			),
			ref_,
			diff_clock_
		)
	);

	ref_.size(
		fcppt::math::dim::structure_cast<
			sanguis::client::draw2d::sprite::dim
		>(
			series.begin()->dim()
		)
	);
}

void
sanguis::client::draw2d::entities::model::part::update_orientation(
	sanguis::client::draw2d::sprite::rotation const _rot
)
{
	ref_.rotation(
		_rot
	);
}

sanguis::client::draw2d::sprite::rotation
sanguis::client::draw2d::entities::model::part::orientation() const
{
	return ref_.rotation();
}
