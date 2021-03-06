
def can_build(env, platform):
  return True


def configure(env):
	pass


def get_doc_classes():
  return [
    "VoxelBuffer",
    "VoxelMap",

    "Voxel",
    "VoxelLibrary",

    "VoxelTerrain",
    "VoxelLodTerrain",

    "VoxelStream",
    "VoxelStreamFile",
    "VoxelStreamBlockFiles",
    "VoxelStreamRegionFiles",

    "VoxelGenerator",
    "VoxelGeneratorHeightmap",
    "VoxelGeneratorImage",
    "VoxelGeneratorNoise",
    "VoxelGeneratorNoise2D",
    "VoxelGeneratorTest",

    "VoxelBoxMover",
    "VoxelTool",
    "VoxelRaycastResult",

    "VoxelMesher",
    "VoxelMesherBlocky",
    "VoxelMesherTransvoxel",
    "VoxelMesherDMC"

    ]


def get_doc_path():
  return "doc/classes"
