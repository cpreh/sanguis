#ifndef SANGUIS_CLIENT_LOAD_MODEL_COLLECTION_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_COLLECTION_HPP_INCLUDED

#include <sanguis/client/load/model/collection_fwd.hpp>
#include <sanguis/client/load/model/object_fwd.hpp>
#include <sanguis/client/load/resource/context_fwd.hpp>
#include <sanguis/load/model/path.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
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
		sanguis::load::model::path const &
	) const;

	collection(
		fcppt::log::context_reference,
		sanguis::client::load::resource::context const &
	);

	~collection();
private:
	mutable fcppt::log::object log_;

	sanguis::client::load::resource::context const &resources_;

	typedef
	fcppt::unique_ptr<
		sanguis::client::load::model::object
	>
	model_unique_ptr;

	typedef
	std::map<
		sanguis::load::model::path,
		model_unique_ptr
	>
	model_map;

	mutable model_map models_;
};

}
}
}
}

#endif
