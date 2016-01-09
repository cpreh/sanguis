#include <sanguis/diff_timer.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/weapons/attack.hpp>
#include <sanguis/server/weapons/attack_result.hpp>
#include <sanguis/server/weapons/log.hpp>
#include <sanguis/server/weapons/random_angle.hpp>
#include <sanguis/server/weapons/target.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/accuracy.hpp>
#include <sanguis/server/weapons/events/poll.hpp>
#include <sanguis/server/weapons/events/reload.hpp>
#include <sanguis/server/weapons/events/stop.hpp>
#include <sanguis/server/weapons/states/backswing.hpp>
#include <sanguis/server/weapons/states/castpoint.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::weapons::states::castpoint::castpoint(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	attack_time_(
		sanguis::diff_timer::parameters(
			this->context<
				sanguis::server::weapons::weapon
			>().diff_clock(),
			this->context<
				sanguis::server::weapons::weapon
			>().cast_point().get()
			/
			this->context<
				sanguis::server::weapons::weapon
			>().owner().ias().get()
		)
	),
	cancelled_(
		false
	)
{
	this->context<
		sanguis::server::weapons::weapon
	>().weapon_status(
		sanguis::weapon_status::attacking
	);

	FCPPT_LOG_VERBOSE(
		sanguis::server::weapons::log(),
		fcppt::log::_
			<< FCPPT_TEXT("castpoint: ")
			<< this
	);
}

FCPPT_PP_POP_WARNING

sanguis::server::weapons::states::castpoint::~castpoint()
{
}

boost::statechart::result
sanguis::server::weapons::states::castpoint::react(
	sanguis::server::weapons::events::poll const &
)
{
	if(
		!attack_time_.expired()
	)
		return
			this->discard_event();

	sanguis::server::entities::with_weapon &owner(
		this->context<
			sanguis::server::weapons::weapon
		>().owner()
	);

	return
		fcppt::optional::maybe(
			owner.target(),
			[
				this
			]{
				this->post_event(
					sanguis::server::weapons::events::stop()
				);

				return
					this->transit<
						sanguis::server::weapons::states::backswing
					>();
			},
			[
				&owner,
				this
			](
				sanguis::server::weapons::target const _target
			)
			{
				switch(
					this->context<
						sanguis::server::weapons::weapon
					>().do_attack(
						sanguis::server::weapons::attack(
							fcppt::optional::maybe(
								this->context<
									sanguis::server::weapons::weapon
								>().accuracy(),
								[
									&owner
								]{
									return
										owner.angle();
								},
								[
									&owner,
									this
								](
									sanguis::server::weapons::attributes::accuracy const _accuracy
								)
								{
									return
										sanguis::server::weapons::random_angle(
											this->context<
												sanguis::server::weapons::weapon
											>().random_generator(),
											_accuracy.value(),
											owner.angle()
										);
								}
							),
							FCPPT_ASSERT_OPTIONAL_ERROR(
								owner.environment()
							).get(),
							_target
						)
					)
				)
				{
				case sanguis::server::weapons::attack_result::success:
					this->context<
						sanguis::server::weapons::weapon
					>().use_magazine_item();

					break;
				case sanguis::server::weapons::attack_result::failure:
					break;
				}

				if(
					cancelled_
				)
					this->post_event(
						sanguis::server::weapons::events::stop()
					);

				return
					this->transit<
						sanguis::server::weapons::states::backswing
					>();
			}
		);
}

boost::statechart::result
sanguis::server::weapons::states::castpoint::react(
	sanguis::server::weapons::events::stop const &
)
{
	cancelled_ =
		true;

	return
		this->discard_event();
}
