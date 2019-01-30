#ifndef DRACOPROCESSFACTORY_H
#define DRACOPROCESSFACTORY_H

#include "interfaces/IProcessFactory.h"

namespace draco_impl
{
    class DracoProcessFactory : public interfaces::IProcessFactory
    {
    public:
        DracoProcessFactory() = default;
        virtual ~DracoProcessFactory() = default;
        virtual interfaces::IProcess* createProcess();
    };
}

#endif // DRACOPROCESSFACTORY_H
