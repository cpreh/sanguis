#ifndef SANGUIS_SERVER_ENTITIES_DOODAD_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_DOODAD_HPP_INCLUDED

#include <sanguis/doodad_type.hpp>
#include <sanguis/collision/world/body_group_fwd.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/player_id_fwd.hpp>
#include <sanguis/server/entities/doodad_fwd.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class doodad
:
	public sanguis::server::entities::with_body,
	public sanguis::server::entities::with_id,
	public sanguis::server::entities::with_links
{
	FCPPT_NONMOVABLE(
		doodad
	);
protected:
	doodad(
		sanguis::server::environment::load_context &, // NOLINT(google-runtime-references)
		sanguis::doodad_type
	);
public:
	~doodad()
	override = 0;

	void
	kill();

	[[nodiscard]]
	bool
	dead() const
	override;

	void
	update()
	override;
private:
	[[nodiscard]]
	sanguis::collision::world::body_group
	collision_group() const
	override;

	[[nodiscard]]
	sanguis::messages::server::unique_ptr
	add_message(
		sanguis::server::player_id,
		sanguis::collision::world::created
	) const
	override;

	sanguis::doodad_type const doodad_type_;

	bool dead_;
};

}
}
}

#endif
