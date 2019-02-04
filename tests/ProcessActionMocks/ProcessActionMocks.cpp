#include <memory>
#include <QApplication>
#include "gmock/gmock.h"
#include "interfaces/IProcess.h"
#include "interfaces/IProcessAction.h"
#include "interfaces/IProcessFactory.h"
#include "interfaces/IProcessType.h"
#include "interfaces/IController.h"
#include "interfaces/IViewer.h"
#include "draco_implementation/DracoCompressAction.h"
#include "draco_implementation/DracoDecompressAction.h"
#include "draco_implementation/DracoProcessFactory.h"
#include "draco_implementation/DracoProcessImpl.h"
#include "draco_implementation/DracoProcessTypeImpl.h"
#include "controller/ControllerImpl.h"
#include "gui/ViewerImpl.h"

class MockCompressionAction : public interfaces::IProcessAction
{
public:
    MockCompressionAction() = default;
    virtual ~MockCompressionAction() = default;

    MOCK_METHOD1(setCompressionLevel, void(int));
    MOCK_METHOD1(setQuantizationBits, void(int));
    MOCK_METHOD1(setPathToSourceFile, void(const std::string&));
    MOCK_METHOD1(setPathToOutputFile, void(const std::string&));
    MOCK_METHOD0(doAction, std::string());
};

class MockProcess : public interfaces::IProcess
{
public:
    MockProcess() = default;
    virtual ~MockProcess() = default;
    MOCK_METHOD1(setCompressionLevel, void(int));
    MOCK_METHOD1(setQuantizationBits, void(int));
    MOCK_METHOD1(setPathToSourceFile, void(const std::string&));
    MOCK_METHOD1(setPathToOutputFile, void(const std::string&));
    MOCK_METHOD1(doProcessAction, std::string(interfaces::IProcessAction*));
};

class MockViewer : public interfaces::IViewer
{
public:
    MockViewer() = default;
    virtual ~MockViewer() = default;

    MOCK_CONST_METHOD0(getCompressionLevel, int());
    MOCK_CONST_METHOD0(getQuantizationBits, int());
    MOCK_CONST_METHOD0(getPathToSourceFile, std::string());
    MOCK_CONST_METHOD0(getPathToOutputFile, std::string());
    MOCK_METHOD1(message, void(const std::string&));

    void show()
    {
        emit doCompress();
    }
};

TEST(TestProcessAction, MethodsCalls)
{
    std::unique_ptr<interfaces::IProcessFactory> factory(new draco_impl::DracoProcessFactory);
    std::unique_ptr<interfaces::IProcess> process(factory->createProcess());
    auto mockAction = std::make_unique<MockCompressionAction>();

    EXPECT_CALL(*mockAction, setCompressionLevel(::testing::Ge(7))).Times(::testing::AtMost(1));
    EXPECT_CALL(*mockAction, setQuantizationBits(::testing::Ge(14))).Times(::testing::AtMost(1));
    EXPECT_CALL(*mockAction, setPathToSourceFile(::testing::_)).Times(::testing::AtMost(1));
    EXPECT_CALL(*mockAction, setPathToOutputFile(::testing::_)).Times(::testing::AtMost(1));
    EXPECT_CALL(*mockAction, doAction).Times(::testing::AtMost(1)).WillOnce(::testing::Return("Successful compression"));

    EXPECT_EQ(process->doProcessAction(mockAction.get()), "Successful compression");
}

TEST(TestController, ValidCase)
{
    int i = 0;
    QApplication a(i, nullptr);
    auto mockViewer = std::make_unique<MockViewer>();
    auto mockProcess = std::make_unique<MockProcess>();

    EXPECT_CALL(*mockViewer, getCompressionLevel).Times(::testing::AtMost(1)).WillOnce(::testing::Return(7));
    EXPECT_CALL(*mockViewer, getQuantizationBits).Times(::testing::AtMost(1)).WillOnce(::testing::Return(14));
    EXPECT_CALL(*mockViewer, getPathToSourceFile).Times(::testing::AtMost(1)).WillOnce(::testing::Return("path"));
    EXPECT_CALL(*mockViewer, getPathToOutputFile).Times(::testing::AtMost(1)).WillOnce(::testing::Return("path"));
    EXPECT_CALL(*mockViewer, message(::testing::_)).Times(::testing::AtMost(1));
    EXPECT_CALL(*mockProcess, setCompressionLevel(::testing::_)).Times(::testing::AtMost(1));
    EXPECT_CALL(*mockProcess, setQuantizationBits(::testing::_)).Times(::testing::AtMost(1));
    EXPECT_CALL(*mockProcess, setPathToSourceFile(::testing::_)).Times(::testing::AtMost(1));
    EXPECT_CALL(*mockProcess, setPathToOutputFile(::testing::_)).Times(::testing::AtMost(1));
    EXPECT_CALL(*mockProcess, doProcessAction(::testing::_)).Times(::testing::AtMost(1)).WillOnce(::testing::Return("Successful"));

    auto controller = std::make_unique<controller::ControllerImpl>(std::move(mockViewer), std::move(mockProcess));

    EXPECT_NO_THROW(controller->show());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
