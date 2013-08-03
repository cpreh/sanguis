#include <sanguis/server/ai/base.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::with_ai::with_ai(
	sanguis::server::ai::create_function const &_create_ai,
	sanguis::server::weapons::unique_ptr &&_start_weapon
)
:
	sanguis::server::entities::ifaces::with_team(),
	sanguis::server::entities::with_auras(),
	sanguis::server::entities::with_weapon(
		std::move(
			_start_weapon
		)
	),
	create_ai_(
		_create_ai
	),
	ai_()
{
}

sanguis::server::entities::with_ai::~with_ai()
{
}

void
sanguis::server::entities::with_ai::on_update()
{
	sanguis::server::entities::with_weapon::on_update();

	FCPPT_ASSERT_PRE(
		ai_
	);

	ai_->update();
}

void
sanguis::server::entities::with_ai::on_create()
{
	ai_.take(
		create_ai_(
			*this
		)
	);
}
