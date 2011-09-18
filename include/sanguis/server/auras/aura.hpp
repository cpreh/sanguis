#ifndef SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED

#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/collision/body_base_fwd.hpp>
#include <sanguis/server/collision/ghost_base.hpp>
#include <sanguis/server/collision/ghost_unique_ptr.hpp>
#include <sanguis/server/collision/group_vector.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/entity_id.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool_fwd.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace server
{
namespace auras
{

class aura
:
	private collision::ghost_base
{
	FCPPT_NONCOPYABLE(
		aura
	);
public:
	virtual ~aura();

	void
	owner(
		sanguis::entity_id
	);

	collision::ghost_unique_ptr
	recreate();
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

	boost::logic::tribool const
	can_collide_with(
		collision::body_base const &
	) const;

	void
	body_enter(
		collision::body_base &
	);

	void
	body_exit(
		collision::body_base &
	);

	virtual void
	enter(
		entities::with_body &
	) = 0;

	virtual void
	leave(
		entities::with_body &
	) = 0;

	server::radius const radius_;

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
