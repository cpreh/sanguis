#include "connect.hpp"
#include "../../../resolution.hpp"
#include <sge/systems/instance.hpp>
#include <sge/image/loader.hpp>
#include <sge/gui/layouts/horizontal.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/make_image.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/structure_cast.hpp>
#include <sge/text.hpp>

sanguis::client::menu::menus::connect::connect(
	sge::gui::widget::parent_data const &_parent,
	sge::filesystem::path const &buttons_path,
	sge::filesystem::path const &labels_path,
	sge::systems::instance const &sys)
:
	parent(
		_parent,
		sge::gui::widget::parameters()
			.pos(
				sge::gui::point::null())
			.size(
				sge::structure_cast<sge::gui::dim>(
					resolution()))
			.activation(
				sge::gui::activation_state::inactive)
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::vertical>())),

	host(
		parent,
		sge::gui::widget::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>())),
	host_label(
		host,
		sge::gui::widget::parameters(),
		sge::gui::make_image(
			sys.image_loader()->load(
				labels_path/SGE_TEXT("host.png")))),
	host_edit(
		host,
		sge::gui::widget::parameters(),
		sge::gui::widgets::edit::single_line,
		sge::gui::dim(30,1)),

	port(
		parent,
		sge::gui::widget::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>())),
	port_label(
		port,
		sge::gui::widget::parameters(),
		sge::gui::make_image(
			sys.image_loader()->load(
				labels_path/SGE_TEXT("port.png")))),
	port_edit(
		port,
		sge::gui::widget::parameters(),
		sge::gui::widgets::edit::single_line,
		sge::gui::dim(5,1)),

	connect_wrapper(
		parent,
		sge::gui::widget::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>())),
	connect_(
		connect_wrapper,
		sys.image_loader(),
		buttons_path,
		SGE_TEXT("connect")),
	return_wrapper(
		parent,
		sge::gui::widget::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>())),
	return_(
		return_wrapper,
		sys.image_loader(),
		buttons_path,
		SGE_TEXT("return"))
{
}
