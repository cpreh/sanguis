#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_ANIMATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_ANIMATION_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/model/animation_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/optional_sound.hpp>
#include <sanguis/client/draw2d/sprite/animation/texture.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <sge/texture/const_part_ref_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace model
{

class animation
{
	FCPPT_NONCOPYABLE(
		animation
	);
public:
	animation(
		sanguis::client::draw2d::sprite::animation::texture &&,
		sanguis::client::load::animation_type,
		sanguis::client::draw2d::entities::model::optional_sound &&
	);

	animation(
		animation &&
	);

	animation &
	operator=(
		animation &&
	);

	~animation();

	sanguis::client::load::animation_type
	animation_type() const;

	sge::texture::const_part_ref
	current_texture();

	sanguis::client::draw2d::entities::model::optional_sound const &
	sound() const;

	bool
	ended() const;
private:
	sanguis::client::draw2d::sprite::animation::texture texture_animation_;

	sanguis::client::load::animation_type animation_type_;

	sanguis::client::draw2d::entities::model::optional_sound sound_;
};

}
}
}
}
}

#endif
