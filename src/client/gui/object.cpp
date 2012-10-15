#include <sanguis/client/gui/object.hpp>
#include <sanguis/client/cursor/object.hpp>
#include <sge/cegui/duration.hpp>
#include <sge/cegui/load_context.hpp>
#include <sge/config/media_path.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::gui::object::object(
	sge::renderer::device::ffp &_renderer,
	sge::image2d::system &_image_loader,
	sge::charconv::system &_charconv_system,
	sge::viewport::manager &_viewport_manager,
	sge::input::keyboard::device &_keyboard,
	client::cursor::object &_cursor
)
:
	charconv_system_(_charconv_system),
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
		charconv_system_,
		_viewport_manager,
		sge::cegui::cursor_visibility::invisible
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
		_cursor.get()
	)
{
}

sanguis::client::gui::object::~object()
{
}

sge::charconv::system &
sanguis::client::gui::object::charconv_system() const
{
	return charconv_system_;
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
		boost::chrono::duration_cast<
			sge::cegui::duration
		>(
			_time
		)
	);
}
