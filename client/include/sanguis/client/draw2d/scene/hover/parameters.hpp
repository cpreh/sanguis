#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_PARAMETERS_HPP_INCLUDED

#include <sanguis/client/draw2d/radius.hpp>
#include <sanguis/client/draw2d/scene/hover/parameters_fwd.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/nonassignable.hpp>


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
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	parameters(
		sanguis::gui::style::base const &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sanguis::client::load::hud::context &,
		sanguis::client::draw2d::sprite::center,
		sanguis::client::draw2d::radius
	);

	sanguis::gui::style::base const &
	gui_style() const;

	sge::renderer::device::ffp &
	renderer() const;

	sge::font::object &
	font() const;

	sanguis::client::load::hud::context &
	load_context() const;

	sanguis::client::draw2d::sprite::center const
	center() const;

	sanguis::client::draw2d::radius const
	radius() const;
private:
	sanguis::gui::style::base const &gui_style_;

	sge::renderer::device::ffp &renderer_;

	sge::font::object &font_;

	sanguis::client::load::hud::context &load_context_;

	sanguis::client::draw2d::sprite::center const center_;

	sanguis::client::draw2d::radius const radius_;
};

}
}
}
}
}

#endif
