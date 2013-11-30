#include <sanguis/diff_timer.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/optional_target.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/poll.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>
#include <sanguis/server/weapons/events/stop.hpp>
#include <sanguis/server/weapons/states/backswing.hpp>
#include <sanguis/server/weapons/states/backswing_parameters.hpp>
#include <sanguis/server/weapons/states/castpoint.hpp>
#include <sanguis/server/weapons/states/castpoint_parameters.hpp>
#include <sanguis/server/weapons/states/ready.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/pi.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/normal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::weapons::states::castpoint::castpoint(
	my_context _ctx,
	sanguis::server::weapons::states::castpoint_parameters const &_parameters
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
			_parameters.ias().get()
		)
	),
	cancelled_(
		false
	)
{
}

FCPPT_PP_POP_WARNING

sanguis::server::weapons::states::castpoint::~castpoint()
{
}

boost::statechart::result
sanguis::server::weapons::states::castpoint::react(
	sanguis::server::weapons::events::poll const &_event
)
{
	sanguis::server::weapons::optional_target const target(
		_event.owner().target()
	);

	if(
		!target
		||
		!attack_time_.expired()
	)
		return
			this->discard_event();

	sanguis::server::space_unit const spread(
		(
			fcppt::literal<
				sanguis::server::space_unit
			>(
				1
			)
			-
			this->context<
				sanguis::server::weapons::weapon
			>().accuracy().get()
		)
		*
		fcppt::math::pi<
			sanguis::server::space_unit
		>()
		/
		fcppt::literal<
			sanguis::server::space_unit
		>(
			4
		)
	);

	typedef
	fcppt::random::distribution::parameters::normal<
		sanguis::server::space_unit
	>
	normal_distribution;

	auto angle_distribution(
		fcppt::random::distribution::make_basic(
			normal_distribution(
				normal_distribution::mean(
					_event.owner().angle().get()
				),
				normal_distribution::stddev(
					spread
				)
			)
		)
	);

	if(
		this->context<
			sanguis::server::weapons::weapon
		>().do_attack(
			sanguis::server::weapons::delayed_attack(
				_event.owner().center(),
				sanguis::server::angle(
					angle_distribution(
						this->context<
							sanguis::server::weapons::weapon
						>().random_generator()
					)
				),
				_event.owner().team(),
				*_event.owner().environment(),
				*target
			)
		)
	)
		this->context<
			sanguis::server::weapons::weapon
		>().use_magazine_item();

	if(
		cancelled_
	)
		this->post_event(
			sanguis::server::weapons::events::stop()
		);

	return
		this->transit<
			sanguis::server::weapons::states::backswing
		>(
			sanguis::server::weapons::states::backswing_parameters(
				_event.owner().ias()
			)
		);
}

boost::statechart::result
sanguis::server::weapons::states::castpoint::react(
	sanguis::server::weapons::events::stop const &
)
{
	cancelled_ = true;

	return
		this->discard_event();
}
