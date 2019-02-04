#include "DracoProcessFactory.h"
#include "DracoProcessImpl.h"

interfaces::IProcess* draco_impl::DracoProcessFactory::createProcess()
{
    return new DracoProcessImpl();
}
