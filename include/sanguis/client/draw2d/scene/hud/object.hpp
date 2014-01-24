#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HUD_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HUD_OBJECT_HPP_INCLUDED

#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/optional_weapon_description.hpp>
#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/client/draw2d/entities/name_fwd.hpp>
#include <sanguis/client/draw2d/scene/hud/object_fwd.hpp>
#include <sanguis/client/exp.hpp>
#include <sanguis/client/level.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/timer/frames_counter.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace hud
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::font::object &,
		sge::renderer::device::ffp &
	);

	~object();

	void
	experience(
		sanguis::client::exp
	);

	void
	level(
		sanguis::client::level
	);

	void
	add_weapon(
		sanguis::weapon_description const &
	);

	void
	remove_weapon(
		sanguis::is_primary_weapon
	);

	void
	draw(
		sge::renderer::context::ffp &
	);

	void
	show_name(
		sanguis::client::draw2d::entities::name const &
	);

	void
	clear_name();
private:
	sanguis::optional_weapon_description &
	weapon_description(
		sanguis::is_primary_weapon
	);

	sge::font::object &font_object_;

	sge::renderer::device::ffp &renderer_;

	sanguis::client::exp experience_;

	sanguis::client::level level_;

	sge::timer::frames_counter frames_counter_;

	sanguis::optional_weapon_description primary_weapon_;

	sanguis::optional_weapon_description secondary_weapon_;

	sge::font::string name_text_;
};

}
}
}
}
}

#endif
