#include "receive_buffer.hpp"
#include "receive_buffer_part.hpp"
#include <fcppt/container/raw_vector_impl.hpp>
#include <cstddef>

sanguis::net::receive_buffer::receive_buffer(
	size_type const _size
)
:
	impl_(_size),
	begin_(impl_.data()),
	end_(begin_)
{
}

sanguis::net::receive_buffer::~receive_buffer()
{
}

sanguis::net::receive_buffer_part const
sanguis::net::receive_buffer::next_receive_part()
{
	return
		begin_ <= end_
		?
			net::receive_buffer_part(
				end_,
				impl_.data_end()
			)
		:
			net::receive_buffer_part(
				end_,
				begin_
			);
}

void
sanguis::net::receive_buffer::bytes_received(
	size_type const _size
)
{
	end_ += _size;	

	if(
		end_ == impl_.end()
	)
		end_ = impl_.begin();
}

sanguis::net::receive_buffer::joined_range const
sanguis::net::receive_buffer::range() const
{
	return
		begin_ <= end_
		?
			receive_buffer::joined_range(
				receive_buffer::iterator_range(
					static_cast<
						const_pointer
					>(
						begin_
					),
					static_cast<
						const_pointer
					>(
						end_
					)
				),
				receive_buffer::iterator_range()
			)
		:
			receive_buffer::joined_range(
				receive_buffer::iterator_range(
					static_cast<
						const_pointer
					>(
						begin_
					),
					impl_.data_end()
				),
				receive_buffer::iterator_range(
					impl_.data(),
					static_cast<
						const_pointer
					>(
						end_
					)
				)
			);
}

void
sanguis::net::receive_buffer::erase(
	size_type const _size
)
{
	begin_ =
		impl_.data()
		+
		(
			(
				begin_
				-
				impl_.data()
				+ 
				static_cast<
					std::ptrdiff_t
				>(
					_size
				)
			)
			%
			static_cast<
				std::ptrdiff_t
			>(
				impl_.size()
			)
		);
}


sanguis::net::receive_buffer::size_type
sanguis::net::receive_buffer::read_size() const
{
	return
		static_cast<
			size_type
		>(
			range().size()
		);
}
