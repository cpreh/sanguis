#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/animation.hpp>
#include <sanguis/client/draw2d/entities/model/desired_orientation.hpp>
#include <sanguis/client/draw2d/entities/model/part_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/object_fwd.hpp>
#include <sanguis/client/load/animation_type_fwd.hpp>
#include <sanguis/client/load/model/part_fwd.hpp>
#include <sge/texture/const_part_ref_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_wrapper_decl.hpp>


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
		sanguis::optional_primary_weapon_type,
		sanguis::client::draw2d::sprite::rotation,
		sanguis::client::load::animation_type
	);

	part(
		part &&
	);

	part &
	operator=(
		part &&
	);

	~part();

	void
	pause(
		bool
	);

	void
	animation(
		sanguis::client::load::animation_type
	);

	void
	weapon(
		sanguis::optional_primary_weapon_type
	);

	void
	update(
		sanguis::client::draw2d::sprite::normal::object &
	);

	void
	orientation(
		sanguis::client::draw2d::sprite::rotation
	);

	bool
	ended() const;

	sge::texture::const_part_ref const
	texture();
private:
	sanguis::client::draw2d::entities::model::animation
	load_animation(
		sanguis::client::load::animation_type
	);

	fcppt::reference_wrapper<
		sanguis::diff_clock const
	> diff_clock_;

	fcppt::reference_wrapper<
		sanguis::client::sound_manager
	> sound_manager_;

	sanguis::diff_timer rotation_timer_;

	sanguis::client::draw2d::entities::model::desired_orientation desired_orientation_;

	fcppt::reference_wrapper<
		sanguis::client::load::model::part const
	> load_part_;

	sanguis::optional_primary_weapon_type weapon_;

	sanguis::client::draw2d::entities::model::animation animation_;
};

}
}
}
}
}

#endif
