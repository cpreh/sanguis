#ifndef SANGUIS_SERVER_ENTITIES_WITH_GHOSTS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_GHOSTS_HPP_INCLUDED

#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/collision/ghost_container.hpp>
#include <sanguis/server/collision/ghost_fwd.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/optional_transfer_result_fwd.hpp>
#include <sanguis/server/entities/remove_from_world_result_fwd.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class with_ghosts
:
	public virtual sanguis::server::entities::base
{
	FCPPT_NONMOVABLE(
		with_ghosts
	);
public:
	with_ghosts();

	explicit
	with_ghosts(
		sanguis::server::collision::ghost_container &&
	);

	~with_ghosts()
	override;
protected:
	[[nodiscard]]
	sanguis::collision::world::body_enter_container
	add_ghost(
		sanguis::server::collision::ghost &&
	);

	void
	init_ghosts(
		sanguis::server::collision::ghost_container &&
	);

	[[nodiscard]]
	sanguis::server::entities::optional_transfer_result
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	)
	override;

	[[nodiscard]]
	sanguis::server::entities::remove_from_world_result
	remove_from_world()
	override;

	void
	update_ghost_center(
		sanguis::server::center const &
	);
private:
	sanguis::server::collision::ghost_container ghosts_;
};

}
}
}

#endif
