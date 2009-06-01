#ifndef SANGUIS_CLIENT_MENU_MENUS_HIGHSCORE_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_MENUS_HIGHSCORE_HPP_INCLUDED

#include <sge/gui/widgets/parent_data.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/widgets/buttons/text.hpp>
#include <sge/systems/instance_fwd.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sanguis
{
namespace client
{
namespace menu
{
namespace menus
{
struct highscore
{
	typedef boost::ptr_vector<sge::gui::widgets::base> child_container;

	highscore(
		sge::gui::widgets::parent_data const &,
		sge::filesystem::path const &buttons_path,
		sge::systems::instance const &);
	
	sge::gui::widgets::base parent;
		sge::gui::widgets::base table;
		sge::gui::widgets::buttons::text back_button;
	child_container children;

private:
	void populate_children();
};
}
}
}
}

#endif // SANGUIS_CLIENT_MENU_MENUS_HIGHSCORE_HPP_INCLUDED