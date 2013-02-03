#ifndef SANGUIS_SERVER_WORLD_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_CONTEXT_HPP_INCLUDED

#include <sanguis/world_id.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/world/context_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

class context
{
	FCPPT_NONCOPYABLE(
		context
	);
protected:
	context();
public:
	virtual
	void
	transfer_entity(
		sanguis::world_id destination,
		sanguis::server::entities::unique_ptr &&,
		sanguis::server::entities::insert_parameters const &
	) = 0;

	virtual
	void
	send_to_player(
		sanguis::server::player_id,
		sanguis::messages::base const &
	) = 0;

	virtual
	void
	remove_player(
		sanguis::server::player_id
	) = 0;

	virtual
	~context();
};

}
}
}

#endif
