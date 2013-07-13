#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_HIDDEN_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_HIDDEN_HPP_INCLUDED

#include <sanguis/server/entities/base.hpp>
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
	public virtual sanguis::server::entities::base
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
};

}
}
}
}

#endif
