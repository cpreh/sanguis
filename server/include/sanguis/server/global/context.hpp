#ifndef SANGUIS_SERVER_GLOBAL_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_CONTEXT_HPP_INCLUDED

#include <sanguis/cheat_type_fwd.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/player_name_fwd.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/server/console_fwd.hpp>
#include <sanguis/server/load_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/vector_fwd.hpp>
#include <sanguis/server/entities/optional_player_ref_fwd.hpp>
#include <sanguis/server/entities/player_fwd.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/global/context_fwd.hpp>
#include <sanguis/server/global/source_world_pair.hpp>
#include <sanguis/server/global/world_map.hpp>
#include <sanguis/server/world/context.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_wrapper_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace global
{

class context
:
	public sanguis::server::world::context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context(
		sanguis::server::unicast_callback const &,
		sanguis::server::load const &,
		sanguis::server::console &
	);

	~context()
	override;

	void
	insert_player(
		sanguis::world_id,
		sanguis::server::player_id,
		sanguis::player_name const &
	);

	void
	player_disconnect(
		sanguis::server::player_id
	);

	void
	player_target(
		sanguis::server::player_id,
		sanguis::server::vector const &
	);

	void
	player_change_world(
		sanguis::server::player_id
	);

	void
	player_change_shooting(
		sanguis::server::player_id,
		bool shooting,
		sanguis::is_primary_weapon
	);

	void
	player_reload(
		sanguis::server::player_id,
		sanguis::is_primary_weapon
	);

	void
	player_drop_or_pickup_weapon(
		sanguis::server::player_id,
		sanguis::is_primary_weapon
	);

	void
	player_speed(
		sanguis::server::player_id,
		sanguis::server::speed const &
	);

	void
	player_cheat(
		sanguis::server::player_id,
		sanguis::cheat_type
	);

	void
	player_choose_perk(
		sanguis::server::player_id,
		sanguis::perk_type
	);

	void
	update(
		sanguis::duration const &
	);

	bool
	multiple_players() const;

	bool
	has_player(
		sanguis::server::player_id
	) const;
private:
	sanguis::entity_id const
	next_id();

	// callbacks for world

	void
	send_to_player(
		sanguis::server::player_id,
		sanguis::messages::server::base const &
	)
	override;

	void
	remove_player(
		sanguis::server::player_id
	)
	override;

	bool
	request_transfer(
		sanguis::server::global::source_world_pair
	) const
	override;

	void
	transfer_entity(
		sanguis::server::global::source_world_pair,
		sanguis::server::entities::unique_ptr &&
	)
	override;

	sanguis::server::world::object &
	world(
		sanguis::world_id
	);

	sanguis::server::entities::player &
	player_exn(
		sanguis::server::player_id
	);

	sanguis::server::entities::optional_player_ref const
	player_opt(
		sanguis::server::player_id
	);

	sanguis::random_generator random_generator_;

	sanguis::entity_id next_id_;

	sanguis::server::unicast_callback const send_unicast_;

	typedef
	std::unique_ptr<
		sanguis::server::environment::load_context
	>
	load_context_unique_ptr;

	load_context_unique_ptr const load_context_;

	sanguis::server::console &console_;

	typedef
	fcppt::reference_wrapper<
		sanguis::server::entities::player
	>
	player_ref;

	typedef
	std::unordered_map<
		sanguis::server::player_id,
		player_ref
	>
	player_map;

	player_map players_;

	sanguis::server::global::world_map const worlds_;
};

}
}
}

#endif
