#ifndef SANGUIS_CLIENT_HIGHSCORE_READ_HPP_INCLUDED
#define SANGUIS_CLIENT_HIGHSCORE_READ_HPP_INCLUDED

#include "table.hpp"
#include <fcppt/io/istream.hpp>

namespace sanguis
{
namespace client
{
namespace highscore
{
table const read(
	fcppt::io::istream &);
}
}
}

#endif // SANGUIS_CLIENT_HIGHSCORE_READ_HPP_INCLUDED
