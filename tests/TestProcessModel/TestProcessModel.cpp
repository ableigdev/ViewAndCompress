#include <memory>
#include <stdexcept>
#include "gtest/gtest.h"
#include "interfaces/IProcess.h"
#include "interfaces/IProcessAction.h"
#include "interfaces/IProcessFactory.h"
#include "interfaces/IProcessType.h"
#include "draco_implementation/DracoCompressAction.h"
#include "draco_implementation/DracoDecompressAction.h"
#include "draco_implementation/DracoProcessFactory.h"
#include "draco_implementation/DracoProcessImpl.h"
#include "draco_implementation/DracoProcessTypeImpl.h"

TEST(Valid, Valid)
{
    std::unique_ptr<interfaces::IProcessFactory> factory(new draco_impl::DracoProcessFactory);
    std::unique_ptr<interfaces::IProcess> process(factory->createProcess());
    std::unique_ptr<interfaces::IProcessAction> compress(new draco_impl::DracoCompressAction);
    std::unique_ptr<interfaces::IProcessAction> decompress(new draco_impl::DracoDecompressAction);

    EXPECT_TRUE(factory != nullptr);
    EXPECT_TRUE(process != nullptr);
    EXPECT_TRUE(compress != nullptr);
    EXPECT_TRUE(decompress != nullptr);
}

TEST(SetSourcePath, Valid)
{
    std::unique_ptr<interfaces::IProcessFactory> factory(new draco_impl::DracoProcessFactory);
    std::unique_ptr<interfaces::IProcess> process(factory->createProcess());

    EXPECT_NO_THROW(process->setPathToSourceFile("/path/to/source/file"));
}

TEST(SetSourcePath, EmptyPath)
{
    std::unique_ptr<interfaces::IProcessFactory> factory(new draco_impl::DracoProcessFactory);
    std::unique_ptr<interfaces::IProcess> process(factory->createProcess());

    EXPECT_THROW(process->setPathToSourceFile(""), std::invalid_argument);
}

TEST(SetOutputPath, Valid)
{
    std::unique_ptr<interfaces::IProcessFactory> factory(new draco_impl::DracoProcessFactory);
    std::unique_ptr<interfaces::IProcess> process(factory->createProcess());

    EXPECT_NO_THROW(process->setPathToOutputFile("/path/to/output/file"));
}

TEST(SetOutputPath, EmptyPath)
{
    std::unique_ptr<interfaces::IProcessFactory> factory(new draco_impl::DracoProcessFactory);
    std::unique_ptr<interfaces::IProcess> process(factory->createProcess());

    EXPECT_THROW(process->setPathToOutputFile(""), std::invalid_argument);
}

TEST(SetCompressionLevel, ValidValue)
{
    std::unique_ptr<interfaces::IProcessFactory> factory(new draco_impl::DracoProcessFactory);
    std::unique_ptr<interfaces::IProcess> process(factory->createProcess());

    EXPECT_NO_THROW(process->setCompressionLevel(5));
}

TEST(SetCompressionLevel, LessThanValidValue)
{
    std::unique_ptr<interfaces::IProcessFactory> factory(new draco_impl::DracoProcessFactory);
    std::unique_ptr<interfaces::IProcess> process(factory->createProcess());

    EXPECT_THROW(process->setCompressionLevel(0), std::out_of_range);
}

TEST(SetCompressionLevel, MoreThanValidValue)
{
    std::unique_ptr<interfaces::IProcessFactory> factory(new draco_impl::DracoProcessFactory);
    std::unique_ptr<interfaces::IProcess> process(factory->createProcess());

    EXPECT_THROW(process->setCompressionLevel(11), std::out_of_range);
}

TEST(SetQuantizationBits, ValidValue)
{
    std::unique_ptr<interfaces::IProcessFactory> factory(new draco_impl::DracoProcessFactory);
    std::unique_ptr<interfaces::IProcess> process(factory->createProcess());

    EXPECT_NO_THROW(process->setQuantizationBits(14));
}

TEST(SetQuantizationBits, LessThanValidValue)
{
    std::unique_ptr<interfaces::IProcessFactory> factory(new draco_impl::DracoProcessFactory);
    std::unique_ptr<interfaces::IProcess> process(factory->createProcess());

    EXPECT_THROW(process->setQuantizationBits(0), std::out_of_range);
}

TEST(SetQuantizationBits, MoreThanValidValue)
{
    std::unique_ptr<interfaces::IProcessFactory> factory(new draco_impl::DracoProcessFactory);
    std::unique_ptr<interfaces::IProcess> process(factory->createProcess());

    EXPECT_THROW(process->setQuantizationBits(31), std::out_of_range);
}

TEST(SetProcessAction, NullPointer)
{
    std::unique_ptr<interfaces::IProcessFactory> factory(new draco_impl::DracoProcessFactory);
    std::unique_ptr<interfaces::IProcess> process(factory->createProcess());

    EXPECT_THROW(process->doProcessAction(nullptr), std::invalid_argument);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
