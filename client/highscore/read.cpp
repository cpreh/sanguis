#include "read.hpp"
#include <sge/assign/make_container.hpp>
#include <sge/text.hpp>

sanguis::client::highscore::table const sanguis::client::highscore::read(
	sge::istream &)
{
	table t;
	t.push_back(
		entry(
			sge::assign::make_container<name_container>(SGE_TEXT("Phillemann"))(SGE_TEXT("Freundlich")),
			31337));
	t.push_back(
		entry(
			sge::assign::make_container<name_container>(SGE_TEXT("nille")),
			1337));
	return t;
}
