#ifndef SANGUIS_SERVER_ENTITIES_WITH_AI_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_AI_HPP_INCLUDED

#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/scoped_ptr.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class with_ai
:
	public virtual sanguis::server::entities::ifaces::with_team,
	public sanguis::server::entities::with_auras,
	public sanguis::server::entities::with_weapon
{
	FCPPT_NONCOPYABLE(
		with_ai
	);
protected:
	with_ai(
		sanguis::server::ai::create_function const &,
		sanguis::server::weapons::unique_ptr &&start_weapon
	);

	~with_ai();

	virtual
	void
	on_update()
	override;
private:
	void
	on_create()
	override;

	sanguis::server::ai::create_function const create_ai_;

	sanguis::server::ai::scoped_ptr ai_;
};

}
}
}

#endif
