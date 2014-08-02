#include <sanguis/client/draw2d/radius.hpp>
#include <sanguis/client/draw2d/scene/hover/parameters.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/nonassignable.hpp>


sanguis::client::draw2d::scene::hover::parameters::parameters(
	sanguis::gui::style::base const &_gui_style,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sanguis::client::load::hud::context &_load_context,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::client::draw2d::radius const _radius
)
:
	gui_style_(
		_gui_style
	),
	renderer_(
		_renderer
	),
	font_(
		_font
	),
	load_context_(
		_load_context
	),
	center_{
		_center
	},
	radius_{
		_radius
	}
{
}

sanguis::gui::style::base const &
sanguis::client::draw2d::scene::hover::parameters::gui_style() const
{
	return
		gui_style_;
}

sge::renderer::device::ffp &
sanguis::client::draw2d::scene::hover::parameters::renderer() const
{
	return
		renderer_;
}

sge::font::object &
sanguis::client::draw2d::scene::hover::parameters::font() const
{
	return
		font_;
}

sanguis::client::load::hud::context &
sanguis::client::draw2d::scene::hover::parameters::load_context() const
{
	return
		load_context_;
}

sanguis::client::draw2d::sprite::center const
sanguis::client::draw2d::scene::hover::parameters::center() const
{
	return
		center_;
}

sanguis::client::draw2d::radius const
sanguis::client::draw2d::scene::hover::parameters::radius() const
{
	return
		radius_;
}