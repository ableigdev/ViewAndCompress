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

void draco_impl::DracoProcessImpl::setProcessAction(interfaces::IProcessAction* processAction)
{
    m_DracoProcessTypeImpl->setProcessAction(processAction);
}
