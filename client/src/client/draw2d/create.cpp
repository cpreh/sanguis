#include <sanguis/client/cursor_ref.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/sound_manager_ref.hpp>
#include <sanguis/client/draw/base.hpp>
#include <sanguis/client/draw/base_unique_ptr.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/create.hpp>
#include <sanguis/client/draw2d/scene/object.hpp>
#include <sanguis/client/load/context_cref.hpp>
#include <sanguis/client/load/hud/context_ref.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw::base_unique_ptr
sanguis::client::draw2d::create(
	fcppt::log::context_reference const _log_context,
	sanguis::client::load::context_cref const _load_context,
	sanguis::client::load::hud::context_ref const _hud_context,
	sanguis::client::sound_manager_ref const _sound_manager,
	sge::gui::style::const_reference const _gui_style,
	sge::renderer::device::ffp_ref const _renderer,
	sge::font::object_ref const _font,
	sge::viewport::manager_ref const _viewport_manager,
	sanguis::client::player_health_callback &&_player_health_callback,
	sanguis::client::cursor_ref const _cursor,
	sanguis::client::draw::debug const _debug
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::client::draw::base
		>(
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::scene::object
			>(
				_log_context,
				_load_context,
				_hud_context,
				_sound_manager,
				_gui_style,
				_renderer,
				_font,
				_viewport_manager,
				std::move(
					_player_health_callback
				),
				_cursor,
				_debug
			)
		);
}
