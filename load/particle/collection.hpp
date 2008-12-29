#ifndef SANGUIS_LOAD_PARTICLE_COLLECTION_HPP_INCLUDED
#define SANGUIS_LOAD_PARTICLE_COLLECTION_HPP_INCLUDED

#include "../../particle_type.hpp"
#include <sge/path.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/noncopyable.hpp>

namespace sanguis
{
namespace load
{
namespace resource
{
class context;
}
namespace particle
{

class context;
class animations;

class collection : boost::noncopyable {
public:
	animations const &
	operator[](
		particle_type::type) const;
	
	collection(
		sge::path const &,
		resource::context const &);
	~collection();
private:
	typedef boost::ptr_map<
		particle_type::type,
		animations
	> animations_map;

	animations_map animations_;
};

}
}
}

#endif
