#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/client/sound_manager.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/entities/model/clamp_orientation.hpp>
#include <sanguis/client/draw2d/entities/model/loop_method.hpp>
#include <sanguis/client/draw2d/entities/model/orientation.hpp>
#include <sanguis/client/draw2d/entities/model/part.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/animation/loop_method.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/texture_animation_decl.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <sanguis/client/load/optional_animation_type.hpp>
#include <sanguis/client/load/model/animation.hpp>
#include <sanguis/client/load/model/base_animation_not_found.hpp>
#include <sanguis/client/load/model/part.hpp>
#include <sanguis/client/load/model/weapon_category.hpp>
#include <sanguis/client/load/resource/animation/series.hpp>
#include <sge/audio/buffer.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/do_pause.hpp>
#include <sge/audio/sound/nonpositional_parameters.hpp>
#include <sge/audio/sound/pause_or_resume.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/timer/elapsed_fractional_and_reset.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/optional_comparison.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/diff.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_signed.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::entities::model::part::part(
	sanguis::diff_clock const &_diff_clock,
	sanguis::client::sound_manager &_sound_manager,
	sanguis::client::load::model::part const &_load_part,
	sanguis::client::draw2d::sprite::normal::object &_ref
)
:
	diff_clock_(
		_diff_clock
	),
	sound_manager_(
		_sound_manager
	),
	rotation_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			std::chrono::seconds(
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
	animation_type_(),
	weapon_(),
	animation_(),
	animation_ended_(
		false
	),
	sound_()
{
	ref_.size(
		sprite::dim::null()
	);
}

sanguis::client::draw2d::entities::model::part::~part()
{
}

void
sanguis::client::draw2d::entities::model::part::pause(
	bool const _value
)
{
	fcppt::maybe_void(
		sound_,
		[
			_value
		](
			sge::audio::sound::base_unique_ptr const &_sound
		)
		{
			sge::audio::sound::pause_or_resume(
				*_sound,
				sge::audio::sound::do_pause(
					_value
				)
			);
		}
	);
}

bool
sanguis::client::draw2d::entities::model::part::try_animation(
	sanguis::client::load::animation_type const _atype
)
{
	if(
		animation_type_
		==
		sanguis::client::load::optional_animation_type(
			_atype
		)
	)
		return
			true;

	if(
		!load_part_[
			weapon_
		].has_animation(
			_atype
		)
	)
		return
			false;

	this->load_animation(
		_atype
	);

	animation_type_ =
		sanguis::client::load::optional_animation_type(
			_atype
		);

	return
		true;
}

void
sanguis::client::draw2d::entities::model::part::weapon(
	sanguis::optional_primary_weapon_type const _weapon
)
{
	// we lose the animation here
	// which model has to reset
	weapon_ = _weapon;

	animation_type_ =
		sanguis::client::load::optional_animation_type();
}

void
sanguis::client::draw2d::entities::model::part::update()
{
	fcppt::maybe_void(
		animation_,
		[
			this
		](
			scoped_texture_animation const &_animation
		)
		{
			animation_ended_ =
				_animation->process()
				||
				animation_ended_;
		}
	);

	fcppt::maybe_void(
		sound_,
		[](
			sge::audio::sound::base_unique_ptr const &_sound
		)
		{
			_sound->update();
		}
	);

	fcppt::maybe_void(
		desired_orientation_,
		[
			this
		](
			sanguis::client::draw2d::sprite::rotation const _rotation
		)
		{

			if(
				fcppt::math::diff(
					this->orientation(),
					_rotation
				)
				<
				fcppt::literal<
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
					_rotation
				)
			);
		}
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
		!desired_orientation_.has_value()
	)
		this->update_orientation(
			_rot
		);

	desired_orientation_ =
		optional_rotation(
			_rot
		);
}

bool
sanguis::client::draw2d::entities::model::part::ended() const
{
	return
		animation_ended_;
}

sanguis::client::draw2d::sprite::normal::object &
sanguis::client::draw2d::entities::model::part::object()
{
	return
		ref_;
}

sanguis::client::draw2d::sprite::normal::object const &
sanguis::client::draw2d::entities::model::part::object() const
{
	return
		ref_;
}

void
sanguis::client::draw2d::entities::model::part::load_animation(
	sanguis::client::load::animation_type const _atype
)
{
	sanguis::client::load::model::animation const &animation(
		load_part_[
			weapon_
		][
			_atype
		]
	);

	sanguis::client::load::resource::animation::series const &series(
		animation.series()
	);

	sanguis::client::draw2d::sprite::animation::loop_method const loop_method(
		sanguis::client::draw2d::entities::model::loop_method(
			_atype
		)
	);

	animation_ =
		optional_scoped_texture_animation(
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::sprite::normal::texture_animation
			>(
				series,
				loop_method,
				ref_,
				diff_clock_
			)
		);

	ref_.size(
		fcppt::math::dim::structure_cast<
			sanguis::client::draw2d::sprite::dim,
			fcppt::cast::size_fun
		>(
			fcppt::math::dim::to_signed(
				series.begin()->dim()
			)
		)
	);

	sound_ =
		optional_sound();

	fcppt::maybe_void(
		animation.sound(),
		[
			loop_method,
			this
		](
			sge::audio::buffer &_buffer
		)
		{
			switch(
				loop_method
			)
			{
			case sanguis::client::draw2d::sprite::animation::loop_method::stop_at_end:
				sound_manager_.add(
					_buffer.create_nonpositional(
						sge::audio::sound::nonpositional_parameters()
					)
				);

				break;
			case sanguis::client::draw2d::sprite::animation::loop_method::repeat:
				{
					sge::audio::sound::base_unique_ptr new_sound(
						_buffer.create_nonpositional(
							sge::audio::sound::nonpositional_parameters()
						)
					);

					new_sound->play(
						sge::audio::sound::repeat::loop
					);

					sound_ =
						optional_sound(
							std::move(
								new_sound
							)
						);
				}
				break;
			}
		}
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
	return
		ref_.rotation();
}
