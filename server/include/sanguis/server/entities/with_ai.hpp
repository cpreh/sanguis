#ifndef SANGUIS_SERVER_ENTITIES_WITH_AI_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_AI_HPP_INCLUDED

#include <sanguis/diff_timer.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/tree/base_unique_ptr.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/entities/transfer_result_fwd.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <sanguis/server/entities/with_auras_id.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/ifaces/with_health.hpp>
#include <sanguis/server/entities/ifaces/with_links.hpp>
#include <sanguis/server/entities/ifaces/with_radius.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/ifaces/with_velocity.hpp>
#include <sanguis/server/weapons/ias.hpp>
#include <sanguis/server/weapons/irs.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class with_ai
:
	public virtual sanguis::server::entities::ifaces::with_angle,
	public virtual sanguis::server::entities::ifaces::with_health,
	public virtual sanguis::server::entities::ifaces::with_links,
	public virtual sanguis::server::entities::ifaces::with_radius,
	public virtual sanguis::server::entities::ifaces::with_team,
	public virtual sanguis::server::entities::ifaces::with_velocity,
	public sanguis::server::entities::with_auras_id,
	public sanguis::server::entities::with_weapon
{
	FCPPT_NONCOPYABLE(
		with_ai
	);
protected:
	with_ai(
		sanguis::server::ai::create_function const &,
		sanguis::server::weapons::unique_ptr &&,
		sanguis::server::auras::container &&,
		sanguis::server::weapons::ias,
		sanguis::server::weapons::irs
	);

	~with_ai()
	override;

	void
	update()
	override;

	sanguis::server::entities::transfer_result
	on_create()
	override;
public:
	sanguis::server::ai::create_function const &
	create_ai() const;
private:
	sanguis::diff_timer update_timer_;

	sanguis::server::ai::create_function const create_ai_;

	sanguis::server::ai::context ai_context_;

	using
	optional_ai_unique_ptr
	=
	fcppt::optional::object<
		sanguis::server::ai::tree::base_unique_ptr
	>;

	optional_ai_unique_ptr ai_;
};

}
}
}

#endif
