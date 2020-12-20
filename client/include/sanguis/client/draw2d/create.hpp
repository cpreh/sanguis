#ifndef SANGUIS_CLIENT_DRAW2D_CREATE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_CREATE_HPP_INCLUDED

#include <sanguis/client/cursor_ref.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/sound_manager_ref.hpp>
#include <sanguis/client/draw/base_unique_ptr.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/load/context_cref.hpp>
#include <sanguis/client/load/hud/context_ref.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/viewport/manager_ref.hpp>
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
	sanguis::client::load::context_cref,
	sanguis::client::load::hud::context_ref,
	sanguis::client::sound_manager_ref,
	sge::gui::style::const_reference,
	sge::renderer::device::ffp_ref,
	sge::font::object_ref,
	sge::viewport::manager_ref,
	sanguis::client::player_health_callback &&,
	sanguis::client::cursor_ref,
	sanguis::client::draw::debug
);

}
}
}

#endif
