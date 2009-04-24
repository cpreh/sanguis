#ifndef SANGUIS_OUTPUT_BUFFER_HPP_INCLUDED
#define SANGUIS_OUTPUT_BUFFER_HPP_INCLUDED

#include <string>
#include <cstddef>

template< typename Char,typename Traits = std::char_traits<Char> >
struct output_buffer
{
	std::basic_string<Char,Traits> current;
	std::basic_string<Char,Traits> appendix;

	output_buffer &push_back(const std::basic_string<Char,Traits> &s)
	{
		if (current.empty())
			current = s;
		else
			appendix += s;
		
		return *this;
	}

	// extracts "bytes" bytes from the current string and returns the bytes to remain
	output_buffer finished(const std::size_t bytes)
	{
		current = current.substr(bytes)+appendix;
		appendix.clear();
		return *this;
	}

	bool to_send() const { return !current.empty(); }
	const std::basic_string<Char,Traits> &buffer() const { return current; }
};

#endif
