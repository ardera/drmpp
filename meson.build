# SPDX-FileCopyrightText: (c) 2024 The drmpp Contributors
# SPDX-License-Identifier: Apache-2.0

project('drmpp', ['c', 'cpp'],
        version : '0.1.0',
        meson_version : '>= 0.55.0',
        license : 'Apache-2.0',
        default_options : ['cpp_std=c++17']
)

#########################
# Version Variable
#########################
version_array = meson.project_version().split('.')
drmpp_major_version = version_array[0].to_int()
drmpp_minor_version = version_array[1].to_int()
drmpp_micro_version = version_array[2].to_int()

drmpp_api_version_string = '@0@'.format(drmpp_major_version)

drmpp_interface_age = drmpp_micro_version
drmpp_binary_age = 100 * drmpp_minor_version + drmpp_micro_version

# Maintain compatibility with libtool versioning
drmpp_soversion = 0
current = drmpp_binary_age - drmpp_interface_age
revision = drmpp_interface_age
drmpp_libversion = '@0@.@1@.@2@'.format(drmpp_soversion, current, revision)

drmpp_name = 'drmpp-' + drmpp_api_version_string
drmpp_full_name = 'libdrmpp-' + drmpp_api_version_string

#########################
# Package Config
#########################
prefix = get_option('prefix')
libdir = join_paths(prefix, get_option('libdir'))
devenv = environment()

pkgname = meson.project_name()
pkglibdir = join_paths(libdir, pkgname)

#########################
# Compiler
#########################
cpp = meson.get_compiler('cpp')
add_project_arguments(
    cpp.get_supported_arguments(['-Wno-unused-parameter', '-Wno-missing-field-initializers', ]),
    language : ['cpp'],
)

#########################
# Config Header
#########################

cdata = configuration_data()
cdata.set_quoted('VERSION', meson.project_version())

config_h = configure_file(
    input : 'config.h.meson',
    output : 'config.h',
    configuration : cdata
)
config_inc = include_directories('.')

#########################
# Source
#########################

subdir('src')

if get_option('examples')
    subdir('examples')
endif

if meson.version().version_compare('>=0.58.0')
    meson.add_devenv(devenv)
endif

install_headers('include/drmpp/drmpp.h')
