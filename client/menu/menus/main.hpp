#ifndef SANGUIS_CLIENT_MENU_MENUS_MAIN_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_MENUS_MAIN_HPP_INCLUDED

#include "../button.hpp"
#include <sge/gui/widgets/base.hpp>
#include <sge/image/multi_loader_fwd.hpp>
#include <fcppt/filesystem/path.hpp>

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
		sge::gui::dim const &,
		fcppt::filesystem::path const &,
		sge::image::multi_loader const &
	);

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
