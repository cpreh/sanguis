#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/object_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/texture_animation_fwd.hpp>
#include <sanguis/client/load/animation_type_fwd.hpp>
#include <sanguis/client/load/optional_animation_type.hpp>
#include <sanguis/client/load/model/part_fwd.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/unique_ptr_impl.hpp>


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
		sanguis::client::sound_manager &,
		sanguis::client::load::model::part const &,
		sanguis::client::draw2d::sprite::normal::object &
	);

	~part();

	void
	pause(
		bool
	);

	bool
	try_animation(
		sanguis::client::load::animation_type
	);

	void
	weapon(
		sanguis::optional_primary_weapon_type
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
		sanguis::client::load::animation_type
	);

	void
	update_orientation(
		sanguis::client::draw2d::sprite::rotation
	);

	sanguis::client::draw2d::sprite::rotation
	orientation() const;

	sanguis::diff_clock const &diff_clock_;

	sanguis::client::sound_manager &sound_manager_;

	sanguis::diff_timer rotation_timer_;

	typedef
	fcppt::optional<
		sanguis::client::draw2d::sprite::rotation
	>
	optional_rotation;

	optional_rotation desired_orientation_;

	sanguis::client::load::model::part const &load_part_;

	sanguis::client::draw2d::sprite::normal::object &ref_;

	sanguis::client::load::optional_animation_type animation_type_;

	sanguis::optional_primary_weapon_type weapon_;

	typedef
	fcppt::unique_ptr<
		sanguis::client::draw2d::sprite::normal::texture_animation
	>
	scoped_texture_animation;

	typedef
	fcppt::optional<
		scoped_texture_animation
	>
	optional_scoped_texture_animation;

	optional_scoped_texture_animation animation_;

	bool animation_ended_;

	typedef
	fcppt::optional<
		sge::audio::sound::base_unique_ptr
	>
	optional_sound;

	optional_sound sound_;
};

}
}
}
}
}

#endif
