#include "context.hpp"
#include "world_context.hpp"
#include <sge/make_shared_ptr.hpp>

sanguis::server::global::context::context(
	unicast_callback const &send_unicast_
)
:
	send_unicast_(send_unicast_)
	worlds_(),
	players_(),
	world_context_(
		sge::make_shared_ptr<
			world_context
		>(
			*this
		)
	)
{}

sanguis::server::global::context::~context()
{}

void
sanguis::server::global::context::insert_player(
	world_id const world_id_,
	player_id const player_id_,
	string const &name,
	connect_state::type const connect_state_
)
{
	world::object &world_(
		worlds_[
			world_id_
		]
	);

	entities::player_auto_ptr player(
		create_player(
			m,
			send_unicast_,
			environment(),
			entities_,
			connect_state_
		)
	);
}

void
sanguis::server::global::context::choose_perk(
	player_id const player_id_,
	perk_type::type const perk_type_
)
{
	entities::player &player_(
		players_[
			player_id_
		]
	);
	
	if(
		!player_.perk_choosable(
			perk
		)
	)
	{
		SGE_LOG_WARNING(
			log(),
			sge::log::_1
				<< SGE_TEXT("Player with id ")
				<< player_id_
				<< SGE_TEXT(" tried to take an invalid perk")
				<< SGE_TEXT(" or has no skillpoints left!"));
		return;
	}

	player_.add_perk(
		perks::create(
			perk_type_
		)
	);
	
	send_available_perks(
		player_
	);
}

void
sanguis::server::global::context::send_to_player(
	player_id const player_id_,
	messages::auto_ptr msg_
)
{
	// TODO: we probably want to map this id to a net::id_type
	send_unicast(
		player_id_,
		msg_
	);
}

void
sanguis::server::global::context::transfer_entity(
	world_id const destination,
	entities::auto_ptr entity
)
{
	worlds_[
		destination
	].insert(
		entity
	);
}
