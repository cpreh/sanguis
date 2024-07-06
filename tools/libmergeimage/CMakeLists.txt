fcppt_utils_load_source_files(tools/libmergeimage/files.txt SANGUIS_TOOLS_LIBMERGEIMAGE_FILES)

sanguis_add_library(
  tools_libmergeimage
  "${SANGUIS_TOOLS_LIBMERGEIMAGE_FILES}"
  HAS_IMPL_DIR
  DEPS
  ${sanguis_core_TARGET}
  ${sanguis_model_TARGET}
  ${sgeimage_TARGET}
  ${sgeimagecolor_TARGET}
  ${sgeimage2d_TARGET}
  ${fcppt_core_TARGET}
  ${fcppt_filesystem_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})
