#include <QApplication>
#include <QLockFile>
#include <QDir>
#include <QMessageBox>
#include <memory>
#include "interfaces/IProcess.h"
#include "interfaces/IProcessFactory.h"
#include "interfaces/IProcessType.h"
#include "interfaces/IController.h"
#include "interfaces/IViewer.h"
#include "draco_implementation/DracoProcessFactory.h"
#include "draco_implementation/DracoProcessImpl.h"
#include "draco_implementation/DracoProcessTypeImpl.h"
#include "gui/ViewerImpl.h"
#include "controller/ControllerImpl.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLockFile lockFile(QDir::temp().absoluteFilePath("temp.lock"));

    if (!lockFile.tryLock(100))
    {
        QMessageBox message;
        message.setIcon(QMessageBox::Warning);
        message.setText("The application was run.\nYou can run only one instance of the application.");
        message.exec();
        return 1;
    }

    std::unique_ptr<interfaces::IProcessFactory> factory(new draco_impl::DracoProcessFactory);
    std::unique_ptr<interfaces::IProcess> process(factory->createProcess());
    std::unique_ptr<interfaces::IViewer> viewer(new ViewerImpl);
    std::unique_ptr<interfaces::IController> controller(new controller::ControllerImpl(std::move(viewer), std::move(process)));
    controller->show();

    return a.exec();
}
