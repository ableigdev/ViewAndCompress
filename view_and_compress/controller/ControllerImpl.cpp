#include <QMessageBox>
#include "ControllerImpl.h"
#include "draco_implementation/DracoCompressAction.h"
#include "draco_implementation/DracoDecompressAction.h"

controller::ControllerImpl::ControllerImpl(
        std::unique_ptr<interfaces::IViewer> viewer,
        std::unique_ptr<interfaces::IProcess> processModel)
    : m_Viewer(std::move(viewer)),
      m_ProcessModel(std::move(processModel)),
      m_ProcessAction(nullptr)
{
    connect(m_Viewer.get(), &interfaces::IViewer::doCompress, this, &ControllerImpl::catchCompressionAction);
    connect(m_Viewer.get(), &interfaces::IViewer::doDecompress, this, &ControllerImpl::catchDecompressionAction);
}

void controller::ControllerImpl::show()
{
    m_Viewer->show();
}

void controller::ControllerImpl::catchCompressionAction()
{
    m_ProcessAction.reset(new draco_impl::DracoCompressAction);
    helpDoAction();
}

void controller::ControllerImpl::catchDecompressionAction()
{
    m_ProcessAction.reset(new draco_impl::DracoDecompressAction);
    helpDoAction();
}

void controller::ControllerImpl::helpDoAction()
{
    m_ProcessModel->setCompressionLevel(m_Viewer->getCompressionLevel());
    m_ProcessModel->setQuantizationBits(m_Viewer->getQuantizationBits());
    m_ProcessModel->setPathToSourceFile(m_Viewer->getPathToSourceFile());
    m_ProcessModel->setPathToOutputFile(m_Viewer->getPathToOutputFile());
    try
    {
        auto message = m_ProcessModel->doProcessAction(m_ProcessAction.get());
        m_Viewer->message(message);
    }
    catch(const std::invalid_argument& e)
    {
        QMessageBox::critical(m_Viewer.get(), "Error!", e.what());
    }
    catch(const std::out_of_range& e)
    {
        QMessageBox::critical(m_Viewer.get(), "Error!", e.what());
    }
    catch(const std::runtime_error& e)
    {
        QMessageBox::critical(m_Viewer.get(), "Error!", e.what());
    }
}
