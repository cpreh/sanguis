#include <sanguis/io_service_impl.hpp>
#include <alda/net/io_service_wrapper_fwd.hpp>


sanguis::io_service_impl::io_service_impl()
:
	io_service_(),
	wrapper_(
		io_service_
	)
{
}

sanguis::io_service_impl::~io_service_impl()
= default;

alda::net::io_service_wrapper const &
sanguis::io_service_impl::get() const
{
	return
		wrapper_;
}
