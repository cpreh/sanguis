#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_IMAGE_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_IMAGE_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/image_fwd.hpp>
#include <sanguis/tools/libmergeimage/image_store.hpp>
#include <sanguis/tools/libmergeimage/path_count_pair_vector.hpp>
#include <sanguis/tools/libmergeimage/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace tools
{
namespace libmergeimage
{

class image
{
	FCPPT_NONCOPYABLE(
		image
	);
public:
	image(
		sanguis::tools::libmergeimage::path_count_pair_vector &&,
		sanguis::tools::libmergeimage::image_store &&
	);

	image(
		sanguis::tools::libmergeimage::path_count_pair_vector const &,
		sanguis::tools::libmergeimage::image_store &&
	);

	SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL
	image(
		image &&
	);

	SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL
	image &
	operator=(
		image &&
	);

	SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL
	~image();

	SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL
	sanguis::tools::libmergeimage::path_count_pair_vector const &
	paths() const;

	SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL
	sanguis::tools::libmergeimage::image_store const &
	store() const;
private:
	sanguis::tools::libmergeimage::path_count_pair_vector paths_;

	sanguis::tools::libmergeimage::image_store store_;
};

}
}
}

#endif
