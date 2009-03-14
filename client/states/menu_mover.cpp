#include "menu_mover.hpp"
#include <sge/gui/widget.hpp>
#include <sge/gui/manager.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/structure_cast.hpp>

sanguis::client::menu_mover::menu_mover(
	sge::gui::manager &_man,
	sge::gui::widget &_connect_menu,
	sge::gui::widget &_main_menu)
:
	man_(_man),
	connect_menu_(_connect_menu),
	main_menu_(_main_menu),
	pos_connect(
		static_cast<sge::time::funit>(0),
		static_cast<sge::time::funit>(0)),
	vantage_connect(
		static_cast<sge::time::funit>(-2000),
		static_cast<sge::time::funit>(-2000)),
	pos_main(
		static_cast<sge::time::funit>(0),
		static_cast<sge::time::funit>(0)),
	vantage_main(
		static_cast<sge::time::funit>(5000),
		static_cast<sge::time::funit>(5000)),
	real_main(time_vector::null()),
	real_connect(time_vector::null()),
	speed(static_cast<sge::time::funit>(8))
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
	float c_a,m_a;

	if (connect_menu_.activation() == sge::gui::activation_state::active)
	{
		real_main += speed * delta * (vantage_main - real_main);
		real_connect += speed * delta * (pos_connect - real_connect);
		c_a = 
			std::abs(
				static_cast<float>(vantage_connect.x()-real_connect.x()))/
				3000.0f;

		m_a = 1.0f-std::abs(
							static_cast<float>(vantage_main.x()-real_main.x()))/
							3000.0f;
	}
	else
	{
		real_main += speed * delta * (pos_main - real_main);
		real_connect += speed * delta * (vantage_connect - real_connect);

		c_a = 
			1.0f-std::abs(
				static_cast<float>(vantage_connect.x()-real_connect.x()))/
				3000.0f;

		m_a = std::abs(
							static_cast<float>(vantage_main.x()-real_main.x()))/
							3000.0f;
	}
	main_menu_.relative_pos(
		sge::structure_cast<sge::gui::point>(
			real_main));
	connect_menu_.relative_pos(
		sge::structure_cast<sge::gui::point>(
			real_connect));

	man_.connected_sprite(connect_menu_).visible(true);
	man_.connected_sprite(main_menu_).visible(true);

	/*
	man_.connected_sprite(connect_menu_).color(
		sge::gui::internal_color(
			0xff,
			0xff,
			0xff,
			static_cast<unsigned char>(c_a*255.0f)));

	man_.connected_sprite(main_menu_).color(
		sge::gui::internal_color(
			0xff,
			0xff,
			0xff,
			static_cast<unsigned char>(m_a*255.0f)));
			*/
}
