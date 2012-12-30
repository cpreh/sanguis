#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/texture_animation.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/animation_type.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/load/model/part_fwd.hpp>
#include <sanguis/load/model/animation/context_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/scoped_ptr.hpp>

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

class part
{
	FCPPT_NONCOPYABLE(
		part
	);
public:
	part(
		sanguis::diff_clock const &,
		load::model::part const &,
		sprite::normal::object &ref
	);

	~part();

	bool
	try_animation(
		animation_type::type
	);

	void
	weapon(
		sanguis::weapon_type
	);

	void
	update();

	void
	orientation(
		sprite::rotation
	);

	bool
	ended() const;

	sprite::normal::object &
	object();

	sprite::normal::object const &
	object() const;
private:
	typedef fcppt::scoped_ptr<
		load::model::animation::context
	> animation_context_ptr;

	void
	load_animation(
		animation_type::type
	);

	void
	update_orientation(
		sprite::rotation
	);

	sprite::rotation
	orientation() const;

	sanguis::diff_clock const &diff_clock_;

	sanguis::diff_timer rotation_timer_;

	typedef fcppt::optional<
		sprite::rotation
	> optional_rotation;

	optional_rotation desired_orientation_;

	load::model::part const &load_part_;

	sprite::normal::object &ref_;

	sanguis::animation_type::type animation_type_;

	sanguis::weapon_type weapon_;

	animation_context_ptr animation_context_;

	typedef fcppt::scoped_ptr<
		sprite::normal::texture_animation
	> scoped_texture_animation;

	scoped_texture_animation animation_;

	bool animation_ended_;
};

}
}
}
}
}

#endif
