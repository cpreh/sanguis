#ifndef SANGUIS_SERVER_AURAS_TARGET_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_TARGET_HPP_INCLUDED

#include <sanguis/optional_aura_type_fwd.hpp>
#include <sanguis/server/add_target_callback.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/remove_target_callback.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/target_kind_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

class target
:
	public sanguis::server::auras::aura
{
	FCPPT_NONCOPYABLE(
		target
	);
public:
	target(
		sanguis::server::radius,
		sanguis::server::team,
		sanguis::server::auras::target_kind,
		sanguis::server::add_target_callback const &,
		sanguis::server::remove_target_callback const &
	);

	~target()
	override;
private:
	sanguis::optional_aura_type const
	type() const
	override;

	void
	enter(
		sanguis::server::entities::with_body &
	)
	override;

	void
	leave(
		sanguis::server::entities::with_body &
	)
	override;

	sanguis::server::add_target_callback const add_target_;

	sanguis::server::remove_target_callback const remove_target_;
};

}
}
}

#endif
