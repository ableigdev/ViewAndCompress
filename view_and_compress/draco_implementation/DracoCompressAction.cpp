#include <cassert>
#include <fstream>
#include "DracoCompressAction.h"
#include "draco/core/cycle_timer.h"

draco_impl::DracoCompressAction::DracoCompressAction()
    : m_QuantizationBits(14),
      m_CompressionLevel(7),
      m_PointCloud(nullptr)
{

}

void draco_impl::DracoCompressAction::setQuantizationBits(int quantizationBits)
{
    m_QuantizationBits = quantizationBits;
}

void draco_impl::DracoCompressAction::setCompressionLevel(int level)
{
    m_CompressionLevel = level;
}

void draco_impl::DracoCompressAction::setPathToSourceFile(const std::string& path)
{
    m_PathToSourceFile = path;
}

void draco_impl::DracoCompressAction::setPathToOutputFile(const std::string& path)
{
    m_PathToOutputFile = path;
}

std::string draco_impl::DracoCompressAction::doAction()
{
    draco::Mesh* mesh = nullptr;
    auto maybe_mesh = draco::ReadMeshFromFile(m_PathToSourceFile, false); // Use metadata: true or false

    if (!maybe_mesh.ok())
    {
        throw std::runtime_error("Failed loading the intput mesh: " + maybe_mesh.status().error_msg_string() + "\n");
    }
    mesh = maybe_mesh.value().get();
    m_PointCloud = std::move(maybe_mesh).value();
    // Convert compression level to speed (that 0 = slowest, 10 = fastest).
    const int speed = 10 - m_CompressionLevel;
    draco::Encoder encoder;

    // Setup encoder options
    encoder.SetAttributeQuantization(draco::GeometryAttribute::POSITION, m_QuantizationBits);
    encoder.SetAttributeQuantization(draco::GeometryAttribute::TEX_COORD, m_TexCoordsQuantizationBits);
    encoder.SetAttributeQuantization(draco::GeometryAttribute::NORMAL, m_NormalsQuantizationBits);
    encoder.SetAttributeQuantization(draco::GeometryAttribute::GENERIC, m_GenericQuantizationBits);
    encoder.SetSpeedOptions(speed, speed);

    if (m_PathToOutputFile.empty())
    {
        m_PathToOutputFile = m_PathToSourceFile + ".drc";
    }
    std::string message("Encoder options:\n");
    message += "    Compression level = " + std::to_string(m_CompressionLevel) + "\n";
    message += "    Positions: Quantization = " + std::to_string(m_QuantizationBits) + "bits\n";

    const bool inputIsMesh = mesh && mesh->num_faces() > 0;
    assert(inputIsMesh);

    if (inputIsMesh)
    {
        message += encodeMeshToFile(*mesh, &encoder);
    }

    if (m_CompressionLevel < 10)
    {
        message += "\nFor better compression, increase the compression level up to '10'.\n";
    }
    return message;
}

std::string draco_impl::DracoCompressAction::encodeMeshToFile(const draco::Mesh& mesh, draco::Encoder* encoder)
{
    draco::CycleTimer timer;
    // Encode the geometry
    draco::EncoderBuffer buffer;
    timer.Start();
    const draco::Status status = encoder->EncodeMeshToBuffer(mesh, &buffer);
    if (!status.ok())
    {
        throw std::runtime_error("Failed to encode the mesh.\n" + status.error_msg_string() + "\n");
    }
    timer.Stop();
    // Save the encoded geometry into a file
    // FIXME: Change path to file
    std::ofstream outFile(m_PathToOutputFile, std::ios::binary);

    if (!outFile)
    {
        throw std::runtime_error("Failed to create the output file.\n");
    }
    outFile.write(buffer.data(), static_cast<long>(buffer.size()));

    std::string message("\nEncoded mesh saved to " + m_PathToOutputFile +
            "('" + std::to_string(timer.GetInMs()) + "' ms to encode).\n");
    message += "Encoded size = " + std::to_string(buffer.size()) + "bytes.\n";

    return message;
}
