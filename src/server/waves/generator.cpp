#include <sanguis/server/waves/generator.hpp>
#include <sanguis/server/waves/infinite.hpp>
#include <sanguis/server/waves/single.hpp>
#include <sanguis/server/waves/make.hpp>
#include <sanguis/server/waves/convert_enemy_name.hpp>
#include <sanguis/server/console.hpp>
#include <sanguis/server/player_id_from_args.hpp>
#include <sge/font/text/to_fcppt_string.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/font/text/string.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/assign/ptr_list_inserter.hpp>
#include <fcppt/config/external_end.hpp>

#include <sanguis/server/log.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/extract_from_string_exn.hpp>

// NOTE: be careful when we move this class because
// it should not register the functions more than once

sanguis::server::waves::generator::generator(
	sanguis::diff_clock const &_diff_clock,
	server::console &_console
)
:
	diff_clock_(_diff_clock),
	console_(_console),
	spawn_connection_(
		console_.insert(
			FCPPT_TEXT("spawn"),
			std::tr1::bind(
				&generator::spawn,
				this,
				std::tr1::placeholders::_1
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
		wave_list::iterator it = waves_.begin();
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
		&& _args[1] == SGE_FONT_TEXT_LIT("all")
	)
	{
		spawn_all();

		return;
	}

	if(
		_args.size() != 4u && _args.size() != 5u
	)
	{
		console_.print_line(
			server::player_id_from_args(
				_args
			),
			FCPPT_TEXT("Invalid parameter count for spawn command.")
		);

		return;
	}

	sge::font::text::string const action(
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
		action == SGE_FONT_TEXT_LIT("wave")
	)
		for(
			unsigned i = 0;
			i < count;
			++i
		)
			fcppt::container::ptr::push_back_unique_ptr(
				waves_,
				waves::make(
					diff_clock_,
					sge::font::text::to_fcppt_string(
						_args[2]
					)
				)
			);
	else if(
		action == SGE_FONT_TEXT_LIT("enemy")
	)
		for(
			unsigned i = 0;
			i < count;
			++i
		)
			fcppt::container::ptr::push_back_unique_ptr(
				waves_,
				fcppt::make_unique_ptr<
					waves::single
				>(
					fcppt::cref(
						diff_clock_
					),
					convert_enemy_name(
						sge::font::text::to_fcppt_string(
							_args[2]
						)
					)
				)
			);
	else
	{
		console_.print_line(
			server::player_id_from_args(
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
		server::player_id_from_args(
			_args
		),
		error.string()
	);
}

void
sanguis::server::waves::generator::spawn_all()
{
	// TODO: somehow put this in a configuration file!
	boost::assign::ptr_push_back<waves::infinite>(waves_)
	(
		fcppt::cref(
			diff_clock_
		),
		delay(60),
		spawn_interval(40),
		spawns_per_wave(5),
		enemy_type::spider
	)(
		fcppt::cref(
			diff_clock_
		),
		delay(0),
		spawn_interval(9),
		spawns_per_wave(15),
		enemy_type::maggot
	)(
		fcppt::cref(
			diff_clock_
		),
		delay(50),
		spawn_interval(20),
		spawns_per_wave(10),
		enemy_type::maggot
	)(
		fcppt::cref(
			diff_clock_
		),
		delay(0),
		spawn_interval(30),
		spawns_per_wave(8),
		enemy_type::zombie01
	)(
		fcppt::cref(
			diff_clock_
		),
		delay(0),
		spawn_interval(30),
		spawns_per_wave(8),
		enemy_type::zombie01
	)(
		fcppt::cref(
			diff_clock_
		),
		delay(90),
		spawn_interval(60),
		spawns_per_wave(7),
		enemy_type::zombie00
	)(
		fcppt::cref(
			diff_clock_
		),
		delay(45),
		spawn_interval(30),
		spawns_per_wave(3),
		enemy_type::wolf_brown
	)(
		fcppt::cref(
			diff_clock_
		),
		delay(80),
		spawn_interval(30),
		spawns_per_wave(3),
		enemy_type::wolf_white
	)(
		fcppt::cref(
			diff_clock_
		),
		delay(120),
		spawn_interval(30),
		spawns_per_wave(3),
		enemy_type::wolf_black
	)(
		fcppt::cref(
			diff_clock_
		),
		delay(130),
		spawn_interval(80),
		spawns_per_wave(6),
		enemy_type::spider
	)(
		fcppt::cref(
			diff_clock_
		),
		delay(180),
		spawn_interval(120),
		spawns_per_wave(3),
		enemy_type::skeleton
	);
}
