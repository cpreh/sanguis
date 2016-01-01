#ifndef SANGUIS_CLIENT_LOAD_MODEL_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_OBJECT_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/load/model/object_fwd.hpp>
#include <sanguis/client/load/model/part_fwd.hpp>
#include <sanguis/client/load/model/part_map.hpp>
#include <sanguis/client/load/model/part_result.hpp>
#include <sanguis/client/load/resource/context_fwd.hpp>
#include <sanguis/model/cell_size.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/random/variate_decl.hpp>
#include <fcppt/random/distribution/basic_decl.hpp>
#include <fcppt/random/distribution/parameters/uniform_int_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace model
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef sanguis::client::load::model::part_map::const_iterator const_iterator;

	typedef sanguis::client::load::model::part_map::size_type size_type;

	object(
		boost::filesystem::path const &,
		sanguis::client::load::resource::context const &
	);

	~object();

	sanguis::client::load::model::part const &
	operator[](
		fcppt::string const &
	) const;

	sanguis::client::load::model::part const &
	random_part(
		sanguis::random_generator &
	) const;

	size_type
	size() const;

	const_iterator
	begin() const;

	const_iterator
	end() const;

	sanguis::model::cell_size
	cell_size() const;
private:
	sanguis::client::load::model::part_map const &
	parts() const;

	boost::filesystem::path const path_;

	sanguis::client::load::model::part_result const part_result_;

	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			sanguis::client::load::model::part_map::size_type
		>
	> part_map_distribution;

	typedef fcppt::random::variate<
		sanguis::random_generator,
		part_map_distribution
	> part_rand;

	typedef
	fcppt::optional::object<
		part_rand
	>
	optional_part_rand;

	mutable optional_part_rand random_part_;
};

}
}
}
}

#endif
