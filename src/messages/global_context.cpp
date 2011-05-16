#include "global_context.hpp"
#include "serialization/context.hpp"

sanguis::messages::serialization::context &
sanguis::messages::global_context()
{
	static serialization::context ctx;

	return ctx;
}
