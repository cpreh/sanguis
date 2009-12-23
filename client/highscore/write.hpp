#ifndef SANGUIS_CLIENT_HIGHSCORE_WRITE_HPP_INCLUDED
#define SANGUIS_CLIENT_HIGHSCORE_WRITE_HPP_INCLUDED

#include "table.hpp"
#include <fcppt/io/ostream.hpp>

namespace sanguis
{
namespace client
{
namespace highscore
{
void write(
	fcppt::io::ostream &,
	table const &
);
}
}
}

#endif // SANGUIS_CLIENT_HIGHSCORE_WRITE_HPP_INCLUDED
