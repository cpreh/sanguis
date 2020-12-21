#ifndef SANGUIS_CLIENT_EVENTS_MENU_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_MENU_HPP_INCLUDED

#include <sanguis/client/events/menu_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace events
{

class menu
:
	public boost::statechart::event<
		sanguis::client::events::menu
	>
{
public:
	menu();

	menu(
		menu &&
	)
	noexcept;

	menu(
		menu const &
	);

	menu &
	operator=(
		menu &&
	)
	noexcept;

	menu &
	operator=(
		menu const &
	);

	~menu()
	override;
};

}
}
}

#endif
