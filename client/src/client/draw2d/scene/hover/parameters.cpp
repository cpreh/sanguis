#include <sanguis/client/weapon_pair.hpp>
#include <sanguis/client/draw2d/radius.hpp>
#include <sanguis/client/draw2d/scene/hover/parameters.hpp>
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
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::hover::parameters::parameters(
	sge::gui::style::const_reference const _gui_style,
	sge::gui::renderer::base_ref const _gui_renderer,
	sge::renderer::device::ffp_ref const _renderer,
	sge::font::object_ref const _font,
	sanguis::client::load::hud::context_ref const _load_context,
	sanguis::client::weapon_pair &&_player_weapons,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::client::draw2d::radius const _radius
)
:
	gui_style_(
		_gui_style
	),
	gui_renderer_(
		_gui_renderer
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
	player_weapons_(
		std::move(
			_player_weapons
		)
	),
	center_{
		_center
	},
	radius_{
		_radius
	}
{
}

sge::gui::style::base const &
sanguis::client::draw2d::scene::hover::parameters::gui_style() const
{
	return
		gui_style_.get();
}

sge::gui::renderer::base &
sanguis::client::draw2d::scene::hover::parameters::gui_renderer() const
{
	return
		gui_renderer_.get();
}

sge::renderer::device::ffp &
sanguis::client::draw2d::scene::hover::parameters::renderer() const
{
	return
		renderer_.get();
}

sge::font::object &
sanguis::client::draw2d::scene::hover::parameters::font() const
{
	return
		font_.get();
}

sanguis::client::load::hud::context &
sanguis::client::draw2d::scene::hover::parameters::load_context() const
{
	return
		load_context_.get();
}

sanguis::client::weapon_pair const &
sanguis::client::draw2d::scene::hover::parameters::player_weapons() const
{
	return
		player_weapons_;
}

sanguis::client::draw2d::sprite::center
sanguis::client::draw2d::scene::hover::parameters::center() const
{
	return
		center_;
}

sanguis::client::draw2d::radius
sanguis::client::draw2d::scene::hover::parameters::radius() const
{
	return
		radius_;
}
