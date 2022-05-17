#include"../include/ConeProjector.h"
#include"../include/DataLoader.h"
#include"../astra-2.1.0/astra/Float32ProjectionData3DMemory.h"
#include"../astra-2.1.0/astra/Float32VolumeData3DMemory.h"

namespace ConeGeometry{

    const int angles = 360;
    const int projHeight = 1000;
    const int projWidth = 200;
    const int volumeWidth = 512;
    const int volumeSlice = 72;
    const int SOD = 1000;
    const int SDD = 0;
    
    float32 geometry[angles*12];
    float32 volume[volumeWidth*volumeWidth*volumeSlice];
    float32 sino[projWidth*projHeight*angles];

    void createConeXMLDocument(string xmlPath){
        XMLDocument *document = new XMLDocument();
        document = document->createDocument("projector3D");
        XMLNode root = document->getRootNode();
        root.addAttribute("type", "cuda");
        XMLNode child = root.addChildNode("ProjectionGeometry");
        child.addAttribute("type", "cone");
        child.addChildNode("DetectorSpacingX", 1);
        child.addChildNode("DetectorSpacingY", 1);
        child.addChildNode("DetectorRowCount", projWidth);
        child.addChildNode("DetectorColCount", projHeight);
        float32 projectionAngles[angles] = {0};
        for(uint i = 0;i < angles;i++)
            projectionAngles[i] = (float32)i*(360/angles);
        XMLNode vectors = child.addChildNode("ProjectionAngles");
        vectors.setContent(projectionAngles, angles);
        child.addChildNode("DistanceOriginSource", SOD);
        child.addChildNode("DistanceOriginDetector", SDD);
        child = root.addChildNode("VolumeGeometry");
        child.addChildNode("GridRowCount",volumeWidth);
        child.addChildNode("GridColCount",volumeWidth);
        child.addChildNode("GridSliceCount",volumeSlice);
        document->saveToFile(xmlPath);
    }

    void createConeVecXMLDocument(string coneVecPath, string xmlPath){
        XMLDocument *document = new XMLDocument();
        document = document->createDocument("projector3D");
        XMLNode root = document->getRootNode();
        root.addAttribute("type", "cuda");
        XMLNode child = root.addChildNode("ProjectionGeometry");
        child.addAttribute("type", "cone_vec");
        child.addChildNode("DetectorRowCount", projWidth);
        child.addChildNode("DetectorColCount", projHeight);
        XMLNode vectors = child.addChildNode("Vectors");
        readRaw(coneVecPath.c_str(), geometry, angles*12);
        vectors.setContent(geometry, angles, 12, false);
        child = root.addChildNode("VolumeGeometry");
        child.addChildNode("GridRowCount",volumeWidth);
        child.addChildNode("GridColCount",volumeWidth);
        child.addChildNode("GridSliceCount",volumeSlice);
        document->saveToFile(xmlPath);
    }

    CProjector3D* createProjector(string xmlPath){
        XMLDocument *document = new XMLDocument();
        XMLNode root = document->readFromFile(xmlPath)->getRootNode();
        Config *config = new Config(root);
        CProjector3D *projector = new CCudaProjector3D();
        projector->initialize(*config);
        return projector;
    }

    CFloat32ProjectionData3D* createSino(const string sinoFilePath, CProjector3D* projector){
        readRaw(sinoFilePath.c_str(), sino, projWidth*projHeight*angles);
        CProjectionGeometry3D *geometryOfProjection = projector->getProjectionGeometry();
        CFloat32ProjectionData3D *sinoWrap = new CFloat32ProjectionData3DMemory(geometryOfProjection, sino);
        return sinoWrap;
    }

    CFloat32ProjectionData3D* createSino(float32 *data, CProjector3D* projector, int){
        CProjectionGeometry3D *geometryOfProjection = projector->getProjectionGeometry();
        CFloat32ProjectionData3D *sinoWrap = new CFloat32ProjectionData3DMemory(geometryOfProjection, data);
        return sinoWrap;
    }

    CFloat32ProjectionData3D* createSino(const float32 scalar, CProjector3D* projector){
        CProjectionGeometry3D *geometryOfProjection = projector->getProjectionGeometry();
        CFloat32ProjectionData3D *sinoWrap = new CFloat32ProjectionData3DMemory(geometryOfProjection, scalar);
        return sinoWrap;
    }

    CFloat32VolumeData3D* createVolume(const string volumeFilePath, CProjector3D* projector){
        readRaw(volumeFilePath.c_str(), volume, volumeWidth*volumeWidth*volumeSlice);
        CVolumeGeometry3D *geometryOfVolume = projector->getVolumeGeometry();
        CFloat32VolumeData3D *volumeWrap = new CFloat32VolumeData3DMemory(geometryOfVolume, volume);
        return volumeWrap;
    }

    CFloat32VolumeData3D* createVolume(float32 *data, CProjector3D* projector, int){
        CVolumeGeometry3D *geometryOfVolume = projector->getVolumeGeometry();
        CFloat32VolumeData3D *volumeWrap = new CFloat32VolumeData3DMemory(geometryOfVolume, data);
        return volumeWrap;
    }

    CFloat32VolumeData3D* createVolume(const float32 scalar, CProjector3D* projector){
        CVolumeGeometry3D *geometryOfVolume = projector->getVolumeGeometry();
        CFloat32VolumeData3D *volumeWrap = new CFloat32VolumeData3DMemory(geometryOfVolume, scalar);
        return volumeWrap;
    }

    void saveSino(const string targetPath, CFloat32ProjectionData3D *targetSino){
        CFloat32ProjectionData3DMemory *sinoWarp = dynamic_cast<CFloat32ProjectionData3DMemory *>(targetSino);
        writeRaw(targetPath.c_str(), sinoWarp->getData(), projWidth*projHeight*angles);
    }

    void saveVolume(const string targetPath, CFloat32VolumeData3D *targetVolume){
        CFloat32VolumeData3DMemory *volumeWarp = dynamic_cast<CFloat32VolumeData3DMemory *>(targetVolume);
        writeRaw(targetPath.c_str(), volumeWarp->getData(), volumeWidth*volumeWidth*volumeSlice);
    }

    float32* getSino(CFloat32ProjectionData3D *targetSino){
        return dynamic_cast<CFloat32ProjectionData3DMemory *>(targetSino)->getData();
    }

    float32* getVolume(CFloat32VolumeData3D *targetVolume){
        return dynamic_cast<CFloat32VolumeData3DMemory *>(targetVolume)->getData();
    }
}