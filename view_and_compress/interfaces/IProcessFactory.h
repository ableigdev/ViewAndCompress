#ifndef VIEW_AND_COMPRESS_IPROCESSFACTORY_H
#define VIEW_AND_COMPRESS_IPROCESSFACTORY_H

#include "IProcess.h"

namespace interfaces
{
    class IProcessFactory
    {
    public:
        IProcessFactory() = default;
        virtual ~IProcessFactory() = default;
        virtual IProcess* createProcess() = 0;
    };
}

#endif //VIEW_AND_COMPRESS_IPROCESSFACTORY_H
