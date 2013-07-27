#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/console.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/player_id_from_args.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/waves/generator.hpp>
#include <sanguis/server/waves/infinite.hpp>
#include <sanguis/server/waves/make.hpp>
#include <sanguis/server/waves/single.hpp>
#include <sanguis/server/waves/convert_enemy_name.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>
#include <sge/font/to_fcppt_string.hpp>
#include <fcppt/extract_from_string_exn.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/config/external_begin.hpp>
#if defined(BOOST_ASSIGN_MAX_PARAMS)
#undef BOOST_ASSIGN_MAX_PARAMS
#endif
#define BOOST_ASSIGN_MAX_PARAMS 6
#include <boost/assign/ptr_list_inserter.hpp>
#undef BOOST_ASSIGN_MAX_PARAMS
#include <boost/ref.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


// NOTE: be careful when we move this class because
// it should not register the functions more than once

sanguis::server::waves::generator::generator(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::console &_console
)
:
	diff_clock_(
		_diff_clock
	),
	random_generator_(
		_random_generator
	),
	console_(
		_console
	),
	spawn_connection_(
		console_.insert(
			FCPPT_TEXT("spawn"),
			std::bind(
				&sanguis::server::waves::generator::spawn,
				this,
				std::placeholders::_1
			),
			FCPPT_TEXT("spawn wave (wavename) [count], spawn enemy (enemyname) [count] or spawn all")
		)
	),
	waves_()
{
}

sanguis::server::waves::generator::~generator()
{
}

void
sanguis::server::waves::generator::process(
	environment::object &_env,
	environment::load_context &_load_context
)
{
	for(
		wave_list::iterator it(
			waves_.begin()
		);
		it != waves_.end();
	)
	{
		it->process(
			_env,
			_load_context
		);

		if(
			it->ended()
		)
			it = waves_.erase(it);
		else
			++it;
	}
}

void
sanguis::server::waves::generator::spawn(
	sge::console::arg_list const &_args
)
try
{
	if(
		_args.size() == 3u
		&& _args[1] == SGE_FONT_LIT("all")
	)
	{
		this->spawn_all();

		return;
	}

	if(
		_args.size() != 4u && _args.size() != 5u
	)
	{
		console_.print_line(
			sanguis::server::player_id_from_args(
				_args
			),
			FCPPT_TEXT("Invalid parameter count for spawn command.")
		);

		return;
	}

	sge::font::string const action(
		_args[1]
	);

	unsigned const count(
		_args.size() == 5u
		?
			fcppt::extract_from_string_exn<
				unsigned
			>(
				_args[3]
			)
		:
			1u
	);

	if(
		action == SGE_FONT_LIT("wave")
	)
		for(
			unsigned i = 0;
			i < count;
			++i
		)
			fcppt::container::ptr::push_back_unique_ptr(
				waves_,
				sanguis::server::waves::make(
					diff_clock_,
					random_generator_,
					sge::font::to_fcppt_string(
						_args[2]
					)
				)
			);
	else if(
		action == SGE_FONT_LIT("enemy")
	)
		for(
			unsigned i = 0;
			i < count;
			++i
		)
			fcppt::container::ptr::push_back_unique_ptr(
				waves_,
				fcppt::make_unique_ptr<
					sanguis::server::waves::single
				>(
					diff_clock_,
					random_generator_,
					sanguis::server::waves::convert_enemy_name(
						sge::font::to_fcppt_string(
							_args[2]
						)
					)
				)
			);
	else
	{
		console_.print_line(
			sanguis::server::player_id_from_args(
				_args
			),
			FCPPT_TEXT("Invalid argument for spawn command.")
		);
	}
}
catch(
	fcppt::exception const &error
)
{
	console_.print_line(
		sanguis::server::player_id_from_args(
			_args
		),
		error.string()
	);
}

