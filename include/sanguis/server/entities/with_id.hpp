#ifndef SANGUIS_SERVER_ENTITIES_WITH_ID_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_ID_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_id_fwd.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class with_id
:
	public virtual sanguis::server::entities::base,
	public virtual sanguis::server::entities::ifaces::with_id
{
	FCPPT_NONCOPYABLE(
		with_id
	);
protected:
	explicit
	with_id(
		sanguis::entity_id
	);
public:
	virtual
	~with_id() = 0;

	sanguis::entity_id const
	id() const
	override;

	virtual
	sanguis::messages::unique_ptr
	add_message(
		sanguis::server::player_id
	) const = 0;
private:
	sanguis::entity_id const id_;
};

}
}
}

#endif