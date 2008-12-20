#ifndef SANGUIS_LOAD_RESOURCE_ANIMATIONS_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_ANIMATIONS_HPP_INCLUDED

#include <sge/sprite/animation_series.hpp>
#include <sge/path.hpp>
#include <boost/noncopyable.hpp>

namespace sanguis
{
namespace load
{
namespace resource
{

class animations : boost::noncopyable {
public:
	sge::sprite::animation_series const
	load(
		sge::path const &);
};

}
}
}

#endif
