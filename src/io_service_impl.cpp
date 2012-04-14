#include <sanguis/io_service_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_service.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::io_service_impl::io_service_impl()
:
	io_service_()
{
}

sanguis::io_service_impl::~io_service_impl()
{
}

boost::asio::io_service &
sanguis::io_service_impl::get()
{
	return
		io_service_;
}
