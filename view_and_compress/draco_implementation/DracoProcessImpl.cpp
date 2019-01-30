#include "DracoProcessImpl.h"

draco_impl::DracoProcessImpl::DracoProcessImpl()
    : m_DracoProcessTypeImpl(new DracoProcessTypeImpl)
{

}

void draco_impl::DracoProcessImpl::setCompressionLevel(int level)
{
    m_DracoProcessTypeImpl->setCompressionLevel(level);
}

void draco_impl::DracoProcessImpl::setQuantizationBits(int quantizationBits)
{
    m_DracoProcessTypeImpl->setQuantizationBits(quantizationBits);
}

void draco_impl::DracoProcessImpl::setPathToSourceFile(const std::string& path)
{
    m_DracoProcessTypeImpl->setPathToSourceFile(path);
}

void draco_impl::DracoProcessImpl::setPathToOutputFile(const std::string& path)
{
    m_DracoProcessTypeImpl->setPathToOutputFile(path);
}

std::string draco_impl::DracoProcessImpl::doProcessAction(interfaces::IProcessAction* processAction)
{
    return m_DracoProcessTypeImpl->doProcessAction(processAction);
}
