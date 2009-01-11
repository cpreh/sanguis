#include "send_available_perks.hpp"
#include "perks/list.hpp"
#include "entities/player.hpp"
#include "../messages/available_perks.hpp"

void
sanguis::server::send_available_perks(
	entities::player &p,
	send_callback const &send)
{
	perks::list const &list(
		p.available_perks());
	send(
		messages::auto_ptr(
			new messages::available_perks(
				messages::perk_list(
					list.begin(),
					list.end()))));

}
