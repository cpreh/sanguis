#include "make_send_callback.hpp"
#include "machine.hpp"
#include <fcppt/tr1/functional.hpp>
#include <fcppt/function/object.hpp>

sanguis::server::send_callback const
sanguis::server::make_send_callback(
	server::machine &machine_
)
{
	return
		std::tr1::bind(
			&server::machine::send_to_all,
			&machine_,
			std::tr1::placeholders::_1
		);
}
