#ifndef SANGUIS_CLIENT_DRAW2D_SUNLIGHT_TIME_TO_GREGORIAN_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SUNLIGHT_TIME_TO_GREGORIAN_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/date_time/gregorian/greg_date.hpp>
#include <ctime>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sunlight
{

boost::gregorian::date const
time_to_gregorian(
	std::tm const &
);

}
}
}
}

#endif
