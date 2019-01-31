#ifndef CONTROLLERIMPL_H
#define CONTROLLERIMPL_H

#include <memory>
#include "interfaces/IController.h"
#include "interfaces/IProcess.h"
#include "interfaces/IViewer.h"

namespace controller
{
    class ControllerImpl : public interfaces::IController
    {
    public:
        ControllerImpl(std::unique_ptr<interfaces::IViewer> viewer,
                       std::unique_ptr<interfaces::IProcess> processModel);
        virtual ~ControllerImpl() = default;
        virtual void show();

    public slots:
        virtual void catchCompressionAction();
        virtual void catchDecompressionAction();

    private:
        std::unique_ptr<interfaces::IViewer> m_Viewer;
        std::unique_ptr<interfaces::IProcess> m_ProcessModel;
    };
}

#endif // CONTROLLERIMPL_H
