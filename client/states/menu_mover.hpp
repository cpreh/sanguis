#ifndef SANGUIS_CLIENT_MENU_MOVER_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_MOVER_HPP_INCLUDED

#include <sge/gui/widget_fwd.hpp>
#include <sge/math/vector/static.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/time/funit.hpp>

namespace sanguis
{
namespace client
{
class menu_mover
{
	public:
	menu_mover(
		sge::gui::widget &_connect_menu,
		sge::gui::widget &_main_menu);

	void connect_to_server();
	void return_to_menu();
	void update(sge::time::funit const);
	private:
	typedef sge::math::vector::static_<sge::time::funit,2>::type time_vector;

	sge::gui::widget &connect_menu_;
	sge::gui::widget &main_menu_;
	time_vector pos_connect;
	time_vector vantage_connect;
	time_vector pos_main;
	time_vector vantage_main;
	time_vector real_main;
	time_vector real_connect;
	sge::time::funit speed;
};
}
}

#endif
