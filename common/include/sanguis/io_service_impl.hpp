#ifndef SANGUIS_IO_SERVICE_IMPL_HPP_INCLUDED
#define SANGUIS_IO_SERVICE_IMPL_HPP_INCLUDED

#include <sanguis/io_service_impl_fwd.hpp>
#include <alda/net/io_service_wrapper.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_service.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{

class io_service_impl
{
	FCPPT_NONMOVABLE(
		io_service_impl
	);
public:
	io_service_impl();

	~io_service_impl();

	[[nodiscard]]
	alda::net::io_service_wrapper const &
	get() const;
private:
	boost::asio::io_service io_service_;

	alda::net::io_service_wrapper const wrapper_;
};

}

#endif
