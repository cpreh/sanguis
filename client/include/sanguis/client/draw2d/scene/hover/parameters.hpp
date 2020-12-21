#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_PARAMETERS_HPP_INCLUDED

#include <sanguis/client/weapon_pair.hpp>
#include <sanguis/client/draw2d/radius.hpp>
#include <sanguis/client/draw2d/scene/hover/parameters_fwd.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sanguis/client/load/hud/context_ref.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/renderer/base_ref.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace hover
{

class parameters
{
public:
	parameters(
		sge::gui::style::const_reference,
		sge::gui::renderer::base_ref,
		sge::renderer::device::ffp_ref,
		sge::font::object_ref,
		sanguis::client::load::hud::context_ref,
		sanguis::client::weapon_pair &&,
		sanguis::client::draw2d::sprite::center,
		sanguis::client::draw2d::radius
	);

	[[nodiscard]]
	sge::gui::style::base const &
	gui_style() const;

	[[nodiscard]]
	sge::gui::renderer::base &
	gui_renderer() const;

	[[nodiscard]]
	sge::renderer::device::ffp &
	renderer() const;

	[[nodiscard]]
	sge::font::object &
	font() const;

	[[nodiscard]]
	sanguis::client::load::hud::context &
	load_context() const;

	[[nodiscard]]
	sanguis::client::weapon_pair const &
	player_weapons() const;

	[[nodiscard]]
	sanguis::client::draw2d::sprite::center
	center() const;

	[[nodiscard]]
	sanguis::client::draw2d::radius
	radius() const;
private:
	sge::gui::style::const_reference gui_style_;

	sge::gui::renderer::base_ref gui_renderer_;

	sge::renderer::device::ffp_ref renderer_;

	sge::font::object_ref font_;

	sanguis::client::load::hud::context_ref load_context_;

	sanguis::client::weapon_pair player_weapons_;

	sanguis::client::draw2d::sprite::center center_;

	sanguis::client::draw2d::radius radius_;
};

}
}
}
}
}

#endif
