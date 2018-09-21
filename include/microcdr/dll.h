// Copyright 2017 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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


#ifndef _MICROCDR_DLL_H_
#define _MICROCDR_DLL_H_

#if defined(_WIN32)
#if defined(microcdr_SHARED)
#if defined(microcdr_EXPORTS)
#define MCDLLAPI __declspec( dllexport )
#else
#define MCDLLAPI __declspec( dllimport )
#endif // microcdr_EXPORTS
#else
#define MCDLLAPI
#endif // BUILDING_SHARED_LIBS
#else
#define MCDLLAPI
#endif // _WIN32

#endif // _MICROCDR_DLL_H_
