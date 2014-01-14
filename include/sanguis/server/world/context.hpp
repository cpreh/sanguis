#ifndef SANGUIS_SERVER_WORLD_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_CONTEXT_HPP_INCLUDED

#include <sanguis/world_id.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/global/source_world_pair.hpp>
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
	bool
	request_transfer(
		sanguis::server::global::source_world_pair
	) const = 0;

	virtual
	void
	transfer_entity(
		sanguis::server::global::source_world_pair,
		sanguis::server::entities::unique_ptr &&
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
