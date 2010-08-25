#ifndef SANGUIS_SCOPED_MACHINE_HPP_INCLUDED
#define SANGUIS_SCOPED_MACHINE_HPP_INCLUDED

#include <fcppt/noncopyable.hpp>

namespace sanguis
{

template<
	typename Machine
>
class scoped_machine
{
	FCPPT_NONCOPYABLE(scoped_machine)
public:
	explicit scoped_machine(
		Machine &
	);

	~scoped_machine();
private:
	Machine &machine_;
};

}

#endif
