#ifndef CONTROLLERIMPL_H
#define CONTROLLERIMPL_H

#include <memory>
#include "interfaces/IController.h"
#include "interfaces/IProcess.h"
#include "interfaces/IViewer.h"
#include "interfaces/IProcessAction.h"

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
        void helpDoAction();

    private:
        std::unique_ptr<interfaces::IViewer> m_Viewer;
        std::unique_ptr<interfaces::IProcess> m_ProcessModel;
        std::unique_ptr<interfaces::IProcessAction> m_ProcessAction;
    };
}

#endif // CONTROLLERIMPL_H
