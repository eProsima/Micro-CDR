# Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#
# Autoconf script microCDR
#

#
# Define variables for the microCDR version number.
#
m4_define([version_major],[1])
m4_define([version_minor],[0])
m4_define([version_micro],[6])

AC_INIT([microcdr], [version_major.version_minor.version_micro], [support@eprosima.com], [eProsima microCDR], [http://eprosima.com/])
CONFIG_ARGS="$*"
AC_SUBST(CONFIG_ARGS)

#Minimum autoconf version we require.
AC_PREREQ([2.59])

AM_INIT_AUTOMAKE([1.10 no-define foreign subdir-objects])

# Makes version available in config.h
AC_DEFINE(MICROCDR_VERSION_MAJOR, version_major, [microcdr version major])
AC_DEFINE(MICROCDR_VERSION_MINOR, version_minor, [microcdr version minor])
AC_DEFINE(MICROCDR_VERSION_MICRO, version_micro, [microcdr version micro])

# Check stdcxx
AX_CXX_COMPILE_STDCXX_11(,optional)
AS_IF([test $HAVE_CXX11 = 1],
      [AC_DEFINE(HAVE_CXX0X, 1, ["Define if g++ supports C++0x features. "])],
      [AX_CXX_COMPILE_STDCXX_0X()])


# Check endianess
AC_C_BIGENDIAN(
  AC_DEFINE(__BIG_ENDIAN__, 1, [machine is bigendian]),
  AC_DEFINE(__BIG_ENDIAN__, 0, [machine is littleendian]),
  AC_MSG_ERROR(unknown endianess),
  AC_MSG_ERROR(universial endianess not supported)
)

# Check for libraries used in the main build process
AC_PROG_CXX
AC_PROG_CPP

# Init libtool
AC_CONFIG_MACRO_DIR([m4])
LT_INIT

AC_CONFIG_HEADERS([include/microcdr/config.h:include/microcdr/config.h.in])
AC_CONFIG_FILES([Makefile
                 include/Makefile
                 src/c/Makefile])

AC_OUTPUT
