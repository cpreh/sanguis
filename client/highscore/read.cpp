#include "read.hpp"
#include <sge/assign/make_container.hpp>

sanguis::client::highscore::table const sanguis::client::highscore::read(
	sge::istream &)
{
	table t;
	t.push_back(
		entry(
			sge::assign::make_container<name_container>("Phillemann")("Freundlich"),
			31337));
	t.push_back(
		entry(
			sge::assign::make_container<name_container>("nille"),
			1337));
	return t;
}
