#ifndef SANGUIS_SERVER_ENTITIES_CENTER_GHOST_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_CENTER_GHOST_HPP_INCLUDED

#include <sanguis/server/entities/center_simple.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class center_ghost
:
	public sanguis::server::entities::center_simple,
	public virtual sanguis::server::entities::with_ghosts
{
	FCPPT_NONCOPYABLE(
		center_ghost
	);
protected:
	center_ghost();
public:
	virtual
	~center_ghost() = 0;
protected:
	bool
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	)
	override
	final;
};

}
}
}

#endif
