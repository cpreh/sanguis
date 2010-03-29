#include "connect_box.hpp"
#include <sge/font/align_h.hpp>
#include <sge/font/align_v.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/layouts/horizontal.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>

sanguis::client::menu::menus::connect_box::connect_box(
	sge::gui::widgets::parent_data const &_parent
)
:
	parent(
		_parent,
		sge::gui::widgets::parameters()
			.pos(
				sge::gui::point::null())
			.activation(
				sge::gui::activation_state::inactive)
			.layout(
				fcppt::make_shared_ptr<sge::gui::layouts::vertical>())),
	
	label_wrapper(
		parent,
		sge::gui::widgets::parameters()
			.layout(
				fcppt::make_shared_ptr<sge::gui::layouts::horizontal>())),

	label_(
		label_wrapper,
		sge::gui::widgets::parameters(),
		FCPPT_TEXT(""),
		sge::font::align_h::center,
		sge::font::align_v::center,
		sge::gui::dim(30,10)),
	
	buttons(
		parent,
		sge::gui::widgets::parameters()
			.layout(
				fcppt::make_shared_ptr<sge::gui::layouts::horizontal>())),
	
	buttons_retry(
		buttons,
		sge::gui::widgets::parameters(),
		FCPPT_TEXT("Retry")),

	buttons_cancel(
		buttons,
		sge::gui::widgets::parameters(),
		FCPPT_TEXT("Cancel"))
{
}
