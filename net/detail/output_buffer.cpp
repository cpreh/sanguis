#include "output_buffer.hpp"
#include <sge/container/raw_vector_impl.hpp>
#include <sge/algorithm/append.hpp>

sanguis::net::detail::output_buffer::output_buffer()
{}

sanguis::net::detail::output_buffer::~output_buffer()
{}

void sanguis::net::detail::output_buffer::clear()
{
	current.clear();
	appendix.clear();
}

void sanguis::net::detail::output_buffer::push_back(
	data_type const &s)
{
	if (current.empty())
		current = s;
	else
		sge::algorithm::append(
			appendix,
			s
		);
}

void sanguis::net::detail::output_buffer::erase(
	data_type::size_type const bytes)
{
	current.erase(
		current.begin(),
		current.begin() + bytes
	);

	sge::algorithm::append(
		current,
		appendix
	);

	appendix.clear();
}

bool sanguis::net::detail::output_buffer::characters_left() const 
{ 
	return !current.empty(); 
}

sanguis::net::data_type const &
sanguis::net::detail::output_buffer::buffer() const 
{ 
	return current; 
}
