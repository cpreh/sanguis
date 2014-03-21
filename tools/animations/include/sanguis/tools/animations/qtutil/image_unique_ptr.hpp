#ifndef SANGUIS_TOOLS_ANIMATIONS_QTUTIL_IMAGE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_QTUTIL_IMAGE_UNIQUE_PTR_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <QImage>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tools
{
namespace animations
{
namespace qtutil
{

typedef
std::unique_ptr<
	QImage
>
image_unique_ptr;

}
}
}
}

#endif
