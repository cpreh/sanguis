#ifndef SANGUIS_MAIN_OBJECT_HPP_INCLUDED
#define SANGUIS_MAIN_OBJECT_HPP_INCLUDED

#include <sanguis/main_object_fwd.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{

class main_object
{
	FCPPT_NONCOPYABLE(
		main_object
	);
protected:
	main_object();
public:
	virtual
	~main_object() = 0;

	virtual
	awl::main::exit_code const
	run() = 0;
};

}

#endif
