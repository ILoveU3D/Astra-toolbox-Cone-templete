#include<iostream>
#include"../astra-2.1.0/astra/CudaProjector3D.h"
#include"../astra-2.1.0/astra/Float32ProjectionData3D.h"
#include"../astra-2.1.0/astra/Float32VolumeData3D.h"
using namespace std;
using namespace astra;

namespace ConeGeometry{
    void createConeXMLDocument(string xmlPath);
    void createConeVecXMLDocument(string coneVecPath, string xmlPath);
    CProjector3D* createProjector(string xmlPath);
    CFloat32ProjectionData3D* createSino(const string sinoFilePath, CProjector3D* projector);
    CFloat32ProjectionData3D* createSino(const float32 scalar, CProjector3D* projector);
    CFloat32ProjectionData3D* createSino(float32* data, CProjector3D* projector, int);
    void saveSino(const string targetPath, CFloat32ProjectionData3D *sino);
    float32* getSino(CFloat32ProjectionData3D *sino);
    CFloat32VolumeData3D* createVolume(const string volumeFilePath, CProjector3D* projector);
    CFloat32VolumeData3D* createVolume(const float32 scalar, CProjector3D* projector);
    CFloat32VolumeData3D* createVolume(float32* data, CProjector3D* projector, int);
    void saveVolume(const string targetPath, CFloat32VolumeData3D *volume);
    float32* getVolume(CFloat32VolumeData3D *volume);
}