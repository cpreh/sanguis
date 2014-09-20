#include <sanguis/log_stream.hpp>
#include <fcppt/io/clog.hpp>
#include <fcppt/io/ostream.hpp>


fcppt::io::ostream &
sanguis::log_stream()
{
	return
		fcppt::io::clog();
}
