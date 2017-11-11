#ifndef SANGUIS_CLIENT_HEALTH_HPP_INCLUDED
#define SANGUIS_CLIENT_HEALTH_HPP_INCLUDED

#include <sanguis/client/health_value.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace client
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::client::health_value,
	health
);

}
}

#endif
