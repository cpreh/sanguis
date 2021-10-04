#ifndef SANGUIS_SERVER_ENTITIES_WITH_ID_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_ID_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_id_fwd.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::entities
{

class with_id
:
	public virtual sanguis::server::entities::base,
	public virtual sanguis::server::entities::ifaces::with_id
{
	FCPPT_NONMOVABLE(
		with_id
	);
protected:
	explicit
	with_id(
		sanguis::entity_id
	);
public:
	~with_id()
	override = 0;

	[[nodiscard]]
	sanguis::entity_id
	id() const
	override;

	virtual
	void
	transfer_to_world();

	void
	transfer_from_world();

	[[nodiscard]]
	virtual
	sanguis::messages::server::unique_ptr
	add_message(
		sanguis::server::player_id,
		sanguis::collision::world::created
	) const = 0;
private:
	sanguis::entity_id const id_;
};

}

#endif
