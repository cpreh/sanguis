#ifndef SANGUIS_CLIENT_DRAW2D_CREATE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_CREATE_HPP_INCLUDED

#include <sanguis/client/cursor_fwd.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/draw/base_unique_ptr.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/load/context_fwd.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/log/context_reference_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{

sanguis::client::draw::base_unique_ptr
create(
	fcppt::log::context_reference,
	sanguis::client::load::context const &,
	sanguis::client::load::hud::context &,
	sanguis::client::sound_manager &,
	sge::gui::style::const_reference,
	sge::renderer::device::ffp &,
	sge::font::object &,
	sge::viewport::manager &,
	sanguis::client::player_health_callback const &,
	sanguis::client::cursor &,
	sanguis::client::draw::debug
);

}
}
}

#endif
