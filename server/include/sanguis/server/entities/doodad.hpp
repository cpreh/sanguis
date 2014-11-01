#ifndef SANGUIS_SERVER_ENTITIES_DOODAD_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_DOODAD_HPP_INCLUDED

#include <sanguis/doodad_type.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/player_id_fwd.hpp>
#include <sanguis/server/entities/center_simple.hpp>
#include <sanguis/server/entities/doodad_fwd.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class doodad
:
	public sanguis::server::entities::with_id,
	public sanguis::server::entities::center_simple
{
	FCPPT_NONCOPYABLE(
		doodad
	);
protected:
	doodad(
		sanguis::server::environment::load_context &,
		sanguis::doodad_type
	);
public:
	~doodad()
	override = 0;

	void
	kill();

	bool
	dead() const
	override;
private:
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
