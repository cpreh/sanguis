#ifndef SANGUIS_NET_DETAIL_CONNECTION_HPP_INCLUDED
#define SANGUIS_NET_DETAIL_CONNECTION_HPP_INCLUDED

#include "output_buffer_decl.hpp"
#include "../data_type.hpp"
#include "../id_type.hpp"
#include <sge/noncopyable.hpp>
#include <boost/tr1/array.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace sanguis
{
namespace net
{
namespace detail
{

class connection {
	SGE_NONCOPYABLE(connection)
public:
	// typedefs
	typedef std::tr1::array<
		data_type::value_type,
		4096> static_buffer_type;

	connection(
		id_type,
		boost::asio::io_service &);

	typedef output_buffer<data_type::value_type> output_buffer_type;

	id_type const id_;
	boost::asio::ip::tcp::socket socket_;
	static_buffer_type new_data_;
	output_buffer_type output_;
	bool connected_,sending_;

};

}
}
}

#endif
