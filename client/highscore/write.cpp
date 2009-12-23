#include "write.hpp"
#include <fcppt/text.hpp>
#include <boost/next_prior.hpp>
#include <ostream>

void
sanguis::client::highscore::write(
	sge::ostream &s,
	table const &t)
{
	s << FCPPT_TEXT("{ \"entries\": [");

	for(
		table::const_iterator it(
			t.begin()
		);
		it != t.end();
		++it
	)
	{
		s << FCPPT_TEXT("{ \"names\": [");

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
				<< FCPPT_TEXT('"')
				<< *nit
				<< FCPPT_TEXT('"');

			if(boost::next(nit) != names.end())
				s << FCPPT_TEXT(',');
		}

		s
			<< FCPPT_TEXT("], score : ")
			<< it->score()
			<< FCPPT_TEXT('}');

		s << FCPPT_TEXT('}');

		if(boost::next(it) != t.end())
			s << FCPPT_TEXT(',');
	}

	s << FCPPT_TEXT("]}");
}
