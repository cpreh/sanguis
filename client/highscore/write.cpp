#include "write.hpp"
#include <sge/text.hpp>
#include <boost/next_prior.hpp>
#include <ostream>

void
sanguis::client::highscore::write(
	sge::ostream &s,
	table const &t)
{
	s << SGE_TEXT("{ \"entries\": [");

	for(
		table::const_iterator it(
			t.begin()
		);
		it != t.end();
		++it
	)
	{
		s << SGE_TEXT("{ \"names\": [");

		name_container const &names(
			it->names()
		);

		for(
			name_container::const_iterator nit(
				names.begin()
			);
			nit != names.end();
			++nit
		)
		{
			s
				<< SGE_TEXT('"')
				<< *nit
				<< SGE_TEXT('"');

			if(boost::next(nit) != names.end())
				s << SGE_TEXT(',');
		}

		s
			<< SGE_TEXT("], score : ")
			<< it->score()
			<< SGE_TEXT('}');

		s << SGE_TEXT('}');

		if(boost::next(it) != t.end())
			s << SGE_TEXT(',');
	}

	s << SGE_TEXT("]}");
}
