#ifndef SANGUIS_LOAD_PARTICLE_COLLECTION_HPP_INCLUDED
#define SANGUIS_LOAD_PARTICLE_COLLECTION_HPP_INCLUDED

#include "../../particle_type.hpp"
#include <sge/filesystem/path.hpp>
#include <sge/noncopyable.hpp>
#include <boost/ptr_container/ptr_map.hpp>

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

class collection {
	SGE_NONCOPYABLE(collection)
public:
	animations const &
	operator[](
		particle_type::type) const;
	
	collection(
		sge::filesystem::path const &,
		resource::context const &);
	~collection();

	void preload() const;
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
