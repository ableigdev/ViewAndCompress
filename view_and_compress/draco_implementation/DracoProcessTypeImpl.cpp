#include <stdexcept>
#include "DracoProcessTypeImpl.h"

draco_impl::DracoProcessTypeImpl::DracoProcessTypeImpl()
    : m_CompressionLevel(7),
      m_QuantizationBits(14)
{

}

void draco_impl::DracoProcessTypeImpl::setCompressionLevel(int level)
{
    if (level < 1 || level > 10)
    {
        throw std::out_of_range("Out of range in the setting of the compression level");
    }
    m_CompressionLevel = level;
}

void draco_impl::DracoProcessTypeImpl::setQuantizationBits(int quantizationBits)
{
    if (quantizationBits < 1 || quantizationBits > 30)
    {
        throw std::out_of_range("Out of range in the setting of the quantization bits");
    }
    m_QuantizationBits = quantizationBits;
}

void draco_impl::DracoProcessTypeImpl::setPathToSourceFile(const std::string& path)
{
    if (path.empty())
    {
        throw std::invalid_argument("The path to the source file is empty");
    }
    m_PathToSourceFile = path;
}

void draco_impl::DracoProcessTypeImpl::setPathToOutputFile(const std::string& path)
{
    if (path.empty())
    {
        throw std::invalid_argument("The path to the output file is empty");
    }
    m_PathToOutputFile = path;
}

std::string draco_impl::DracoProcessTypeImpl::doProcessAction(interfaces::IProcessAction* processAction)
{
    if (processAction == nullptr)
    {
        throw std::invalid_argument("The pointer of the process action is null");
    }
    processAction->setCompressionLevel(m_CompressionLevel);
    processAction->setQuantizationBits(m_QuantizationBits);
    processAction->setPathToSourceFile(m_PathToSourceFile);
    processAction->setPathToOutputFile(m_PathToOutputFile);

    return processAction->doAction();
}
