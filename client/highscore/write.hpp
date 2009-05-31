#ifndef SANGUIS_CLIENT_HIGHSCORE_WRITE_HPP_INCLUDED
#define SANGUIS_CLIENT_HIGHSCORE_WRITE_HPP_INCLUDED

#include "table.hpp"
#include <sge/ostream.hpp>

namespace sanguis
{
namespace client
{
namespace highscore
{
void write(
	sge::ostream &,
	table const &);
}
}
}

#endif // SANGUIS_CLIENT_HIGHSCORE_WRITE_HPP_INCLUDED
