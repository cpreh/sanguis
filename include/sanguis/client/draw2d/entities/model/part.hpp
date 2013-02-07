#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_HPP_INCLUDED

#include <sanguis/animation_type.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/texture_animation.hpp>
#include <sanguis/load/model/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


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
		sanguis::load::model::part const &,
		sanguis::client::draw2d::sprite::normal::object &
	);

	~part();

	bool
	try_animation(
		sanguis::animation_type
	);

	void
	weapon(
		sanguis::weapon_type
	);

	void
	update();

	void
	orientation(
		sanguis::client::draw2d::sprite::rotation
	);

	bool
	ended() const;

	sanguis::client::draw2d::sprite::normal::object &
	object();

	sanguis::client::draw2d::sprite::normal::object const &
	object() const;
private:
	void
	load_animation(
		sanguis::animation_type
	);

	void
	update_orientation(
		sanguis::client::draw2d::sprite::rotation
	);

	sanguis::client::draw2d::sprite::rotation
	orientation() const;

	sanguis::diff_clock const &diff_clock_;

	sanguis::diff_timer rotation_timer_;

	typedef fcppt::optional<
		sanguis::client::draw2d::sprite::rotation
	> optional_rotation;

	optional_rotation desired_orientation_;

	sanguis::load::model::part const &load_part_;

	sanguis::client::draw2d::sprite::normal::object &ref_;

	sanguis::animation_type animation_type_;

	sanguis::weapon_type weapon_;

	typedef fcppt::scoped_ptr<
		sanguis::client::draw2d::sprite::normal::texture_animation
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
