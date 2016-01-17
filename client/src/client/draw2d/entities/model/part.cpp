#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/entities/model/desired_orientation.hpp>
#include <sanguis/client/draw2d/entities/model/loop_method.hpp>
#include <sanguis/client/draw2d/entities/model/make_sound.hpp>
#include <sanguis/client/draw2d/entities/model/orientation.hpp>
#include <sanguis/client/draw2d/entities/model/part.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/animation/loop_method.hpp>
#include <sanguis/client/draw2d/sprite/animation/texture.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <sanguis/client/load/model/animation.hpp>
#include <sanguis/client/load/model/part.hpp>
#include <sanguis/client/load/model/weapon_category.hpp>
#include <sge/audio/buffer_fwd.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/do_pause.hpp>
#include <sge/audio/sound/pause_or_resume.hpp>
#include <sge/texture/const_part_ref.hpp>
#include <sge/timer/elapsed_fractional_and_reset.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/diff.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::entities::model::part::part(
	sanguis::diff_clock const &_diff_clock,
	sanguis::client::sound_manager &_sound_manager,
	sanguis::client::load::model::part const &_load_part,
	sanguis::optional_primary_weapon_type const _weapon,
	sanguis::client::draw2d::sprite::rotation const _rotation,
	sanguis::client::load::animation_type const _animation_type
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
	desired_orientation_(
		_rotation
	),
	load_part_(
		_load_part
	),
	weapon_(
		_weapon
	),
	animation_(
		this->load_animation(
			_animation_type
		)
	)
{
}

sanguis::client::draw2d::entities::model::part::part(
	part &&
)
= default;

sanguis::client::draw2d::entities::model::part &
sanguis::client::draw2d::entities::model::part::operator=(
	part &&
)
= default;

sanguis::client::draw2d::entities::model::part::~part()
{
}

void
sanguis::client::draw2d::entities::model::part::pause(
	bool const _value
)
{
	fcppt::optional::maybe_void(
		animation_.sound(),
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

void
sanguis::client::draw2d::entities::model::part::animation(
	sanguis::client::load::animation_type const _animation_type
)
{
	if(
		animation_.animation_type()
		==
		_animation_type
	)
		return;

	animation_ =
		this->load_animation(
			_animation_type
		);
}

void
sanguis::client::draw2d::entities::model::part::weapon(
	sanguis::optional_primary_weapon_type const _weapon
)
{
	weapon_ =
		_weapon;
}

void
sanguis::client::draw2d::entities::model::part::update(
	sanguis::client::draw2d::sprite::normal::object &_sprite
)
{
	_sprite.texture(
		animation_.current_texture()
	);

	fcppt::optional::maybe_void(
		animation_.sound(),
		[](
			sge::audio::sound::base_unique_ptr const &_sound
		)
		{
			_sound->update();
		}
	);

	if(
		fcppt::math::diff(
			_sprite.rotation(),
			desired_orientation_.get().get()
		)
		>
		fcppt::literal<
			sanguis::client::draw2d::sprite::rotation::value_type
		>(
			0.001
		)
	)
		_sprite.rotation(
			sanguis::client::draw2d::entities::model::orientation(
				sge::timer::elapsed_fractional_and_reset<
					sanguis::client::draw2d::funit
				>(
					rotation_timer_
				),
				sanguis::client::draw2d::sprite::rotation{
					_sprite.rotation()
				},
				desired_orientation_
			).get()
		);
}

void
sanguis::client::draw2d::entities::model::part::orientation(
	sanguis::client::draw2d::sprite::rotation const _rot
)
{
	desired_orientation_ =
		sanguis::client::draw2d::entities::model::desired_orientation{
			_rot
		};
}

bool
sanguis::client::draw2d::entities::model::part::ended() const
{
	return
		animation_.ended();
}

sge::texture::const_part_ref
sanguis::client::draw2d::entities::model::part::texture()
{
	return
		animation_.current_texture();
}

sanguis::client::draw2d::entities::model::animation
sanguis::client::draw2d::entities::model::part::load_animation(
	sanguis::client::load::animation_type const _animation_type
)
{
	sanguis::client::load::model::animation const &animation(
		load_part_.get()[
			weapon_
		][
			_animation_type
		]
	);

	sanguis::client::draw2d::sprite::animation::loop_method const loop_method(
		sanguis::client::draw2d::entities::model::loop_method(
			_animation_type
		)
	);

	return
		sanguis::client::draw2d::entities::model::animation{
			sanguis::client::draw2d::sprite::animation::texture{
				animation.series(),
				loop_method,
				diff_clock_.get()
			},
			_animation_type,
			fcppt::optional::bind(
				animation.sound(),
				[
					this,
					loop_method
				](
					fcppt::reference<
						sge::audio::buffer
					> const _buffer
				)
				{
					return
						sanguis::client::draw2d::entities::model::make_sound(
							_buffer.get(),
							sound_manager_.get(),
							loop_method
						);
				}
			)
		};
}
