#include <sanguis/diff_timer.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/update_interval.hpp>
#include <sanguis/server/ai/tree/base.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_auras_id.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/ifaces/with_links.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/weapons/ias.hpp>
#include <sanguis/server/weapons/irs.hpp>
#include <sanguis/server/weapons/optional_unique_ptr.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::with_ai::with_ai(
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
		sanguis::server::weapons::optional_unique_ptr(
			std::move(
				_start_weapon
			)
		),
		_ias,
		_irs
	),
	update_timer_(
		sanguis::diff_timer::parameters(
			this->diff_clock(),
			sanguis::server::ai::update_interval()
		)
		.expired(
			true
		)
	),
	create_ai_{
		_create_ai
	},
	ai_context_(
		*this
	),
	ai_()
{
}

sanguis::server::entities::with_ai::~with_ai()
{
}

void
sanguis::server::entities::with_ai::update()
{
	FCPPT_ASSERT_PRE(
		ai_
	);

	sanguis::server::entities::with_weapon::update();

	if(
		update_timer_.expired()
	)
	{
		// TODO: Make this easier in sge
		ai_->run(
			update_timer_.now()
			-
			update_timer_.last_time()
		);

		update_timer_.reset();
	}
}

void
sanguis::server::entities::with_ai::on_create()
{
	ai_ =
		create_ai_(
			ai_context_
		);
}
