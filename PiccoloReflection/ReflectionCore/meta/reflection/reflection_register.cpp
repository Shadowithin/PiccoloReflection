#include <assert.h>

#include "meta/json.h"
#include "meta/reflection/reflection.h"
#include "meta/reflection/reflection_register.h"
#include "meta/serializer/serializer.h"

#include "_generated/reflection/all_reflection.h"
#include "_generated/serializer/all_serializer.ipp"

namespace Piccolo
{
    namespace Reflection
    {
        void TypeMetaRegister::metaUnregister() { TypeMetaRegisterinterface::unregisterAll(); }
    } // namespace Reflection
} // namespace Piccolo
