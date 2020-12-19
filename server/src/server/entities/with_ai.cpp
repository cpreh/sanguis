#include <sanguis/diff_timer.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/update_interval.hpp>
#include <sanguis/server/ai/tree/base.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_auras_id.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/weapons/ias.hpp>
#include <sanguis/server/weapons/irs.hpp>
#include <sanguis/server/weapons/optional_unique_ptr.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::entities::with_ai::with_ai(
	sanguis::server::ai::create_function &&_create_ai,
	sanguis::server::weapons::unique_ptr &&_start_weapon,
	sanguis::server::auras::container &&_auras,
	sanguis::server::weapons::ias const _ias,
	sanguis::server::weapons::irs const _irs
)
:
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
			fcppt::make_cref(
				this->diff_clock()
			),
			sanguis::server::ai::update_interval()
		)
		.expired(
			true
		)
	),
	create_ai_{
		std::move(
			_create_ai
		)
	},
	ai_context_(
		fcppt::make_ref(
			*this
		)
	),
	ai_()
{
}

FCPPT_PP_POP_WARNING

sanguis::server::entities::with_ai::~with_ai()
= default;

void
sanguis::server::entities::with_ai::update()
{
	sanguis::server::entities::with_weapon::update();

	if(
		update_timer_.expired()
	)
	{
		// TODO(philipp): Make this easier in sge
		FCPPT_ASSERT_OPTIONAL_ERROR(
			ai_
		)->run(
			update_timer_.now()
			-
			update_timer_.last_time()
		);

		update_timer_.reset();
	}
}

sanguis::server::entities::transfer_result
sanguis::server::entities::with_ai::on_create()
{
	// TODO(philipp): Improve this!
	sanguis::server::ai::tree::base_unique_ptr new_ai(
		create_ai_(
			fcppt::make_ref(
				ai_context_
			)
		)
	);

	sanguis::server::ai::tree::base &ai_ref(
		*new_ai
	);

	ai_ =
		optional_ai_unique_ptr(
			std::move(
				new_ai
			)
		);

	return
		ai_ref.transfer();
}

sanguis::server::ai::create_function const &
sanguis::server::entities::with_ai::create_ai() const
{
	return
		create_ai_;
}
