#ifndef SANGUIS_SERVER_ENTITIES_WITH_AI_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_AI_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/manager_fwd.hpp>
#include <sanguis/server/ai/scoped_ptr.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <sanguis/server/entities/with_auras_id.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/ifaces/with_links.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/weapons/ias.hpp>
#include <sanguis/server/weapons/irs.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class with_ai
:
	public virtual sanguis::server::entities::ifaces::with_links,
	public virtual sanguis::server::entities::ifaces::with_team,
	public sanguis::server::entities::with_auras_id,
	public sanguis::server::entities::with_weapon
{
	FCPPT_NONCOPYABLE(
		with_ai
	);
protected:
	with_ai(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::server::ai::create_function const &,
		sanguis::server::weapons::unique_ptr &&,
		sanguis::server::auras::container &&,
		sanguis::server::weapons::ias,
		sanguis::server::weapons::irs
	);

	~with_ai();

	virtual
	void
	update()
	override;
public:
	sanguis::server::ai::base const &
	ai() const;
private:
	void
	on_create()
	override;

	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	sanguis::server::ai::scoped_ptr ai_;

	typedef
	fcppt::scoped_ptr<
		sanguis::server::ai::manager
	> manager_scoped_ptr;

	manager_scoped_ptr manager_;
};

}
}
}

#endif
