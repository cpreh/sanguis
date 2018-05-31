#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_EXCEPTION_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_EXCEPTION_HPP_INCLUDED

#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/information_fwd.hpp>


namespace sanguis
{
namespace tools
{
namespace libmergeimage
{

class exception
:
	public fcppt::exception
{
public:
	explicit
	exception(
		fcppt::string &&
	);

	explicit
	exception(
		fcppt::assert_::information const &
	);
};

}
}
}

#endif
