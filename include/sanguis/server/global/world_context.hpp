#ifndef SANGUIS_SERVER_GLOBAL_WORLD_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_WORLD_CONTEXT_HPP_INCLUDED

#include <sanguis/world_id.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/global/context_fwd.hpp>
#include <sanguis/server/global/world_context_fwd.hpp>
#include <sanguis/server/world/context.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace global
{

class world_context
:
	public sanguis::server::world::context
{
	FCPPT_NONCOPYABLE(
		world_context
	);
public:
	explicit
	world_context(
		sanguis::server::global::context &
	);

	~world_context();

	void
	transfer_entity(
		sanguis::world_id destination,
		sanguis::server::entities::unique_ptr &&,
		sanguis::server::entities::insert_parameters const &
	);

	void
	send_to_player(
		sanguis::server::player_id,
		sanguis::messages::base const &
	);

	void
	remove_player(
		sanguis::server::player_id
	);
private:
	sanguis::server::global::context &global_context_;
};

}
}
}

#endif
