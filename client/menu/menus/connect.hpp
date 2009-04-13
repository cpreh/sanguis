#ifndef SANGUIS_CLIENT_MENU_MENUS_CONNECT_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_MENUS_CONNECT_HPP_INCLUDED

#include "../button.hpp"
#include <sge/gui/widget.hpp>
#include <sge/gui/widgets/graphics.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/systems/instance_fwd.hpp>

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
		sge::gui::widget::parent_data const &,
		sge::filesystem::path const &buttons_path,
		sge::filesystem::path const &labels_path,
		sge::systems::instance &);

	sge::gui::widget parent;
		sge::gui::widget host;
			sge::gui::widgets::graphics host_label;
			sge::gui::widgets::edit host_edit;
		sge::gui::widget port;
			sge::gui::widgets::graphics port_label;
			sge::gui::widgets::edit port_edit;
		sge::gui::widget connect_wrapper;
			button connect_;
		sge::gui::widget return_wrapper;
			button return_;
};
}
}
}
}

#endif
