#include "menu_mover.hpp"
#include <sge/gui/widget.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/structure_cast.hpp>

sanguis::client::menu_mover::menu_mover(
	sge::gui::widget &_connect_menu,
	sge::gui::widget &_main_menu)
:
	connect_menu_(_connect_menu),
	main_menu_(_main_menu),
	pos_connect(
		static_cast<sge::time::funit>(0),
		static_cast<sge::time::funit>(0)),
	vantage_connect(
		static_cast<sge::time::funit>(-2000),
		static_cast<sge::time::funit>(200)),
	pos_main(
		static_cast<sge::time::funit>(0),
		static_cast<sge::time::funit>(0)),
	vantage_main(
		static_cast<sge::time::funit>(200),
		static_cast<sge::time::funit>(-2000)),
	real_main(time_vector::null()),
	real_connect(time_vector::null()),
	speed(static_cast<sge::time::funit>(10))
{
	main_menu_.activation(
		sge::gui::activation_state::active);
	connect_menu_.activation(
		sge::gui::activation_state::inactive);
}

void sanguis::client::menu_mover::connect_to_server()
{
	main_menu_.activation(sge::gui::activation_state::inactive);
	connect_menu_.activation(sge::gui::activation_state::active);
}

void sanguis::client::menu_mover::return_to_menu()
{
	connect_menu_.activation(sge::gui::activation_state::inactive);
	main_menu_.activation(sge::gui::activation_state::active);
}

void sanguis::client::menu_mover::update(sge::time::funit const delta)
{
	if (connect_menu_.activation() == sge::gui::activation_state::active)
	{
		real_main += speed * delta * (vantage_main - real_main);
		real_connect += speed * delta * (pos_connect - real_connect);
	}
	else
	{
		real_main += speed * delta * (pos_main - real_main);
		real_connect += speed * delta * (vantage_connect - real_connect);
	}
	main_menu_.relative_pos(
		sge::structure_cast<sge::gui::point>(
			real_main));
	connect_menu_.relative_pos(
		sge::structure_cast<sge::gui::point>(
			real_connect));
}
