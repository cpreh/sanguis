#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_HIDDEN_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_HIDDEN_HPP_INCLUDED

#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace spawns
{

class hidden
:
	public virtual base
{
	FCPPT_NONCOPYABLE(
		hidden
	);
protected:
	hidden();

	~hidden();
private:
	bool
	dead() const;

	bool
	invulnerable() const;

	bool
	server_only() const;

	messages::auto_ptr
	add_message(
		player_id
	) const;
};

}
}
}
}

#endif
