#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED

#include "size_type.hpp"
#include "../base.hpp"
#include "../../center.hpp"
#include "../../team.hpp"
#include "../../../enemy_type.hpp"
#include "../../../entity_type.hpp"
#include "../../../time_delta_fwd.hpp"
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
	FCPPT_NONCOPYABLE(
		spawn
	);
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

	server::center const
	center() const;

	void
	on_update(
		sanguis::time_delta const &
	);

	virtual size_type 
	may_spawn(
		sanguis::time_delta const &
	) = 0;

	virtual void
	add_count(
		size_type
	) = 0;

	enemy_type::type const enemy_type_;
};

}
}
}
}

#endif
