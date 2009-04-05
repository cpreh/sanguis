#ifndef SANGUIS_NET_DETAIL_OUTPUT_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_DETAIL_OUTPUT_BUFFER_HPP_INCLUDED

#include "../data_type.hpp"
#include <sge/container/raw_vector_decl.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace net
{
namespace detail
{

class output_buffer
{
	SGE_NONCOPYABLE(output_buffer)
public:
	output_buffer();
	~output_buffer();

	void push_back(
		data_type const &);

	// extracts "bytes" bytes from the current string and returns the bytes to remain
	void erase(
		data_type::size_type);

	bool characters_left() const;
	data_type const &buffer() const;
private:
	data_type current, appendix;
};
}
}
}

#endif
