#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED

#include "size_type.hpp"
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
	public virtual entities::base
{
	FCPPT_NONCOPYABLE(spawn)
public:
	virtual void
	unregister(
		entities::base &
	);

	~spawn();
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

	virtual size_type 
	may_spawn(
		time_type
	) = 0;

	enemy_type::type const enemy_type_;
};

}
}
}
}

#endif
