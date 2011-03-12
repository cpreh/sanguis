#include "object.hpp"
#include "../cursor/object.hpp"
#include <sge/cegui/load_context.hpp>
#include <sge/config/media_path.hpp>
#include <fcppt/text.hpp>

sanguis::client::gui::object::object(
	sge::renderer::device_ptr const _renderer,
	sge::image2d::multi_loader &_image_loader,
	sge::charconv::system_ptr const _charconv,
	sge::viewport::manager &_viewport_manager,
	sge::input::keyboard::device_ptr const _keyboard,
	client::cursor::object &_cursor
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
		_charconv,
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
