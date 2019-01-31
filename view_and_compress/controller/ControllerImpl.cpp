#include "ControllerImpl.h"

controller::ControllerImpl::ControllerImpl(
        std::unique_ptr<interfaces::IViewer> viewer,
        std::unique_ptr<interfaces::IProcess> processModel)
    : m_Viewer(std::move(viewer)),
      m_ProcessModel(std::move(processModel))
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

}

void controller::ControllerImpl::catchDecompressionAction()
{

}
