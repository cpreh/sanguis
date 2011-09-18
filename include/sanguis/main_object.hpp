#ifndef SANGUIS_MAIN_OBJECT_HPP_INCLUDED
#define SANGUIS_MAIN_OBJECT_HPP_INCLUDED

#include <sanguis/main_object_fwd.hpp>
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
	virtual ~main_object();

	virtual int
	run() = 0;
};

}

#endif
