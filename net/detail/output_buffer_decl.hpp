#ifndef SANGUIS_NET_DETAIL_OUTPUT_BUFFER_DECL_HPP_INCLUDED
#define SANGUIS_NET_DETAIL_OUTPUT_BUFFER_DECL_HPP_INCLUDED

#include <string>
#include <cstddef>

namespace sanguis
{
namespace net
{
namespace detail
{
template<
	typename Char,
	typename Traits = std::char_traits<Char> >
class output_buffer
{
public:
	typedef std::basic_string<Char,Traits> string;

	void push_back(
		string const &);

	// extracts "bytes" bytes from the current string and returns the bytes to remain
	void erase(
		typename string::size_type);

	bool characters_left() const;
	string const &buffer() const;
private:
	string current,appendix;
};
}
}
}

#endif
