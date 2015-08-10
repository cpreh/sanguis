#include <sanguis/client/draw2d/entities/model/animation.hpp>
#include <sanguis/client/draw2d/entities/model/optional_sound.hpp>
#include <sanguis/client/draw2d/sprite/animation/texture.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/texture/const_part_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::entities::model::animation::animation(
	sanguis::client::draw2d::sprite::animation::texture &&_texture_animation,
	sanguis::client::load::animation_type const _animation_type,
	sanguis::client::draw2d::entities::model::optional_sound &&_sound
)
:
	texture_animation_(
		std::move(
			_texture_animation
		)
	),
	animation_type_(
		_animation_type
	),
	sound_(
		std::move(
			_sound
		)
	)
{
}

sanguis::client::draw2d::entities::model::animation::animation(
	animation &&
)
= default;

sanguis::client::draw2d::entities::model::animation &
sanguis::client::draw2d::entities::model::animation::operator=(
	animation &&
)
= default;

sanguis::client::draw2d::entities::model::animation::~animation()
{
}

sanguis::client::load::animation_type
sanguis::client::draw2d::entities::model::animation::animation_type() const
{
	return
		animation_type_;
}

sge::texture::const_part_ref const
sanguis::client::draw2d::entities::model::animation::current_texture()
{
	return
		texture_animation_.current_texture();
}

sanguis::client::draw2d::entities::model::optional_sound const &
sanguis::client::draw2d::entities::model::animation::sound() const
{
	return
		sound_;
}

bool
sanguis::client::draw2d::entities::model::animation::ended() const
{
	return
		texture_animation_.ended();
}
