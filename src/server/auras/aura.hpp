#ifndef SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED

#include "influence.hpp"
#include "../radius.hpp"
#include "../entities/with_body_fwd.hpp"
#include "../collision/body_base_fwd.hpp"
#include "../collision/ghost_unique_ptr.hpp"
#include "../collision/group_vector.hpp"
#include "../team.hpp"
#include "../../entity_id.hpp"
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>

namespace sanguis
{
namespace server
{
namespace auras
{

class aura
{
	FCPPT_NONCOPYABLE(
		aura
	);
public:
	virtual ~aura();

	void
	owner(
		entity_id
	);

	collision::ghost_unique_ptr
	recreate(
		collision::ghost_parameters const &
	);
protected:
	aura(
		server::radius,
		server::team::type,
		auras::influence::type
	);
	
	sanguis::entity_id
	owner() const;
private:
	virtual collision::group_vector const
	collision_groups() const;

	void
	collision_begin(
		collsion::body_base &
	);

	void
	collision_end(
		collsion::body_base &
	);

	virtual void
	enter(
		entities::with_body &
	) = 0;

	virtual void
	leave(
		entities::with_body &
	) = 0;

	server::team::type const team_;

	auras::influence::type const influence_;

	typedef fcppt::optional<
		sanguis::entity_id
	> optional_entity_id;

	optional_entity_id owner_;
};

}
}
}

#endif
