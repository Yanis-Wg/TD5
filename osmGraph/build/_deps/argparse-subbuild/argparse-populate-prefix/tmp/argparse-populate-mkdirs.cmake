# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/ynaru/Documents/IMAC/C++/S2/TD7/osmGraph/build/_deps/argparse-src")
  file(MAKE_DIRECTORY "C:/Users/ynaru/Documents/IMAC/C++/S2/TD7/osmGraph/build/_deps/argparse-src")
endif()
file(MAKE_DIRECTORY
  "C:/Users/ynaru/Documents/IMAC/C++/S2/TD7/osmGraph/build/_deps/argparse-build"
  "C:/Users/ynaru/Documents/IMAC/C++/S2/TD7/osmGraph/build/_deps/argparse-subbuild/argparse-populate-prefix"
  "C:/Users/ynaru/Documents/IMAC/C++/S2/TD7/osmGraph/build/_deps/argparse-subbuild/argparse-populate-prefix/tmp"
  "C:/Users/ynaru/Documents/IMAC/C++/S2/TD7/osmGraph/build/_deps/argparse-subbuild/argparse-populate-prefix/src/argparse-populate-stamp"
  "C:/Users/ynaru/Documents/IMAC/C++/S2/TD7/osmGraph/build/_deps/argparse-subbuild/argparse-populate-prefix/src"
  "C:/Users/ynaru/Documents/IMAC/C++/S2/TD7/osmGraph/build/_deps/argparse-subbuild/argparse-populate-prefix/src/argparse-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/ynaru/Documents/IMAC/C++/S2/TD7/osmGraph/build/_deps/argparse-subbuild/argparse-populate-prefix/src/argparse-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/ynaru/Documents/IMAC/C++/S2/TD7/osmGraph/build/_deps/argparse-subbuild/argparse-populate-prefix/src/argparse-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
