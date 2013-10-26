#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HUD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HUD_HPP_INCLUDED

#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/client/draw2d/entities/name_fwd.hpp>
#include <sanguis/client/draw2d/scene/hud_fwd.hpp>
#include <sanguis/client/exp.hpp>
#include <sanguis/client/level.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/timer/frames_counter.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ctime>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{

class hud
{
	FCPPT_NONCOPYABLE(
		hud
	);
public:
	hud(
		sge::font::object &,
		sge::renderer::device::ffp &,
		std::tm const &
	);

	~hud();

	void
	experience(
		sanguis::client::exp
	);

	void
	level(
		sanguis::client::level
	);

	void
	time(
		std::tm const &
	);

	void
	weapon_description(
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
	void
	make_weapon_text();

	void
	append_weapon_text(
		sanguis::string_vector const &
	);

	sanguis::string_vector &
	weapon_text(
		sanguis::is_primary_weapon
	);

	sge::font::object &font_object_;

	sge::renderer::device::ffp &renderer_;

	sanguis::client::exp experience_;

	sanguis::client::level level_;

	std::tm time_;

	sge::timer::frames_counter frames_counter_;

	sanguis::string_vector primary_weapon_;

	sanguis::string_vector secondary_weapon_;

	sge::font::string weapon_text_;

	sge::font::string name_text_;
};

}
}
}
}

#endif
