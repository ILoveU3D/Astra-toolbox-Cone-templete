#include<iostream>
#include"include/ConeProjector.h"
#include"include/Radon.h"
using namespace std;

//数据路径
const string inputPath = "/media/seu/wyk/Recon/DTV/sample.raw";
const string outputPath = "/media/seu/wyk/Recon/DTV/result.raw";
const string geometryPath = "./geometry.xml";

int main(){
	//创建几何（标准锥束）
	ConeGeometry::createConeXMLDocument(geometryPath);
	CProjector3D* projector = ConeGeometry::createProjector(geometryPath);

	//创建体块/投影图
	CFloat32ProjectionData3D *sino = ConeGeometry::createSino(0, projector);
	CFloat32VolumeData3D *volume = ConeGeometry::createVolume(inputPath, projector);

	//正投影/反投影/FDK
	Transform::createForwardProjection(sino, volume, projector);
	//Transform::createBackProjection(sino, volume, projector);
	//Transform::FDK(sino, volume, projector);
	Transform::ART(sino, volume, projector);

	//保存数据
	ConeGeometry::saveVolume(outputPath, volume);
}
