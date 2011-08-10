#ifndef SANGUIS_SERVER_GLOBAL_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_CONTEXT_HPP_INCLUDED

#include "context_fwd.hpp"
#include "world_context_fwd.hpp"
#include "../world/map.hpp"
#include "../world/context_fwd.hpp"
#include "../entities/unique_ptr.hpp"
#include "../entities/insert_parameters_fwd.hpp"
#include "../entities/player_map.hpp"
#include "../environment/load_context_fwd.hpp"
#include "../console_fwd.hpp"
#include "../player_id.hpp"
#include "../speed.hpp"
#include "../string.hpp"
#include "../unicast_callback.hpp"
#include "../vector.hpp"
#include "../../cheat_type.hpp"
#include "../../connect_state.hpp"
#include "../../diff_clock.hpp"
#include "../../duration_fwd.hpp"
#include "../../perk_type.hpp"
#include "../../weapon_type.hpp"
#include "../../world_id.hpp"
#include "../../messages/auto_ptr.hpp"
#include "../../load/context_base_fwd.hpp"
#include <fcppt/function/object.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/container/map_decl.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace global
{

class context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context(
		server::unicast_callback const &,
		load::context_base const &,
		server::console &
	);

	~context();

	void
	insert_player(
		sanguis::world_id,
		server::player_id,
		server::string const &name,
		sanguis::connect_state::type
	);

	void
	player_disconnect(
		server::player_id
	);

	void
	player_target(
		server::player_id,
		server::vector const &
	);

	void
	player_change_weapon(
		server::player_id,
		weapon_type::type
	);

	void
	player_change_shooting(
		server::player_id,
		bool shooting
	);

	void
	player_speed(
		server::player_id,
		server::speed const &
	);

	void
	player_cheat(
		server::player_id,
		cheat_type::type
	);

	void
	player_choose_perk(
		player_id,
		perk_type::type
	);

	void
	update(
		sanguis::duration const &
	);

	entities::player_map::size_type
	player_count() const;
private:
	friend class world_context;

	// callbacks for world

	void
	send_to_player(
		player_id,
		messages::auto_ptr
	);

	void
	remove_player(
		player_id
	);

	void
	transfer_entity(
		world_id destination,
		entities::unique_ptr,
		entities::insert_parameters const &
	);

	server::world::object &
	world(
		world_id
	);

	static fcppt::log::object &
	log();

	sanguis::diff_clock diff_clock_;

	unicast_callback const send_unicast_;

	typedef fcppt::scoped_ptr<
		server::world::context
	> world_context_scoped_ptr;

	world_context_scoped_ptr const world_context_;

	typedef fcppt::scoped_ptr<
		server::environment::load_context
	> load_context_scoped_ptr;

	load_context_scoped_ptr const load_context_;

	server::console &console_;

	entities::player_map players_;

	world::map worlds_;
};

}
}
}

#endif
