#ifndef SANGUIS_CLIENT_LOAD_MODEL_COLLECTION_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_COLLECTION_HPP_INCLUDED

#include <sanguis/client/load/model/collection_fwd.hpp>
#include <sanguis/client/load/model/object_fwd.hpp>
#include <sanguis/client/load/resource/context_fwd.hpp>
#include <fcppt/string.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
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
	sanguis::client::load::model::object const &
	operator[](
		fcppt::string const &
	) const;

	explicit
	collection(
		sanguis::client::load::resource::context const &
	);

	~collection();
private:
	sanguis::client::load::resource::context const &ctx_;

	typedef boost::ptr_map<
		fcppt::string,
		sanguis::client::load::model::object
	> model_map;

	mutable model_map models_;
};

}
}
}
}

#endif
