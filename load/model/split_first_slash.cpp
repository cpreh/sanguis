#include "split_first_slash.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>

sanguis::load::model::split_pair const
sanguis::load::model::split_first_slash(
	sge::string const &s)
{
	sge::string::size_type const sz(
		s.find(
			SGE_TEXT('/')
		)
	);

	if(sz == sge::string::npos)
		throw exception(
			SGE_TEXT("No / found in ")
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
