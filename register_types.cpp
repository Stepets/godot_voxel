#include "register_types.h"
#include "edition/voxel_tool.h"
#include "generators/voxel_generator_flat.h"
#include "generators/voxel_generator_heightmap.h"
#include "generators/voxel_generator_image.h"
#include "generators/voxel_generator_noise.h"
#include "generators/voxel_generator_noise_2d.h"
#include "generators/voxel_generator_waves.h"
#include "meshers/blocky/voxel_library.h"
#include "meshers/blocky/voxel_mesher_blocky.h"
#include "meshers/dmc/voxel_mesher_dmc.h"
#include "meshers/transvoxel/voxel_mesher_transvoxel.h"
#include "streams/voxel_stream_block_files.h"
#include "streams/voxel_stream_file.h"
#include "streams/voxel_stream_region_files.h"
#include "terrain/voxel_box_mover.h"
#include "terrain/voxel_lod_terrain.h"
#include "terrain/voxel_map.h"
#include "terrain/voxel_terrain.h"
#include "voxel_buffer.h"
#include "voxel_memory_pool.h"
#include "voxel_string_names.h"

void register_voxel_types() {
	using namespace Voxel;

	// Storage
	ClassDB::register_class<VoxelBuffer>();
	ClassDB::register_class<VoxelMap>();

	// Voxel types
	ClassDB::register_class<::Voxel::Voxel>();
	ClassDB::register_class<VoxelLibrary>();

	// Nodes
	ClassDB::register_class<VoxelTerrain>();
	ClassDB::register_class<VoxelLodTerrain>();

	// Streams
	ClassDB::register_class<VoxelStream>();
	ClassDB::register_class<VoxelStreamFile>();
	ClassDB::register_class<VoxelStreamBlockFiles>();
	ClassDB::register_class<VoxelStreamRegionFiles>();

	// Generators
	ClassDB::register_class<VoxelGenerator>();
	ClassDB::register_class<VoxelGeneratorFlat>();
	ClassDB::register_class<VoxelGeneratorWaves>();
	ClassDB::register_class<VoxelGeneratorHeightmap>();
	ClassDB::register_class<VoxelGeneratorImage>();
	ClassDB::register_class<VoxelGeneratorNoise2D>();
	ClassDB::register_class<VoxelGeneratorNoise>();

	// Helpers
	ClassDB::register_class<VoxelBoxMover>();
	ClassDB::register_class<VoxelRaycastResult>();
	ClassDB::register_class<VoxelTool>();

	// Meshers
	ClassDB::register_class<VoxelMesher>();
	ClassDB::register_class<VoxelMesherBlocky>();
	ClassDB::register_class<VoxelMesherTransvoxel>();
	ClassDB::register_class<VoxelMesherDMC>();

	VoxelMemoryPool::create_singleton();
	VoxelStringNames::create_singleton();

#ifdef TOOLS_ENABLED
	VoxelDebug::create_debug_box_mesh();
#endif
}

void unregister_voxel_types() {
	using namespace Voxel;

	unsigned int used_blocks = VoxelMemoryPool::get_singleton()->debug_get_used_blocks();
	if (used_blocks > 0) {
		ERR_PRINT(String("VoxelMemoryPool: {0} memory blocks are still used when unregistering the module. Recycling leak?").format(varray(used_blocks)));
	}
	VoxelMemoryPool::destroy_singleton();

	VoxelStringNames::destroy_singleton();

#ifdef TOOLS_ENABLED
	VoxelDebug::free_debug_box_mesh();
#endif
}
