#include "direct_static_body.h"

#include <scene/resources/world_3d.h>
#include <servers/physics_server_3d.h>

namespace Voxel {

DirectStaticBody::DirectStaticBody() {
}

DirectStaticBody::~DirectStaticBody() {
	destroy();
}

void DirectStaticBody::create() {
	ERR_FAIL_COND(_body.is_valid());
	PhysicsServer3D &ps = *PhysicsServer3D::get_singleton();
	_body = ps.body_create(PhysicsServer3D::BODY_MODE_STATIC);
	ps.body_set_ray_pickable(_body, false);
}

void DirectStaticBody::destroy() {
	if (_body.is_valid()) {
		PhysicsServer3D &ps = *PhysicsServer3D::get_singleton();
		ps.free(_body);
		_body = RID();
		// The shape need to be destroyed after the body
		_shape.unref();
	}
	if (_debug_mesh_instance.is_valid()) {
		_debug_mesh_instance.destroy();
	}
}

bool DirectStaticBody::is_valid() const {
	return _body.is_valid();
}

void DirectStaticBody::set_transform(Transform transform) {
	ERR_FAIL_COND(!_body.is_valid());
	PhysicsServer3D::get_singleton()->body_set_state(_body, PhysicsServer3D::BODY_STATE_TRANSFORM, transform);

	if (_debug_mesh_instance.is_valid()) {
		_debug_mesh_instance.set_transform(transform);
	}
}

void DirectStaticBody::add_shape(Ref<Shape3D> shape) {
	ERR_FAIL_COND(!_body.is_valid());
	PhysicsServer3D::get_singleton()->body_add_shape(_body, shape->get_rid(), Transform(), false);
	// No use case for multishape yet
	_shape = shape;

	if (_debug_mesh_instance.is_valid()) {
		Ref<Mesh> mesh = _shape->get_debug_mesh();
		_debug_mesh_instance.set_mesh(mesh);
	}
}

void DirectStaticBody::remove_shape(int shape_index) {
	ERR_FAIL_COND(!_body.is_valid());
	PhysicsServer3D::get_singleton()->body_remove_shape(_body, shape_index);
	_shape.unref();

	if (_debug_mesh_instance.is_valid()) {
		_debug_mesh_instance.set_mesh(Ref<Mesh>());
	}
}

void DirectStaticBody::set_world(World3D *world) {
	ERR_FAIL_COND(!_body.is_valid());
	PhysicsServer3D &ps = *PhysicsServer3D::get_singleton();
	ps.body_set_space(_body, world != nullptr ? world->get_space() : RID());

	if (_debug_mesh_instance.is_valid()) {
		_debug_mesh_instance.set_world(world);
	}
}

void DirectStaticBody::set_shape_enabled(int shape_index, bool enabled) {
	ERR_FAIL_COND(!_body.is_valid());
	PhysicsServer3D &ps = *PhysicsServer3D::get_singleton();
	ps.body_set_shape_disabled(_body, shape_index, !enabled);

	if (_debug_mesh_instance.is_valid()) {
		_debug_mesh_instance.set_visible(enabled);
	}
}

void DirectStaticBody::set_attached_object(Object *obj) {
	// Serves in high-level collision query results, `collider` will contain the attached object
	ERR_FAIL_COND(!_body.is_valid());
	PhysicsServer3D::get_singleton()->body_attach_object_instance_id(_body, obj != nullptr ? obj->get_instance_id() : ObjectID());
}

void DirectStaticBody::set_debug(bool enabled, World3D *world) {

	ERR_FAIL_COND(world == nullptr);

	if (enabled && !_debug_mesh_instance.is_valid()) {

		_debug_mesh_instance.create();
		_debug_mesh_instance.set_world(world);

		Transform transform = PhysicsServer3D::get_singleton()->body_get_state(_body, PhysicsServer3D::BODY_STATE_TRANSFORM);
		_debug_mesh_instance.set_transform(transform);

		if (_shape.is_valid()) {
			Ref<Mesh> mesh = _shape->get_debug_mesh();
			_debug_mesh_instance.set_mesh(mesh);
		}

	} else if (!enabled && _debug_mesh_instance.is_valid()) {

		_debug_mesh_instance.destroy();
	}
}

}
