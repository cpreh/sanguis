#include <alda/net/port.hpp>
#include <sanguis/args/server_port.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


alda::net::port const
sanguis::args::server_port(
	boost::program_options::variables_map const &_vm
)
{
	return
		alda::net::port(
			_vm["serverport"].as<
				alda::net::port::value_type
			>()
		);
}
