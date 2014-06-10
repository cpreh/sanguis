#ifndef SANGUIS_MODEL_EXCEPTION_HPP_INCLUDED
#define SANGUIS_MODEL_EXCEPTION_HPP_INCLUDED

#include <sanguis/model/symbol.hpp>
#include <fcppt/class_symbol.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace model
{

class FCPPT_CLASS_SYMBOL exception
:
	public fcppt::exception
{
public:
	SANGUIS_MODEL_SYMBOL
	explicit
	exception(
		fcppt::string const &
	);

	SANGUIS_MODEL_SYMBOL
	~exception() throw()
	override;
};

}
}

#endif
