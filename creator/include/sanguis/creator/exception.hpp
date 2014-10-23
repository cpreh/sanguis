#ifndef SANGUIS_CREATOR_EXCEPTION_HPP_INCLUDED
#define SANGUIS_CREATOR_EXCEPTION_HPP_INCLUDED

#include <sanguis/creator/symbol.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/symbol/class.hpp>


namespace sanguis
{
namespace creator
{

class FCPPT_SYMBOL_CLASS exception
:
	public fcppt::exception
{
public:
	SANGUIS_CREATOR_SYMBOL
	explicit
	exception(
		fcppt::string const &
	);

	SANGUIS_CREATOR_SYMBOL
	~exception() throw()
	override;
};

}
}

#endif
