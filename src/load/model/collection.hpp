#ifndef SANGUIS_LOAD_MODEL_COLLECTION_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_COLLECTION_HPP_INCLUDED

#include "collection_fwd.hpp"
#include "../resource/context_fwd.hpp"
#include "object_fwd.hpp"
#include <fcppt/string.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/thread/thread.hpp>
#include <boost/ptr_container/ptr_map.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class collection
{
	FCPPT_NONCOPYABLE(
		collection
	);
public:
	object const &
	operator[](
		fcppt::string const &
	) const;

	explicit collection(
		resource::context const &
	);

	~collection();
private:
	resource::context const &ctx_;

	typedef boost::ptr_map<
		fcppt::string,
		object
	> model_map;

	mutable model_map models_;

	mutable boost::mutex mutex_;
};

}
}
}

#endif
