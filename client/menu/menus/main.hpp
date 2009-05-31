#ifndef SANGUIS_CLIENT_MENU_MENUS_MAIN_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_MENUS_MAIN_HPP_INCLUDED

#include "../button.hpp"
#include <sge/gui/widgets/base.hpp>
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
struct main
{
	main(
		sge::gui::widgets::parent_data const &,
		sge::filesystem::path const &,
		sge::systems::instance const &);

	sge::gui::widgets::base parent;
	button connect;
	button start;
	button highscore;
	button exit;
};
}
}
}
}

#endif
