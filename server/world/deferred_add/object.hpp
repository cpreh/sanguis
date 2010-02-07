#ifndef SANGUIS_SERVER_WORLD_DEFERRED_ADD_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_DEFERRED_ADD_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "../../entities/auto_ptr.hpp"
#include "../../entities/base_fwd.hpp"
#include "../../entities/insert_parameters.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace world
{
namespace deferred_add
{

class object 
{
	FCPPT_NONCOPYABLE(object)
public:
	explicit object(
		entities::auto_ptr,
		entities::insert_parameters const &
	);
	
	~object();

	entities::base &
	entity();

	entities::auto_ptr
	release_entity();

	entities::insert_parameters const &
	insert_parameters() const;
private:
	entities::auto_ptr entity_;

	entities::insert_parameters const insert_parameters_;
};

}
}
}
}

#endif
