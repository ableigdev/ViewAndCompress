#include <fstream>
#include <cassert>
#include "DracoDecompressAction.h"
#include "draco/io/parser_utils.h"
#include "draco/io/ply_encoder.h"
#include "draco/io/obj_encoder.h"
#include "draco/core/cycle_timer.h"

draco_impl::DracoDecompressAction::DracoDecompressAction()
    : m_QuantizationBits(14),
      m_CompressionLevel(7),
      m_PointCloud(nullptr)
{

}

void draco_impl::DracoDecompressAction::setCompressionLevel(int level)
{
    m_CompressionLevel = level;
}

void draco_impl::DracoDecompressAction::setQuantizationBits(int quantizationBits)
{
    m_QuantizationBits = quantizationBits;
}

void draco_impl::DracoDecompressAction::setPathToSourceFile(const std::string& path)
{
    m_PathToSourceFile = path;
}

void draco_impl::DracoDecompressAction::setPathToOutputFile(const std::string& path)
{
    m_PathToOutputFile = path;
}

std::string draco_impl::DracoDecompressAction::doAction()
{
    readFromFile();
    // Create a draco decoding buffer.
    // Note that no data is copied in this step.
    draco::DecoderBuffer buffer;
    draco::CycleTimer timer;
    draco::Mesh* mesh = nullptr;
    buffer.Init(m_DataFromFile.data(), m_DataFromFile.size());
    auto typeStatusor = draco::Decoder::GetEncodedGeometryType(&buffer);

    if (!typeStatusor.ok())
    {
        throw std::runtime_error(returnError(typeStatusor.status()));
    }

    const draco::EncodedGeometryType geomType = typeStatusor.value();
    assert(geomType == draco::TRIANGULAR_MESH);
    if (geomType == draco::TRIANGULAR_MESH)
    {
        timer.Start();
        draco::Decoder decoder;
        auto statusor = decoder.DecodeMeshFromBuffer(&buffer);
        if (!statusor.ok())
        {
            throw std::runtime_error(returnError(statusor.status()));
        }
        std::unique_ptr<draco::Mesh> inMesh = std::move(statusor).value();
        timer.Stop();
        if (inMesh)
        {
            mesh = inMesh.get();
            m_PointCloud = std::move(inMesh);
        }
    }

    if (m_PointCloud == nullptr)
    {
        throw std::runtime_error("Failed to decode the input file.\n");
    }

    if (m_PathToOutputFile.empty())
    {
        m_PathToOutputFile = m_PathToSourceFile + ".ply";
    }

    const std::string extension = draco::parser::ToLower(
        m_PathToOutputFile.size() >= 4
            ? m_PathToOutputFile.substr(m_PathToOutputFile.size() - 4)
            : m_PathToOutputFile);

    if (extension == ".obj")
    {
        draco::ObjEncoder obj_encoder;
        if (mesh)
        {
            if (!obj_encoder.EncodeToFile(*mesh, m_PathToOutputFile))
            {
                throw std::runtime_error("Failed to store the decoded mesh as OBJ.\n");
            }
        }
        else
        {
            if (!obj_encoder.EncodeToFile(*m_PointCloud.get(), m_PathToOutputFile))
            {
                throw std::runtime_error("Failed to store the decoded point cloud as OBJ.\n");
            }
        }
    }
    else if (extension == ".ply")
    {
        draco::PlyEncoder ply_encoder;
        if (mesh)
        {
            if (!ply_encoder.EncodeToFile(*mesh, m_PathToOutputFile))
            {
                throw std::runtime_error("Failed to store the decoded mesh as PLY.\n");
            }
        }
        else
        {
            if (!ply_encoder.EncodeToFile(*m_PointCloud.get(), m_PathToOutputFile))
            {
                throw std::runtime_error("Failed to store the decoded point cloud as PLY.\n");
            }
        }
    }
    else
    {
        throw std::runtime_error("Invalid extension of the output file. Use either .ply or .obj\n");
    }


    return std::string("Decoded geometry saved to " +
                       m_PathToOutputFile + "('" + std::to_string(timer.GetInMs()) + "' ms to decode)\n");
}

void draco_impl::DracoDecompressAction::readFromFile()
{
    std::ifstream inputFile(m_PathToSourceFile, std::ios::binary);
    if (!inputFile)
    {
        throw std::runtime_error("Failed opening the input file.\n");
    }
    // Read the file stream into a buffer.
    std::streampos fileSize = 0;
    inputFile.seekg(0, std::ios::end);
    fileSize = inputFile.tellg() - fileSize;
    inputFile.seekg(0, std::ios::beg);
    m_DataFromFile.resize(static_cast<size_t>(fileSize));
    inputFile.read(m_DataFromFile.data(), fileSize);

    if (m_DataFromFile.empty())
    {
        throw std::runtime_error("Empty input file.\n");
    }
}

std::string draco_impl::DracoDecompressAction::returnError(const draco::Status& status)
{
    return std::string("Failed to decode the input file " + status.error_msg_string() + "\n");
}
