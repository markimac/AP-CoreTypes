srcs = [
    'ara/core/exception.cpp',
    'ara/core/core_error_domain.cpp'
]

ap_coretypes_lib = library('ap-coretypes',
    srcs,
    include_directories : inc_dirs,
    install: true)

ap_coretypes_dep = declare_dependency(
    version: meson.project_version(),
    link_with: ap_coretypes_lib,
    include_directories: inc_dirs
)