void
sanguis::server::waves::generator::spawn_all()
{
	// TODO: Somehow put this in a configuration file!
	// TODO: Also create something that works better with C++11
	boost::assign::ptr_push_back<
		sanguis::server::waves::infinite
	>(
		waves_
	)
	(
		boost::cref(
			diff_clock_
		),
		boost::ref(
			random_generator_
		),
		sanguis::server::waves::delay(
			sanguis::duration_second(
				60.f
			)
		),
		sanguis::server::waves::spawn_interval(
			sanguis::duration_second(
				40
			)
		),
		sanguis::server::waves::spawns_per_wave(
			5u
		),
		sanguis::enemy_type::spider
	)(
		boost::cref(
			diff_clock_
		),
		boost::ref(
			random_generator_
		),
		sanguis::server::waves::delay(
			sanguis::duration_second(
				0.f
			)
		),
		sanguis::server::waves::spawn_interval(
			sanguis::duration_second(
				9.f
			)
		),
		sanguis::server::waves::spawns_per_wave(
			15u
		),
		sanguis::enemy_type::maggot
	)(
		boost::cref(
			diff_clock_
		),
		boost::ref(
			random_generator_
		),
		sanguis::server::waves::delay(
			sanguis::duration_second(
				50.f
			)
		),
		sanguis::server::waves::spawn_interval(
			sanguis::duration_second(
				20
			)
		),
		sanguis::server::waves::spawns_per_wave(
			10u
		),
		sanguis::enemy_type::maggot
	)(
		boost::cref(
			diff_clock_
		),
		boost::ref(
			random_generator_
		),
		sanguis::server::waves::delay(
			sanguis::duration_second(
				0.f
			)
		),
		sanguis::server::waves::spawn_interval(
			sanguis::duration_second(
				30.f
			)
		),
		sanguis::server::waves::spawns_per_wave(
			8u
		),
		sanguis::enemy_type::zombie01
	)(
		boost::cref(
			diff_clock_
		),
		boost::ref(
			random_generator_
		),
		sanguis::server::waves::delay(
			sanguis::duration_second(
				0.f
			)
		),
		sanguis::server::waves::spawn_interval(
			sanguis::duration_second(
				30.f
			)
		),
		sanguis::server::waves::spawns_per_wave(
			8u
		),
		sanguis::enemy_type::zombie01
	)(
		boost::cref(
			diff_clock_
		),
		boost::ref(
			random_generator_
		),
		sanguis::server::waves::delay(
			sanguis::duration_second(
				90.f
			)
		),
		sanguis::server::waves::spawn_interval(
			sanguis::duration_second(
				60
			)
		),
		sanguis::server::waves::spawns_per_wave(
			7u
		),
		sanguis::enemy_type::zombie00
	)(
		boost::cref(
			diff_clock_
		),
		boost::ref(
			random_generator_
		),
		sanguis::server::waves::delay(
			sanguis::duration_second(
				45.f
			)
		),
		sanguis::server::waves::spawn_interval(
			sanguis::duration_second(
				30.f
			)
		),
		sanguis::server::waves::spawns_per_wave(
			3u
		),
		sanguis::enemy_type::wolf_brown
	)(
		boost::cref(
			diff_clock_
		),
		boost::ref(
			random_generator_
		),
		sanguis::server::waves::delay(
			sanguis::duration_second(
				80.f
			)
		),
		sanguis::server::waves::spawn_interval(
			sanguis::duration_second(
				30.f
			)
		),
		sanguis::server::waves::spawns_per_wave(
			3u
		),
		sanguis::enemy_type::wolf_white
	)(
		boost::cref(
			diff_clock_
		),
		boost::ref(
			random_generator_
		),
		sanguis::server::waves::delay(
			sanguis::duration_second(
				120.f
			)
		),
		sanguis::server::waves::spawn_interval(
			sanguis::duration_second(
				30.f
			)
		),
		sanguis::server::waves::spawns_per_wave(
			3u
		),
		sanguis::enemy_type::wolf_black
	)(
		boost::cref(
			diff_clock_
		),
		boost::ref(
			random_generator_
		),
		sanguis::server::waves::delay(
			sanguis::duration_second(
				130.f
			)
		),
		sanguis::server::waves::spawn_interval(
			sanguis::duration_second(
				80.f
			)
		),
		sanguis::server::waves::spawns_per_wave(
			6u
		),
		sanguis::enemy_type::spider
	)(
		boost::cref(
			diff_clock_
		),
		boost::ref(
			random_generator_
		),
		sanguis::server::waves::delay(
			sanguis::duration_second(
				180.f
			)
		),
		sanguis::server::waves::spawn_interval(
			sanguis::duration_second(
				120.f
			)
		),
		sanguis::server::waves::spawns_per_wave(
			3u
		),
		sanguis::enemy_type::skeleton
	);
}
