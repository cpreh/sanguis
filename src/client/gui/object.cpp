#include <sanguis/duration.hpp>
#include <sanguis/client/gui/object.hpp>
#include <sge/cegui/cursor_visibility.hpp>
#include <sge/cegui/duration.hpp>
#include <sge/cegui/load_context.hpp>
#include <sge/cegui/system_fwd.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::client::gui::object::object(
	sge::renderer::device::ffp &_renderer,
	sge::image2d::system &_image_loader,
	sge::viewport::manager &_viewport_manager,
	sge::input::keyboard::device &_keyboard,
	sge::input::cursor::object &_cursor
)
:
	system_(
		sge::cegui::load_context(
			sge::config::media_path()
			/
			FCPPT_TEXT("gui")
			/
			FCPPT_TEXT("TaharezLook.scheme")
		)
		.font_directory(
			sge::config::media_path()
			/
			FCPPT_TEXT("fonts")
		),
		_renderer,
		_image_loader,
		_viewport_manager,
		sge::cegui::cursor_visibility::invisible,
		sge::renderer::texture::emulate_srgb::no
	),
	syringe_(
		system_
	),
	keyboard_(
		syringe_,
		_keyboard
	),
	cursor_(
		syringe_,
		_cursor
	)
{
}

sanguis::client::gui::object::~object()
{
}

sge::cegui::system &
sanguis::client::gui::object::system()
{
	return system_;
}

void
sanguis::client::gui::object::render(
	sge::renderer::context::ffp &_render_context
)
{
	system_.render(
		_render_context
	);
}

void
sanguis::client::gui::object::update(
	sanguis::duration const &_time
)
{
	system_.update(
		std::chrono::duration_cast<
			sge::cegui::duration
		>(
			_time
		)
	);
}
