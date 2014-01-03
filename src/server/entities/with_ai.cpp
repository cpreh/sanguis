#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/ai/base.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/manager.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_auras_id.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/ifaces/with_links.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/weapons/ias.hpp>
#include <sanguis/server/weapons/irs.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::with_ai::with_ai(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator  &_random_generator,
	sanguis::server::ai::create_function const &_create_ai,
	sanguis::server::weapons::unique_ptr &&_start_weapon,
	sanguis::server::auras::container &&_auras,
	sanguis::server::weapons::ias const _ias,
	sanguis::server::weapons::irs const _irs
)
:
	sanguis::server::entities::ifaces::with_links(),
	sanguis::server::entities::ifaces::with_team(),
	sanguis::server::entities::with_auras_id(
		std::move(
			_auras
		)
	),
	sanguis::server::entities::with_weapon(
		std::move(
			_start_weapon
		),
		_ias,
		_irs
	),
	diff_clock_(
		_diff_clock
	),
	random_generator_(
		_random_generator
	),
	ai_(
		_create_ai(
			*this
		)
	),
	manager_()
{
}

sanguis::server::entities::with_ai::~with_ai()
{
}

void
sanguis::server::entities::with_ai::update()
{
	sanguis::server::entities::with_weapon::update();

	FCPPT_ASSERT_PRE(
		manager_
	);

	manager_->update();
}

sanguis::server::ai::base const &
sanguis::server::entities::with_ai::ai() const
{
	return
		*ai_;
}

void
sanguis::server::entities::with_ai::on_create()
{
	manager_.take(
		fcppt::make_unique_ptr<
			sanguis::server::ai::manager
		>(
			diff_clock_,
			random_generator_,
			*ai_,
			*this
		)
	);
}
