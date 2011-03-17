#include "object.hpp"
#include "../cursor/object.hpp"
#include <sge/cegui/load_context.hpp>
#include <sge/config/media_path.hpp>
#include <sge/time/duration.hpp>
#include <sge/time/second_f.hpp>
#include <fcppt/chrono/duration_cast.hpp>
#include <fcppt/text.hpp>

sanguis::client::gui::object::object(
	sge::renderer::device_ptr const _renderer,
	sge::image2d::multi_loader &_image_loader,
	sge::charconv::system_ptr const _charconv_system,
	sge::viewport::manager &_viewport_manager,
	sge::input::keyboard::device_ptr const _keyboard,
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
		*_keyboard
	),
	cursor_(
		syringe_,
		*_cursor.get()
	)
{
}
	
sanguis::client::gui::object::~object()
{
}

sge::charconv::system_ptr const
sanguis::client::gui::object::charconv_system() const
{
	return charconv_system_;
}

void
sanguis::client::gui::object::render()
{
	system_.render();
}

void
sanguis::client::gui::object::update(
	time_type const _time
)
{
	system_.update(
	        fcppt::chrono::duration_cast<
			sge::time::duration
		>(
			sge::time::second_f(
				_time
			)
		)
	);
}