#include <memory>
#include "gmock/gmock.h"
#include "interfaces/IProcess.h"
#include "interfaces/IProcessAction.h"
#include "interfaces/IProcessFactory.h"
#include "interfaces/IProcessType.h"
#include "draco_implementation/DracoCompressAction.h"
#include "draco_implementation/DracoDecompressAction.h"
#include "draco_implementation/DracoProcessFactory.h"
#include "draco_implementation/DracoProcessImpl.h"
#include "draco_implementation/DracoProcessTypeImpl.h"

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

int main(int argc, char** argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
