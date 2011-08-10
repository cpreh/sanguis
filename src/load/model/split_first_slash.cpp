#include "split_first_slash.hpp"
#include "../../exception.hpp"
#include <fcppt/text.hpp>

sanguis::load::model::split_pair const
sanguis::load::model::split_first_slash(
	fcppt::string const &s)
{
	fcppt::string::size_type const sz(
		s.find(
			FCPPT_TEXT('/')
		)
	);

	if(sz == fcppt::string::npos)
		throw exception(
			FCPPT_TEXT("No / found in ")
			+ s
		);

	return split_pair(
		fcppt::string(
			s.substr(
				0,
				sz
			)
		),
		fcppt::string(
			s.substr(
				sz + 1
			)
		)
	);
}
