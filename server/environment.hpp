#ifndef SANGUIS_SERVER_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_HPP_INCLUDED

#include "send_callback.hpp"
#include "insert_callback.hpp"
#include "exp_callback.hpp"

namespace sanguis
{
namespace server
{
struct environment
{
	send_callback send;
	insert_callback insert;
	exp_callback exp;

	environment(const send_callback &,const insert_callback &,const exp_callback &);
};
}
}

#endif
