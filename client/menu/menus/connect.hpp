#ifndef SANGUIS_CLIENT_MENU_MENUS_CONNECT_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_MENUS_CONNECT_HPP_INCLUDED

#include "../button.hpp"
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/widgets/graphics.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/image/loader_ptr.hpp>
#include <fcppt/filesystem/path.hpp>

namespace sanguis
{
namespace client
{
namespace menu
{
namespace menus
{
struct connect
{
	connect(
		sge::gui::widgets::parent_data const &,
		fcppt::filesystem::path const &buttons_path,
		fcppt::filesystem::path const &labels_path,
		sge::image::loader_ptr
	);

	sge::gui::widgets::base parent;
		sge::gui::widgets::base host;
			sge::gui::widgets::graphics host_label;
			sge::gui::widgets::edit host_edit;
		sge::gui::widgets::base port;
			sge::gui::widgets::graphics port_label;
			sge::gui::widgets::edit port_edit;
		sge::gui::widgets::base connect_wrapper;
			button connect_;
		sge::gui::widgets::base return_wrapper;
			button return_;
};
}
}
}
}

#endif
