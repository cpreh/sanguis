#include "connect.hpp"
#include "../../../resolution.hpp"
#include <sge/systems/instance.hpp>
#include <sge/image/loader.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/gui/layouts/horizontal.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/make_image.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>

sanguis::client::menu::menus::connect::connect(
	sge::gui::widgets::parent_data const &_parent,
	fcppt::filesystem::path const &buttons_path,
	fcppt::filesystem::path const &labels_path,
	sge::systems::instance const &sys)
:
	parent(
		_parent,
		sge::gui::widgets::parameters()
			.pos(
				sge::gui::point::null())
			.size(
				sge::gui::dim(1023,768))
			.activation(
				sge::gui::activation_state::inactive)
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::vertical>())),

	host(
		parent,
		sge::gui::widgets::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>())),
	host_label(
		host,
		sge::gui::widgets::parameters(),
		sge::gui::make_image(
			sys.image_loader()->load(
				labels_path/FCPPT_TEXT("host.png")))),
	host_edit(
		host,
		sge::gui::widgets::parameters(),
		sge::gui::widgets::edit::single_line,
		sge::gui::dim(30,1)),

	port(
		parent,
		sge::gui::widgets::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>())),
	port_label(
		port,
		sge::gui::widgets::parameters(),
		sge::gui::make_image(
			sys.image_loader()->load(
				labels_path/FCPPT_TEXT("port.png")))),
	port_edit(
		port,
		sge::gui::widgets::parameters(),
		sge::gui::widgets::edit::single_line,
		sge::gui::dim(5,1)),

	connect_wrapper(
		parent,
		sge::gui::widgets::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>())),
	connect_(
		connect_wrapper,
		sys.image_loader(),
		buttons_path,
		FCPPT_TEXT("connect")),
	return_wrapper(
		parent,
		sge::gui::widgets::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>())),
	return_(
		return_wrapper,
		sys.image_loader(),
		buttons_path,
		FCPPT_TEXT("return"))
{
}
