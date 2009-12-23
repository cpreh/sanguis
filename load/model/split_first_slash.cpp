#include "split_first_slash.hpp"
#include "../../exception.hpp"
#include <fcppt/text.hpp>

sanguis::load::model::split_pair const
sanguis::load::model::split_first_slash(
	sge::string const &s)
{
	sge::string::size_type const sz(
		s.find(
			FCPPT_TEXT('/')
		)
	);

	if(sz == sge::string::npos)
		throw exception(
			FCPPT_TEXT("No / found in ")
			+ s
		);
	
	return split_pair(
		sge::string(
			s.substr(
				0,
				sz
			)
		),
		sge::string(
			s.substr(
				sz + 1
			)
		)
	);
}
