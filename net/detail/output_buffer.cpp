#include "output_buffer.hpp"
#include <sge/container/raw_vector_impl.hpp>

sanguis::net::detail::output_buffer::output_buffer()
{}

sanguis::net::detail::output_buffer::~output_buffer()
{}

void sanguis::net::detail::output_buffer::push_back(
	data_type const &s)
{
	if (current.empty())
		current = s;
	else
		appendix.insert(
			appendix.end(),
			s.begin(),
			s.end()
		);
}

void sanguis::net::detail::output_buffer::erase(
	data_type::size_type const bytes)
{
	current.erase(
		current.begin(),
		current.begin() + bytes
	);

	current.insert(
		current.end(),
		appendix.begin(),
		appendix.end()
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
