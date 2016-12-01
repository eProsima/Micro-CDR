// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _NANOCDR_NANOCDR_DLL_H_
#define _NANOCDR_NANOCDR_DLL_H_

#include "config.h"

// normalize macros
#if !defined(NANOCDR_DYN_LINK) && !defined(NANOCDR_STATIC_LINK) \
    && !defined(EPROSIMA_ALL_DYN_LINK) && !defined(EPROSIMA_ALL_STATIC_LINK)
#define NANOCDR_STATIC_LINK
#endif

#if defined(EPROSIMA_ALL_DYN_LINK) && !defined(NANOCDR_DYN_LINK)
#define NANOCDR_DYN_LINK
#endif

#if defined(NANOCDR_DYN_LINK) && defined(NANOCDR_STATIC_LINK)
#error Must not define both NANOCDR_DYN_LINK and NANOCDR_STATIC_LINK
#endif

#if defined(EPROSIMA_ALL_NO_LIB) && !defined(NANOCDR_NO_LIB)
#define NANOCDR_NO_LIB
#endif

// enable dynamic linking
#if defined(_WIN32)
#if defined(EPROSIMA_ALL_DYN_LINK) || defined(NANOCDR_DYN_LINK)
#if defined(NANOCDR_SOURCE)
#define nanocdr_DllAPI __declspec( dllexport )
#else
#define nanocdr_DllAPI __declspec( dllimport )
#endif // NANOCDR_SOURCE
#else
#define nanocdr_DllAPI
#endif
#else
#define nanocdr_DllAPI
#endif // _WIN32

// Auto linking.

#if !defined(NANOCDR_SOURCE) && !defined(EPROSIMA_ALL_NO_LIB) \
    && !defined(NANOCDR_NO_LIB)

// Set properties.
#define EPROSIMA_LIB_NAME nanocdr

#if defined(EPROSIMA_ALL_DYN_LINK) || defined(NANOCDR_DYN_LINK)
#define EPROSIMA_DYN_LINK
#endif

#include "eProsima_auto_link.h"
#endif // auto-linking disabled

#endif // _NANOCDR_NANOCDR_DLL_H_
