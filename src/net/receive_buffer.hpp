#ifndef SANGUIS_NET_RECEIVE_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_RECEIVE_BUFFER_HPP_INCLUDED

#include "receive_buffer_fwd.hpp"
#include "receive_buffer_part_fwd.hpp"
#include "value_type.hpp"
#include <fcppt/container/raw_vector_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/join.hpp>

namespace sanguis
{
namespace net
{

class receive_buffer
{
	FCPPT_NONCOPYABLE(
		receive_buffer
	);

	typedef fcppt::container::raw_vector<
		net::value_type
	> impl_type;
public:
	typedef impl_type::size_type size_type;

	typedef net::value_type *pointer;

	typedef net::value_type const *const_pointer;

	explicit receive_buffer(
		size_type
	);

	~receive_buffer();

	// in what part can we receive next?
	net::receive_buffer_part const
	next_receive_part();

	// tell the buffer how much was actually read
	void
	bytes_received(
		size_type
	);

	typedef boost::iterator_range<
		const_pointer	
	> iterator_range;

	typedef boost::joined_range<
		iterator_range const,
		iterator_range const
	> joined_range;

	// the range that can be read
	joined_range const
	range() const;

	// remove already processed data
	void
	erase(
		size_type
	);

	size_type
	read_size() const;

	size_type
	capacity() const;
private:
	impl_type impl_;

	pointer
		begin_,
		end_;
};

}
}

#endif
