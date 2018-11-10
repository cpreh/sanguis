#ifndef SANGUIS_CLIENT_OBJECT_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_OBJECT_BASE_HPP_INCLUDED

#include <sanguis/client/object_base_fwd.hpp>
#include <sanguis/client/symbol.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/symbol/class.hpp>


namespace sanguis
{
namespace client
{

class FCPPT_SYMBOL_CLASS object_base
{
	FCPPT_NONCOPYABLE(
		object_base
	);
protected:
	object_base();
public:
	SANGUIS_CLIENT_SYMBOL
	virtual
	~object_base();

	virtual
	awl::main::exit_code
	run() = 0;
};

}
}

#endif
