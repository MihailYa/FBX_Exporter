#pragma once
#include "Utilities.h"
#include <unordered_map>
#include "Material.h"

enum Texture_type { DIFFUSE_MAP, EMMISIVE_MAP, GLOSS_MAP, NORMAL_MAP, SPECULAR_MAP };
struct Texture
{
	unsigned int length_of_name;
	unsigned int texture_id;
	Texture_type texture_type;
	char *name;
};

class FBXExporter
{
public:
	FBXExporter();
	//~FBXExporter();
	bool Initialize();

	bool LoadScene(const char* inFileName);

	bool ProcessScene();
	bool ExportAsMesh(const char* inOutputPath);
	
	void ExportFBX();

private:
	FbxManager* mFBXManager;
	FbxScene* mFBXScene;
	std::string mInputFilePath;
	std::string mOutputFilePath;
	bool mHasAnimation;
	std::unordered_map<unsigned int, CtrlPoint*> mControlPoints; 
	unsigned int mTriangleCount;
	std::vector<Triangle> mTriangles;
	std::vector<PNTIWVertex> mVertices;
	std::vector<Texture> mTextures;
	Skeleton mSkeleton;
	std::unordered_map<unsigned int, Material*> mMaterialLookUp;
	FbxLongLong mAnimationLength;
	std::string mAnimationName;
	LARGE_INTEGER mCPUFreq;
	

private:
	void ProcessGeometry(FbxNode* inNode);
	void ProcessSkeletonHierarchy(FbxNode* inRootNode);
	void ProcessSkeletonHierarchyRecursively(FbxNode* inNode, int inDepth, int myIndex, int inParentIndex);
	void ProcessControlPoints(FbxNode* inNode);
	void ProcessJointsAndAnimations(FbxNode* inNode);
	unsigned int FindJointIndexUsingName(const std::string& inJointName);
	void ProcessMesh(FbxNode* inNode);
	void ReadUV(FbxMesh* inMesh, int inCtrlPointIndex, int inTextureUVIndex, int inUVLayer, XMFLOAT2& outUV);
	void ReadNormal(FbxMesh* inMesh, int inCtrlPointIndex, int inVertexCounter, XMFLOAT3& outNormal);
	void ReadBinormal(FbxMesh* inMesh, int inCtrlPointIndex, int inVertexCounter, XMFLOAT3& outBinormal);
	void ReadTangent(FbxMesh* inMesh, int inCtrlPointIndex, int inVertexCounter, XMFLOAT3& outTangent);
	void Optimize();
	int FindVertex(const PNTIWVertex& inTargetVertex, const std::vector<PNTIWVertex>& uniqueVertices);

	void AssociateMaterialToMesh(FbxNode* inNode);
	void ProcessMaterials(FbxNode* inNode);
	void ProcessMaterialAttribute(FbxSurfaceMaterial* inMaterial, unsigned int inMaterialIndex);
	void ProcessMaterialTexture(FbxSurfaceMaterial* inMaterial, Material* ioMaterial);
	void PrintMaterial();
	void PrintTriangles();
	
	void CleanupFbxManager();
	void WriteMeshToStream(std::ostream& inStream);
	void WriteAnimationToStream(std::ostream& inStream);

	void OptimizeMaterials();

	bool WriteMeshToFile(std::ostream& inStream);
	bool WriteAnimationToFile(std::ostream& inStream);
};