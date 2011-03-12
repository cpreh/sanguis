#include "log_switcher.hpp"
#include "string_vector.hpp"
#include <sge/log/global.hpp>
#include <sge/exception.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/level_from_string.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/text.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/arithmetic.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <vector>

namespace
{

typedef 
std::pair
<
	fcppt::string,
	fcppt::string
>
string_pair;

typedef
std::vector<
	std::string
> std_string_vector;

sanguis::string_vector const
explode(
	fcppt::string const &e,
	fcppt::string const &seps
)
{
	sanguis::string_vector v;

	boost::algorithm::split(
		v,
		e,
		boost::algorithm::is_any_of(
			seps
		)
	);

	return v;
}

string_pair const
split(
	fcppt::string const &e,
	fcppt::char_type const sep
)
{
	fcppt::string::size_type const p = 
		e.rfind(sep);

	string_pair result;
	
	if (p == fcppt::string::npos)
	{
		result.first = e;
		return result;
	}

	result.first = 
		e.substr(
			static_cast<fcppt::string::size_type>(
				0),
			p);
	
	result.second = 
		e.substr(
			static_cast<fcppt::string::size_type>(
				p+1));
	
	return result;
}

template<
	typename Range
>
fcppt::log::location const 
to_location(
	Range const &r
)
{
	FCPPT_ASSERT(
		!r.empty());
		
	fcppt::log::location l(
		r.front()
	);
	
	std::for_each(
		boost::next(r.begin()),
		r.end(),
		boost::phoenix::ref(l) += boost::phoenix::arg_names::arg1
	);
	
	return 
		l;
}

std::string const
make_enable_name(
	std::string const &_prefix
)
{
	return
		"enable-"
		+ _prefix
		+ "-log";
}

}

sanguis::log_switcher::log_switcher(
	options_callback const &_options_callback,
	fcppt::string const &_prefix,
	fcppt::log::context &_context
)
:
	prefix_(
		fcppt::to_std_string(
			_prefix
		)
	),
	context_(
		_context
	)
{
	_options_callback().add_options()
		(
			::make_enable_name(
				prefix_
			).c_str(),
			boost::program_options::value<
				::std_string_vector
			>(),
			"Path specifications enabling either all log levels or just one (example: foo/bar/baz:debug)"
		);
}

void
sanguis::log_switcher::apply(
	boost::program_options::variables_map const &_vm
)
{
	std::string const option(
		::make_enable_name(
			prefix_
		)
	);

	if (!_vm.count(option))
		return;

	::std_string_vector const specs(
		_vm[
			option
		].as<
			::std_string_vector
		>()
	);
	
	BOOST_FOREACH(
		std::string const &string_part,
		specs
	)
	{
		string_pair const splitted(
			::split(
				fcppt::from_std_string(
					string_part
				),
				FCPPT_TEXT(':')
			)
		);

		sanguis::string_vector const parts(
			::explode(
				splitted.first,
				FCPPT_TEXT("/")
			)
		);

		fcppt::log::location const location(
			to_location(
				parts
			)
		);
		
		fcppt::log::object *const log_object(
			context_.find(
				location
			)
		);

		if (!log_object)
			throw 
				sge::exception(
					FCPPT_TEXT("The specified log context ")
					+ location.string()
					+ FCPPT_TEXT(" wasn't found")
				);
	
		fcppt::log::level::type const level = 
			splitted.second.empty()
			?
				fcppt::log::level::debug
			:	
				fcppt::log::level_from_string(
					splitted.second
				);

		fcppt::log::activate_levels(
			*log_object,
			level
		);
	}
}
