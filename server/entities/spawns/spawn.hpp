#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED

#include "count.hpp"
#include "../base.hpp"
#include "../../team.hpp"
#include "../../../enemy_type.hpp"
#include "../../../entity_type.hpp"
#include "../../../time_type.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace spawns
{

class spawn
:
	public base
{
	FCPPT_NONCOPYABLE(spawn)
protected:
	explicit spawn(
		enemy_type::type
	);
private:
	entity_type::type
	type() const;

	server::team::type
	team() const;

	void
	on_update(
		time_type
	);

	count
	may_spawn(
		time_type
	) = 0;
};

}
}
}
}

#endif
