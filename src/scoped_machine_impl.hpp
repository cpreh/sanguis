#ifndef SANGUIS_SCOPED_MACHINE_IMPL_HPP_INCLUDED
#define SANGUIS_SCOPED_MACHINE_IMPL_HPP_INCLUDED

#include "scoped_machine.hpp"

template<
	typename Machine
>
sanguis::scoped_machine<Machine>::scoped_machine(
	Machine &_machine
)
:
	machine_(_machine)
{
	machine_.initiate();
}

template<
	typename Machine
>
sanguis::scoped_machine<Machine>::~scoped_machine()
{
	machine_.terminate();
}

#endif
